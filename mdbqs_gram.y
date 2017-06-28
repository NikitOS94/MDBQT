%{
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
    #include "create_query.h"

    #define DatumGetMDBQueryP(d) ((MDBQuery*)DatumGetPointer(PG_DETOAST_DATUM(d)))
    #define PG_RETURN_MDBQUERY(p) PG_RETURN_POINTER(p)
    #define PG_GETARG_MDBQUERY(x) DatumGetMDBQueryP(PG_GETARG_DATUM(x))

    MDBQuery *RET;

    typedef struct yy_buffer_state * YY_BUFFER_STATE;
    extern int yyparse();
    extern YY_BUFFER_STATE yy_scan_string(char * str);
    extern void yy_delete_buffer(YY_BUFFER_STATE buffer);

    void 
    yyerror(char *s) 
    { 
        //fprintf (stderr, "%s\n", s); 
        exit(0);
    }

    void 
    nSError(char *s) 
    { 
        //fprintf (stderr, "\n%s not supported by jsquery \n", s); 
        exit(0);
    }

    _array *
    createNewArray(List *arrayList) 
    {
        _array *new_ar = (_array *) palloc(sizeof(_array));
        new_ar->arrayList = arrayList;
        return new_ar;
    }

    List *
    addArrayElement(leaf_value * value, List *arrayList) 
    {
        return lappend(arrayList, value);
    }

    operator *
    createNotOperator(operator *op) 
    {
        not_operator *new_op = (not_operator *) palloc(sizeof(operator));
        new_op->type = NOP;
        new_op->op = op;
        return (operator*) new_op;
    }

    operator *
    createModOperator(leaf_value *divisor, leaf_value *remainder) 
    {
        mod_operator *new_op = (mod_operator *) palloc(sizeof(mod_operator));
        new_op->type = MOP;
        new_op->divisor = divisor;
        new_op->remainder = remainder;
        return (operator*) new_op;
    }

    operator *
    createArrayOperator(array_operator_type op, _array *ar) 
    {
        array_operator *new_op = (array_operator *) palloc(sizeof(array_operator));
        new_op->type = AOP;
        new_op->array_op = op;
        new_op->ar = ar;
        return (operator*) new_op;
    }

    operator *
    createValueOperator(value_operator_type op, leaf_value * value) 
    {
        value_operator *new_op = (value_operator *) palloc(sizeof(value_operator));
        new_op->type = VOP;  
        new_op->value_op = op;
        new_op->value = value;
        return (operator*) new_op;
    }

    leaf_value *
    createStringValue(char *str)
    {
        leaf_value *lv = (leaf_value *) palloc(sizeof(leaf_value));
        lv->type = S;
        lv->str = str;
        return lv;
    }

    leaf_value *
    createDoubleValue(char* d)
    {
        leaf_value *lv = (leaf_value *) palloc(sizeof(leaf_value));
        lv->type = D;
        lv->d = d;
        return lv;
    }

    leaf_value *
    createIntegerValue(char* i)
    {
        leaf_value *lv = (leaf_value *) palloc(sizeof(leaf_value));
        lv->type = I;
        lv->i = i;
        return lv;
    }

    leaf_value *
    createArrayValue(_array *ar)
    {
      leaf_value *lv = (leaf_value *) palloc(sizeof(leaf_value));
      lv->type = A;
      lv->ar = ar;
      return lv;
    }

    leaf_value *
    createBooleanValue(_bool b)
    {
      leaf_value *lv = (leaf_value *) palloc(sizeof(leaf_value));
      lv->type = B;
      lv->b = b;
      return lv;
    }

    List *
    addOperator(operator *op, List *operatorList) 
    {  
        return lcons(op, operatorList);
    }

    operator_object *
    createOperatorObject(List *operatorList) 
    {
        operator_object *new_oob = (operator_object *) palloc(sizeof(operator_object));
        new_oob->operatorList = operatorList;
        return new_oob;
    }

    value *
    createOperatorObjectValue(operator_object *oob) 
    {
        value *vl = (value *) palloc(sizeof(value));
        vl->type = OP_OBJECT;
        vl->oob = oob;
        return vl;
    }

    value *
    createLeafValueValue(leaf_value *lv) 
    {
        value *vl = (value *) palloc(sizeof(value));
        vl->type = LF_VALUE;
        vl->lv = lv;
        return vl;
    }

    Clause *
    createLeafClause(char* key, value *vl) 
    {
        leaf_clause *new_lc = (leaf_clause *) palloc(sizeof(leaf_clause));
        new_lc->type = LEAF;
        new_lc->key = key;
        new_lc->vl = vl;
        return ( Clause* ) new_lc;
    }

    Clause *
    createCommentClause(char *op, char *str) 
    {
        comment_clause *new_com_cl = (comment_clause *) palloc(sizeof(comment_clause));
        new_com_cl->type = COMMENT;
        new_com_cl->op = op;
        new_com_cl->str = str;
        return ( Clause* ) new_com_cl;
    }

    where_clause_value *
    stringToWhereClauseValue(char *str)
    {
        where_clause_value *wcv = (where_clause_value *) palloc(sizeof(where_clause_value));
        wcv->str = str;   
        return wcv;
    }

    Clause *
    createWhereClause(char *op, where_clause_value *wcv)
    {
        where_clause *wc = (where_clause *) palloc(sizeof(where_clause));
        wc->type = WHERE;
        wc->op = op;
        wc->wcv = wcv;
        return (Clause *) wc;
    }

    List *
    addClause(Clause *clause, List *clauseList)
    {
        return lappend(clauseList, clause);
    }

    expression *
    createExpression(List *clauseList)
    {
        expression *exp = (expression *) palloc(sizeof(expression));
        exp->clauseList = clauseList;
        return exp;
    }

    List *
    addExpression(expression *exp, List *expressionList)
    {
        return lcons(exp, expressionList);
    }

    Clause *
    createExpressionTreeClause(expression_operator_type op, List *expressionList)
    {
        expression_clause *exp_cl = (expression_clause *) palloc(sizeof(expression_clause));
        exp_cl->type = EXPRESSION;
        exp_cl->op = op;
        exp_cl->expressionList = expressionList;
        return (Clause *) exp_cl;
    }

    Clause *
    createTextClause(char* search_str, _bool lang_op, char* lang_str, _bool case_sense, _bool diacr_sense)
    {
        text_clause *text_cl = (text_clause *) palloc(sizeof(text_clause));
        text_cl->type = TEXT;
        text_cl->search_str = search_str;
        text_cl->lang_op = lang_op;
        text_cl->lang_str = lang_str;
        text_cl->case_sense = case_sense;
        text_cl->diacr_sense = diacr_sense;
        return (Clause *) text_cl;
    }

    MDBQuery *
    createQuery(expression *exp)
    {
        MDBQuery *qu = (MDBQuery *) palloc(sizeof(MDBQuery));
        qu->exp = exp;
        return qu;
    }

    char* sconcat(char *form, char *s1, char *s2, int plus) 
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

    char* sconcatsingle(char *form, char *s1, int plus) 
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
            result = vop->value->b ? sconcat("%s %s", key, opr, 1) : sconcat("NOT (%s %s)", key, opr, 7);
            goto WITHOUT_VALUE;
        }

        char *value = get_leaf_value(vop->value);

        if(vop->value_op == _TYPE)
        {
            result = sconcat("%s %s", key, get_value_type(value), 1);
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
        char *result = sconcatsingle("NOT (%s)", oper, 6);

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
            buff = sconcatsingle("(%s)", buff, 2);
            list_delete_first(operatorList);
            foreach(cell, operatorList)
            {
                str = get_operator(key, ((operator *)lfirst(cell)));
                buff = sconcat("%s AND (%s)", buff, str, 7);
            }
        }
           
        pfree(operatorList);
        pfree(op_object);

        return buff;
    }
    
    char*
    get_leaf_value_eq(char *key, leaf_value *lv)
    {
        char *result = sconcat("%s = %s", key, get_leaf_value(lv), 3);
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
            buff = sconcatsingle("(%s)", buff, 2);
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
        char   *result = sconcatsingle("* = %s", t_clause->search_str, 4);
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
                buff = sconcat("%s AND %s", buff, str, 5);
            }
        
        pfree(ex);

        return buff;
    }

    char *
    get_jsquery(MDBQuery *qu)
    {
        char   *expr = get_expression(qu->exp);
        char   *result = sconcatsingle("'%s'", expr, 2); 
      
        return result;
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
            buff = sconcat("%s, %s", str, buff, 2);
        }

        pfree(arrayList);
        pfree(ar);

        return sconcatsingle("[%s]", buff, 2);
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
%}

