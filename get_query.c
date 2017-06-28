#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "postgres.h"
#include "fmgr.h"
#include "utils/builtins.h"
#include "utils/pg_crc.h"
#include "miscadmin.h"
#include "utils/jsonb.h"

#include "structures.h"
#include "get_query.h"

void 
nSError(char *s) 
{ 
    //fprintf (stderr, "\n%s not supported by jsquery \n", s); 
    exit(0);
}

char* sconcat1(char *form, char *s1, int plus) 
{

    size_t len1 = strlen(s1);               

    char *result = palloc(len1 + 1 + plus);

    if (!result) {
      //  fprintf(stderr, "malloc() failed: insufficient memory!\n");
        return NULL;
    }

    sprintf(result,form,s1);  

    return result;
}

char* sconcat2(char *form, char *s1, char *s2, int plus) 
{

    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);                      

    char *result = palloc(len1 + len2 + 1 + plus);

    if (!result) {
       // fprintf(stderr, "malloc() failed: insufficient memory!\n");
        return NULL;
    }

    sprintf(result,form,s1,s2);  

    return result;
}

char* sconcat3(char *form, char *s1, char *s2, char *s3, int plus) 
{

    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2); 
    size_t len3 = strlen(s3);                      

    char *result = palloc(len1 + len2 + len3 + 1 + plus);

    if (!result) {
     //   fprintf(stderr, "malloc() failed: insufficient memory!\n");
        return NULL;
    }

    sprintf(result, form, s1, s2, s3);  

    return result;
}

char *
get_value_operator_type(value_operator_type vop_type)
{
    char *op;
    switch(vop_type)
    {
        case _LESS :
            op = "<";
            break;
        case _EQ :
        case _NOTEQ :
            op = "=";
            break;
        case _LESSEQ :
            op = "<=";
            break;
        case _GREAT :
            op = ">";
        case _GREATEQ :
            op = ">=";
            break;
        case _TYPE :
            op = "";
            break;
        case _SIZE :
            op = ".@# =";
            break;
        case _EXISTS :
            op = "= *";
            break;
    }
    return op;
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
    else                                                  nSError(value_type);
}

char *
get_value_operator(char *key, value_operator *vop)
{
    char *result;
    char *opr = get_value_operator_type(vop->value_op);

    if(vop->value_op == _EXISTS)
    {
        result = vop->value->b ? sconcat2("%s %s", key, opr, 1) : sconcat2("NOT (%s %s)", key, opr, 7);
        goto WITHOUT_VALUE;
    }

    char *value = get_leaf_value(vop->value);

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
    char *result;
    switch(op->type)
    {
        case NOP :
            result = get_not_operator(key, (not_operator*) op );
            break;
        case MOP :
            nSError("Module operator not suppported by jsquery"); //not supported by jsquery
        case AOP :
            result = get_array_operator(key, (array_operator*) op );
            break;
        case VOP :
            result = get_value_operator(key, (value_operator*) op );
            break;
    }
    
    return result;
}

char * 
get_not_operator(char *key, not_operator *op)
{
    char *oper = get_operator(key,op->op);
    char *result = sconcat1("NOT (%s)", oper, 6);

    pfree(op);

    return result;
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
get_leaf_value_eq(char *key, leaf_value *lv)
{
    char *result = sconcat2("%s = %s", key, get_leaf_value(lv), 3);
    pfree(lv);

    return result;
}

char *
get_leaf_clause_value(char *key, value *val)
{ 
    return (val->type ? get_operator_object(key, val->oob) : get_leaf_value_eq(key, val->lv) );
}

char *
get_leaf_clause(leaf_clause *lc)
{
    char *result = get_leaf_clause_value(lc->key, lc->vl);
    pfree(lc);
    return result;
}

char *
get_expression_operator(expression_operator_type exp_op)
{
    switch(exp_op)
    {
        case _AND :
            return "AND";
        case _OR :
            return "OR";
        case _NOR :
            return "NOR";
    }
}

char *
get_expression_clause(expression_clause* exp_clause)
{
    char *str;
    char *buff="";

    List *expressionList = exp_clause->expressionList;
    ListCell *cell;

    buff = get_expression((expression *)list_nth(expressionList,0)); 
    if(length(expressionList)>1)
    {
        buff = sconcat1("(%s)", buff, 2);
        list_delete_first(expressionList);
        char   *expOperator = get_expression_operator(exp_clause->op);

        foreach(cell, expressionList)
        {
            str = get_expression((expression *)lfirst(cell));
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
            nSError("COMMENT clause");  //Not supported by jsquery
        case TEXT :
            return get_text_clause((text_clause*) cl);
        case WHERE :
            nSError("WHERE clause");  //Not supported by jsquery
        case EXPRESSION :
            return get_expression_clause((expression_clause*) cl);
    }
}

char *
get_expression(expression * ex)
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
get_leaf_value(leaf_value *value)
{
    char *val;
    switch(value->type)
    {
        case S :
            val = value->str;
            break;
        case I :
            val = value->i;
            break;
        case A :
            val = get_array(value->ar);
            break;
        case B :
            val = (value->b==_false ? "false" : "true");
            break;
        case D :
            val = value->d;
            break;
    }

    return val;
}

char *
get_array(_array *ar)
{ 
    char *str;
    char *buff="";

    List *arrayList = ar->arrayList;
    ListCell *cell;

    buff = get_leaf_value((leaf_value *)list_nth(arrayList, 0)); 
    list_delete_first(arrayList);

    foreach(cell, arrayList)
    {
        str = get_leaf_value((leaf_value *)lfirst(cell));
        buff = sconcat2("%s, %s", str, buff, 2);
    }

    pfree(arrayList);
    pfree(ar);

    return sconcat1("[%s]", buff, 2);
}

char *
get_array_operator_type(array_operator_type aop_type)
{
    switch(aop_type)
    {
        case _IN:
        case _NIN:
            return "<@";
            break;
        case _ALL:
            return "&&";
            break;
    }
}

char *
get_array_operator(char *key, array_operator *aop)
{        
    char *ar = get_array(aop->ar);
    char *ar_opr = get_array_operator_type(aop->array_op);
    char *result;

    if(aop->array_op == _NIN)
        result = sconcat3("NOT (%s %s %s)", key, ar_opr, ar, 8);
    else
        result = sconcat3("%s %s %s", key, ar_opr, ar, 2);

    pfree(aop); 

    return result;    
}

char *
get_jsquery(MDBQuery *qu)
{
    char   *expr = get_expression(qu->exp);
    return expr;
}