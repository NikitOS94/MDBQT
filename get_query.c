#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "postgres.h"
#include "fmgr.h"
#include "utils/builtins.h"
#include "utils/pg_crc.h"
#include "miscadmin.h"

#include "structures.h"
#include "get_query.h"

//Function for concatination 1 string with form
static char* 
sconcat1(char *form, char *s1, int plus) 
{
    size_t   len1 = strlen(s1);               
    char    *result = palloc(len1 + 1 + plus);

    sprintf(result,form,s1);  

    return result;
}

//Function for concatination 2 strings with form
static char* 
sconcat2(char *form, char *s1, char *s2, int plus) 
{
    size_t   len1 = strlen(s1);
    size_t   len2 = strlen(s2);                      
    char    *result = palloc(len1 + len2 + 1 + plus);
    
    sprintf(result,form,s1,s2);  

    return result;
}

//Function for concatination 3 strings with form
static char* 
sconcat3(char *form, char *s1, char *s2, char *s3, int plus) 
{
    size_t   len1 = strlen(s1);
    size_t   len2 = strlen(s2); 
    size_t   len3 = strlen(s3);                      
    char    *result = palloc(len1 + len2 + len3 + 1 + plus);

    sprintf(result, form, s1, s2, s3);  

    return result;
}

char *
get_value_operator_type(value_operator_type vop_type)
{
    switch(vop_type)
    {
        case _LESS :
            return "<";
        case _EQ :
        case _NOTEQ :
            return "=";
        case _LESSEQ :
            return "<=";
        case _GREAT :
            return ">";
        case _GREATEQ :
            return ">=";
        case _TYPE :
            return "";
        case _SIZE :
            return ".@# =";
        case _EXISTS :
            return "= *";
        default :
            elog(ERROR,"This value operator is not supported");
            break;
    }
    return NULL;
}

char *
get_value_type(char *value_type)
{
    if(strcmp(value_type,"\"string\"") == 0)              return " IS STRING";
    else if(
                strcmp(value_type, "\"double\"") == 0 || 
                strcmp(value_type, "\"int\"") == 0 || 
                strcmp(value_type, "\"long\"") == 0 || 
                strcmp(value_type, "\"decimal\"") == 0
            )                                             return " IS NUMERIC";
                             
    else if(strcmp(value_type, "\"array\"") == 0)         return " IS ARRAY";
    else if(strcmp(value_type, "\"object\"") == 0)        return " IS OBJECT";
    else if(strcmp(value_type, "\"bool\"") == 0)          return " IS BOOLEAN";
    else                                                  elog(ERROR, "Jsquery is not supported MongoDB %s value type", value_type);
}

char *
get_value_operator(char *key, ValueOperator *vop)
{
    char *result;
    char *value;
    char *opr = get_value_operator_type(vop->value_op);

    if(vop->value_op == _EXISTS)
    {
        result = vop->value->b ? sconcat2("%s %s", key, opr, 1) : sconcat2("NOT (%s %s)", key, opr, 7);
        goto WITHOUT_VALUE;
    }

    value = getLeafValue(vop->value);

    if(vop->value_op == _TYPE)
    {
        result = sconcat2("%s %s", key, get_value_type(value), 1);
        goto WITHOUT_VALUE;
    }

    if(vop->value_op == _NOTEQ)
    {
        result = sconcat3("NOT (%s %s %s)", key, opr, value, 8);
        goto WITH_VALUE;
    }

    result = sconcat3("%s %s %s", key, opr, value, 2);
    
    WITH_VALUE:
    free(value);

    WITHOUT_VALUE:
    pfree(vop);

    return result;
}

char *
get_operator(char *key, operator *op)
{
    switch(op->type)
    {
        case NOP :
            return get_not_operator(key, (not_operator*) op );
        case MOP :
            elog(ERROR, "MongoDB module operator is not supported by jsquery");
        case AOP :
            return getArrayOperator(key, (array_operator*) op );
        case VOP :
            return get_value_operator(key, (ValueOperator*) op );
        default  :
            return NULL;
    }
}

char * 
get_not_operator(char *key, not_operator *op)
{
    char *oper = get_operator(key,op->op);
    
    pfree(op);
    
    return sconcat1("NOT (%s)", oper, 6);
}

char *
get_operator_object(char *key, operator_object *op_object)
{
    char *str;
    char *buff="";

    ListCell *cell;
    List *operatorList = op_object->operatorList;

    buff = get_operator(key, ((operator *)list_nth(operatorList, 0))); 

    if(length(operatorList)>1)
    {
        buff = sconcat1("(%s)", buff, 2);
        list_delete_first(operatorList);
        foreach(cell, operatorList)
        {
            str = get_operator(key, ((operator *)lfirst(cell)));
            buff = sconcat2("%s AND (%s)", buff, str, 7);
        }
    }
       
    pfree(operatorList);
    pfree(op_object);

    return buff;
}