%union 
{
    MDBQuery                    *qu;
    expression                  *exp;
   
    Clause                      *cl;
    value                       *vl;
    leaf_value                  *lv;

    List                        *list;

    where_clause_value          *wcv;

    char                        *strval;
    int                          intval;
    double                       dubval;
    _array                      *arrval;
    _bool                        boolval;
    
    array_operator_type          aop_type;
    expression_operator_type     exop_type;
    value_operator_type          valop_type;

    operator_object             *oob;
    operator                    *op;
}

%type<qu>         QUERY
%type<exp>        EXPRESSION
%type<cl>         CLAUSE TEXT_CLAUSE EXPRESSION_TREE_CLAUSE LEAF_CLAUSE COMMENT_CLAUSE WHERE_CLAUSE
%type<vl>         VALUE 

%type<strval>     KEY 
%type<op>         OPERATOR
%type<oob>        OPEARATOR_OBJECT

%type<strval>     LSCOPE RSCOPE COMMA
    
%type<list>       OPERATOR_LIST LEAF_VALUE_LIST EXPRESSION_LIST CLAUSE_LIST

%type<wcv>        WHERE_CLAUSE_VALUE
%type<strval>     WHERE_OPERATOR
%token            WHERE_OPERATOR

/* OPERATORS */

/* Tree operator */
%type<exop_type>    TREE_OPERATOR OR NOR AND
%token              OR NOR AND

/* Leaf value operator */
 %type<valop_type>    EQ LESS GREAT LESSEQ GREATEQ NOTEQ TYPE __SIZE EXISTS NOT VALUE_OPERATOR
 %token               EQ NOTEQ LESS LESSEQ GREAT GREATEQ TYPE __SIZE EXISTS NOT

/* Array operator */
%type<aop_type>   __IN NIN ALL ARRAY_OPERATOR
%token            __IN NIN ALL

/* Mod operator */
%type<strval>     MOD_OPERATOR 
%type<lv>         DIVISOR REMAINDER
%token            MOD_OPERATOR

/* Comment clause operator */
%type<strval>     COMMENT_OPERATOR
%token            COMMENT_OPERATOR

/* Text clause operator */
%type<strval>     DIACRITIC_SENSITIVE_OPERATOR CASE_SENSITIVE_OPERATOR LANGUAGE_OPERATOR SEARCH_OPERATOR TEXT_OPERATOR
%token            DIACRITIC_SENSITIVE_OPERATOR CASE_SENSITIVE_OPERATOR LANGUAGE_OPERATOR SEARCH_OPERATOR TEXT_OPERATOR

/* Type of values */
%type<lv> LEAF_VALUE
%type<strval> _INT
%type<strval> STRING
%type<strval> __DOUBLE
%type<arrval> ARRAY
%type<boolval> __BOOLEAN    
%token _INT STRING __DOUBLE __BOOLEAN

/* Scope types */
%token LSCOPE RSCOPE COMMA LSQBRACKET RSQBRACKET LRBRACKET RRBRACKET



%start QUERY

%%

QUERY       : EXPRESSION {$$ = createQuery($1); RET=$$; }
            ;

EXPRESSION  : LSCOPE CLAUSE_LIST RSCOPE { $$ = createExpression($2); }
            ;

CLAUSE_LIST : CLAUSE COMMA CLAUSE_LIST  { $$ = addClause($1, $3); }
            | CLAUSE                    { $$ = lappend(NULL, $1); }
            ;

CLAUSE      : LEAF_CLAUSE             
            | COMMENT_CLAUSE         
            | WHERE_CLAUSE            
            | EXPRESSION_TREE_CLAUSE  
            | TEXT_CLAUSE             
            ;


/* TEXT CLAUSE SECTION */

TEXT_CLAUSE : LSCOPE TEXT_OPERATOR EQ LSCOPE SEARCH_OPERATOR EQ STRING RSCOPE RSCOPE { $$ = createTextClause($7, _false, "", _false, _false); }
            | LSCOPE TEXT_OPERATOR EQ LSCOPE SEARCH_OPERATOR EQ STRING COMMA
                LANGUAGE_OPERATOR EQ STRING COMMA
                CASE_SENSITIVE_OPERATOR EQ __BOOLEAN COMMA
                DIACRITIC_SENSITIVE_OPERATOR EQ __BOOLEAN RSCOPE RSCOPE                { $$ = createTextClause($7, _false, $11, $15, $19); }
            ;

/* END OF SECTION */

/*WHERE CLAUSE SECTION*/
                
WHERE_CLAUSE : LSCOPE WHERE_OPERATOR EQ LRBRACKET WHERE_CLAUSE_VALUE RRBRACKET RSCOPE { $$ = createWhereClause($2,$5); }
             ;

WHERE_CLAUSE_VALUE     : STRING { $$ = stringToWhereClauseValue($1); }
                       ;
/* END OF SECTION */   

/*COMMENT CLAUSE SECTION*/
COMMENT_CLAUSE         : LSCOPE COMMENT_OPERATOR EQ STRING RSCOPE { $$ = createCommentClause($2, $4); }
                       ;
/* END OF SECTION */

/*TREE CLAUSE SECTION*/

EXPRESSION_TREE_CLAUSE : TREE_OPERATOR EQ LSQBRACKET EXPRESSION_LIST RSQBRACKET { $$ = createExpressionTreeClause($1, $4); }
                       | LSCOPE EXPRESSION_TREE_CLAUSE RSCOPE                   { $$ = $2; }
                       ;