char*
getLeafValue_eq(char *key, LeafValue *lv)
{
    char *result = sconcat2("%s = %s", key, getLeafValue(lv), 3);
    pfree(lv);

    return result;
}

char *
get_leaf_clause_value(char *key, MDBValue *val)
{ 
    return (val->type ? get_operator_object(key, val->oob) : getLeafValue_eq(key, val->lv) );
}

char *
get_leaf_clause(leaf_clause *lc)
{
    char *result = get_leaf_clause_value(lc->key, lc->vl);
    pfree(lc);
    return result;
}

char *
getExpression_operator(expression_operator_type exp_op)
{
    switch(exp_op)
    {
        case _AND :
            return "AND";
        case _OR :
            return "OR";
        case _NOR :
            return "NOR";
        default :
            elog(ERROR,"This expression operator is not supported");
            break;
    }

    return NULL;
}

char *
getExpression_clause(expression_clause* exp_clause)
{
    char *str;
    char *buff;

    List *expressionList = exp_clause->expressionList;
    ListCell *cell;

    buff = getExpression((Expression *)list_nth(expressionList,0)); 
    if(length(expressionList)>1)
    {
        buff = sconcat1("(%s)", buff, 2);
        list_delete_first(expressionList);

        char   *expOperator;
        expOperator = getExpression_operator(exp_clause->op);

        foreach(cell, expressionList)
        {
            str = getExpression((Expression *)lfirst(cell));
            buff = sconcat3("%s %s (%s)", buff, expOperator, str, 4);
        }   
    }

    pfree(expressionList);
    pfree(exp_clause);

    return buff;
}

char *
get_text_clause(text_clause* t_clause)
{
    char   *result = sconcat1("* = %s", t_clause->search_str, 4);
    pfree(t_clause);

    return result;
}

char *
get_clause(Clause *cl)
{  
    switch(cl->type)
    {
        case LEAF :
            return get_leaf_clause((leaf_clause*) cl);
        case COMMENT :
            elog(ERROR, "MpngoDB comment clause is not supported by jsquery");
        case TEXT :
            return get_text_clause((text_clause*) cl);
        case WHERE :
            elog(ERROR, "MpngoDB where clause is not supported by jsquery");
        case EXPRESSION :
            return getExpression_clause((expression_clause*) cl);
        default:
            return NULL;
    }
}

char *
getExpression(Expression * ex)
{
    char *str;
    char *buff="";

    List *clauseList = ex->clauseList;
    ListCell *cell;

    buff = get_clause((Clause *)list_nth(clauseList,0)); 
    list_delete_first(clauseList);

    if(length(clauseList)>1)
        foreach(cell, clauseList)
        {
            str = get_clause((Clause *)lfirst(cell));
            buff = sconcat2("%s AND %s", buff, str, 5);
        }
    
    pfree(ex);

    return buff;
}

char *
getLeafValue(LeafValue *value)
{
    switch(value->type)
    {
        case S :
            return value->str;
        case I :
            return value->i;
        case A :
            return getArray(value->ar);
        case B :
            return (value->b==_false ? "false" : "true");
        case D :
            return value->d;
    }

    return NULL;
}

char *
getArray(_array *ar)
{ 
    char        *str;
    char        *buff;
    List        *arrayList;
    ListCell    *cell;

    arrayList = ar->arrayList;
    buff = getLeafValue((LeafValue *)list_nth(arrayList, 0)); 
    list_delete_first(arrayList);

    foreach(cell, arrayList)
    {
        str = getLeafValue((LeafValue *)lfirst(cell));
        buff = sconcat2("%s, %s", str, buff, 2);
    }

    pfree(arrayList);
    pfree(ar);

    return sconcat1("[%s]", buff, 2);
}

char *
getArrayOperatorType(array_operator_type aop_type)
{
    switch(aop_type)
    {
        case _IN :
        case _NIN:
            return "<@";
        case _ALL:
            return "&&";
        default  :
            return NULL;
    }
}

char *
getArrayOperator(char *key, array_operator *aop)
{        
    char *ar = getArray(aop->ar);
    char *ar_opr = getArrayOperatorType(aop->array_op);
    pfree(aop); 
    
    if(aop->array_op == _NIN)
        return sconcat3("NOT (%s %s %s)", key, ar_opr, ar, 8);
    else
        return sconcat3("%s %s %s", key, ar_opr, ar, 2);    
}

char *
getJsquery(MDBQuery *qu)
{
    return getExpression(qu->exp);
}