EXPRESSION_LIST        : EXPRESSION                       { $$ = lcons($1, NULL); }
                       | EXPRESSION COMMA EXPRESSION_LIST { $$ = addExpression($1, $3); }
                       ;

TREE_OPERATOR          : OR | AND | NOR ;

/* END OF SECTION */

/* LEAF CLAUSE SECTION */
LEAF_CLAUSE        : KEY EQ VALUE { $$ = createLeafClause($1, $3); }
                   ;

KEY                : STRING
                   ;

VALUE              : LEAF_VALUE       { $$ = createLeafValueValue($1); }
                   | OPEARATOR_OBJECT { $$ = createOperatorObjectValue($1); }
                   ;

OPEARATOR_OBJECT   : LSCOPE OPERATOR_LIST RSCOPE { $$ = createOperatorObject($2); }
                   ;

OPERATOR_LIST      : OPERATOR                     { $$ = lappend(NULL, $1); }
                   | OPERATOR COMMA OPERATOR_LIST { $$ = addOperator($1, $3); }
                   ;

OPERATOR           : VALUE_OPERATOR EQ LEAF_VALUE                                  { $$ = createValueOperator($1, $3); }
                   | ARRAY_OPERATOR EQ ARRAY                                       { $$ = createArrayOperator($1, $3); }
                   | MOD_OPERATOR EQ LSQBRACKET DIVISOR COMMA REMAINDER RSQBRACKET { $$ = createModOperator($4, $6); }
                   | NOT EQ LSCOPE OPERATOR RSCOPE                                 { $$ = createNotOperator($4); }
                   ;

VALUE_OPERATOR      : EQ | NOTEQ | LESS | LESSEQ | GREAT | GREATEQ | TYPE | __SIZE | EXISTS 
                    ;

DIVISOR             : LEAF_VALUE
                    ;

REMAINDER           : LEAF_VALUE
                    ;

ARRAY               : LSQBRACKET LEAF_VALUE_LIST RSQBRACKET {$$ = createNewArray($2); };

ARRAY_OPERATOR      : __IN | NIN | ALL
                    ;

LEAF_VALUE_LIST     : LEAF_VALUE                         { $$ = lcons($1, NULL); }
                    | LEAF_VALUE COMMA LEAF_VALUE_LIST   { $$ = addArrayElement($1, $3); }
                    ;

LEAF_VALUE          : _INT      { $$ = createIntegerValue($1); }
                    | STRING    { $$ = createStringValue($1); }
                    | __DOUBLE  { $$ = createDoubleValue($1); }
                    | ARRAY     { $$ = createArrayValue($1); }
                    | __BOOLEAN { $$ = createBooleanValue($1); }
                    ;

/* END OF SECTION */

%%


PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(mdbquery_in);
Datum
mdbquery_in(PG_FUNCTION_ARGS)
{
    char *input=PG_GETARG_CSTRING(0);
    YY_BUFFER_STATE buffer = yy_scan_string(input);
    
    yyparse();
    yy_delete_buffer(buffer);
       
    PG_RETURN_MDBQUERY(RET);
}

PG_FUNCTION_INFO_V1(mdbquery_q);
Datum
mdbquery_q(PG_FUNCTION_ARGS)
{
    char *input=PG_GETARG_CSTRING(0);
    YY_BUFFER_STATE buffer = yy_scan_string(input);
    
    yyparse();
    yy_delete_buffer(buffer);
       
    PG_RETURN_CSTRING(get_jsquery(RET));
}

PG_FUNCTION_INFO_V1(mdbquery_out);
Datum
mdbquery_out(PG_FUNCTION_ARGS)
{
    MDBQuery *input=PG_GETARG_MDBQUERY(0);
       
    PG_RETURN_CSTRING(get_jsquery(input));
}

PG_FUNCTION_INFO_V1(json_mdbquery_exec);
Datum
json_mdbquery_exec(PG_FUNCTION_ARGS)
{
    Jsonb           *jb = PG_GETARG_JSONB(0);
    MDBQuery        *mq = PG_GETARG_MDBQUERY(1);

    PG_FREE_IF_COPY(jb, 0);
    PG_FREE_IF_COPY(mq, 1);

    PG_RETURN_BOOL(true);
}

PG_FUNCTION_INFO_V1(mdbquery_json_exec);
Datum
mdbquery_json_exec(PG_FUNCTION_ARGS)
{
    MDBQuery        *mq = PG_GETARG_MDBQUERY(0);
    Jsonb           *jb = PG_GETARG_JSONB(1);

    PG_FREE_IF_COPY(mq, 0);
    PG_FREE_IF_COPY(jb, 1);

    PG_RETURN_BOOL(false);
}

int yywrap(void){ return 0; }
