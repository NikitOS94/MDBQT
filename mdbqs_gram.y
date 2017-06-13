%{
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include "postgres.h"
    #include "fmgr.h"
    #include "structures.h"
    #include "get_query.h"

    #include "utils/builtins.h"


    char *RET;

    typedef struct yy_buffer_state * YY_BUFFER_STATE;
    extern int yyparse();
    extern YY_BUFFER_STATE yy_scan_string(char * str);
    extern void yy_delete_buffer(YY_BUFFER_STATE buffer);

    extern char *get_leaf_value(leaf_value * value);

    void yyerror(char *s) { 
    //fprintf (stderr, "%s\n", s); 
    exit(0);
    }

    void nSError(char *s) { //fprintf (stderr, "\n%s not supported by jsquery \n", s); 
    exit(0);
    }
    
    _array *
    createArray(array_element *first_ae) 
    {
        _array *new_ar = (_array *) malloc(sizeof(_array));
        new_ar->first_ae = first_ae;
        return new_ar;
    }

    array_element *
    createArrayElement(leaf_value * value, array_element *next_ae) 
    {
        array_element *new_ae=(array_element *) malloc(sizeof(array_element));
        new_ae->value = value;
        new_ae->next_ae = next_ae;
        return new_ae;
    }

    operator *
    createNotOperator(operator *op) 
    {
        not_operator *new_op = (not_operator *) malloc(sizeof(operator));
        new_op->type = NOP;
        new_op->op = op;
        return (operator*) new_op;
    }

    operator *
    createModOperator(leaf_value *divisor, leaf_value *remainder) 
    {
        mod_operator *new_op = (mod_operator *) malloc(sizeof(mod_operator));
        new_op->type = MOP;
        new_op->divisor = divisor;
        new_op->remainder = remainder;
        return (operator*) new_op;
    }

    operator *
    createArrayOperator(array_operator_type op, _array *ar) 
    {
        array_operator *new_op = (array_operator *) malloc(sizeof(array_operator));
        new_op->type = AOP;
        new_op->array_op = op;
        new_op->ar = ar;
        return (operator*) new_op;
    }

    operator *
    createValueOperator(value_operator_type op, leaf_value * value) 
    {
        value_operator *new_op = (value_operator *) malloc(sizeof(value_operator));
        new_op->type = VOP;  
        new_op->value_op = op;
        new_op->value = value;
        return (operator*) new_op;
    }

    leaf_value *
    createStringValue(char *str)
    {
        leaf_value *lv = (leaf_value *) malloc(sizeof(leaf_value));
        lv->type = S;
        lv->str = str;
        return lv;
    }

    leaf_value *
    createDoubleValue(char* d)
    {
        leaf_value *lv = (leaf_value *) malloc(sizeof(leaf_value));
        lv->type = D;
        lv->d = d;
        return lv;
    }

    leaf_value *
    createIntegerValue(char* i)
    {
        leaf_value *lv = (leaf_value *) malloc(sizeof(leaf_value));
        lv->type = I;
        lv->i = i;
        return lv;
    }

    leaf_value *
    createArrayValue(_array *ar)
    {
      leaf_value *lv = (leaf_value *) malloc(sizeof(leaf_value));
      lv->type = A;
      lv->ar = ar;
      return lv;
    }

    leaf_value *
    createBooleanValue(_bool b)
    {
      leaf_value *lv = (leaf_value *) malloc(sizeof(leaf_value));
      lv->type = B;
      lv->b = b;
      return lv;
    }

    operator_list *
    createOperatorList(operator *op, struct operator_list *ol) 
    {
        operator_list *new_ol = (operator_list *) malloc(sizeof(operator_list));
        new_ol->op = op;
        new_ol->next_op = ol;      
        return new_ol;
    }

    operator_object *
    createOperatorObject(operator_list *ol) 
    {
        operator_object *new_oob = (operator_object *) malloc(sizeof(operator_object));
        new_oob->ol = ol;
        return new_oob;
    }

    value *
    createOperatorObjectValue(operator_object *oob) 
    {
        value *vl = (value *) malloc(sizeof(value));
        vl->type = OP_OBJECT;
        vl->oob = oob;
        return vl;
    }

    value *
    createLeafValueValue(leaf_value *lv) 
    {
        value *vl = (value *) malloc(sizeof(value));
        vl->type = LF_VALUE;
        vl->lv = lv;
        return vl;
    }

    clause *
    createLeafClause(char* key, value *vl) 
    {
        leaf_clause *new_lc = (leaf_clause *) malloc(sizeof(leaf_clause));
        new_lc->type = LEAF;
        new_lc->key = key;
        new_lc->vl = vl;
        return ( clause* ) new_lc;
    }

    clause *
    createCommentClause(char *op, char *str) 
    {
        comment_clause *new_com_cl = (comment_clause *) malloc(sizeof(comment_clause));
        new_com_cl->type = COMMENT;
        new_com_cl->op = op;
        new_com_cl->str = str;
        return ( clause* ) new_com_cl;
    }

    where_clause_value *
    stringToWhereClauseValue(char *str)
    {
        where_clause_value *wcv = (where_clause_value *) malloc(sizeof(where_clause_value));
        wcv->str = str;   
        return wcv;
    }

    clause *
    createWhereClause(char *op, where_clause_value *wcv)
    {
        where_clause *wc = (where_clause *) malloc(sizeof(where_clause));
        wc->type = WHERE;
        wc->op = op;
        wc->wcv = wcv;
        return (clause *) wc;
    }

    clause_list *
    createClauseList(clause *cl,clause_list *next_cll)
    {
        clause_list *cll = (clause_list *) malloc(sizeof(clause_list));
        cll->cl = cl;
        cll->next_cll = next_cll;
        return cll;
    }

    expression *
    createExpression(clause_list *cll)
    {
        expression *exp = (expression *) malloc(sizeof(expression));
        exp->cll = cll;
        return exp;
    }

    expression_list *
    createExpressionList(expression *exp, expression_list *next_exp)
    {
        expression_list *exp_list = (expression_list *) malloc(sizeof(expression_list));
        exp_list->exp = exp;
        exp_list->next_exp = next_exp;
        return exp_list;
    }

    clause *
    createExpressionTreeClause(expression_operator_type op, expression_list *exp)
    {
        expression_clause *exp_cl = (expression_clause *) malloc(sizeof(expression_clause));
        exp_cl->type = EXPRESSION;
        exp_cl->op = op;
        exp_cl->exp = exp;
        return (clause *) exp_cl;
    }

    clause *
    createTextClause(char* search_str, _bool lang_op, char* lang_str, _bool case_sense, _bool diacr_sense)
    {
        text_clause *text_cl = (text_clause *) malloc(sizeof(text_clause));
        text_cl->type = TEXT;
        text_cl->search_str = search_str;
        text_cl->lang_op = lang_op;
        text_cl->lang_str = lang_str;
        text_cl->case_sense = case_sense;
        text_cl->diacr_sense = diacr_sense;
        return (clause *) text_cl;
    }

    Query *
    createQuery(expression *exp)
    {
        Query *qu = (Query *) malloc(sizeof(Query));
        qu->exp = exp;
        return qu;
    }

    char* sconcat(char *form, char *s1, char *s2, int plus) 
    {

        size_t len1 = strlen(s1);
        size_t len2 = strlen(s2);                      

        char *result = malloc(len1 + len2 + 1 + plus);

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

        char *result = malloc(len1 + len2 + len3 + 1 + plus);

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

        char *result = malloc(len1 + 1 + plus);

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
            char *result = sconcat("%s %s", key, get_value_type(value), 1);
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
        free(vop);
   
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

        free(op);
        free(oper);

        return result;
    }

    char *
    get_operator_list(char *key, operator_list *op_list)
    {
        char *result = get_operator(key, op_list->op);
        op_list=op_list->next_op;

        if(op_list) result = sconcatsingle("(%s)", result, 2);

        while(op_list)
        {
            char *oprtr = get_operator(key, op_list->op);
            result = sconcat("%s AND (%s)", result, oprtr, 7);

            free(oprtr);

            op_list=op_list->next_op;
        }

        free(key);
        free(op_list);

        return result;
    }

    char *
    get_operator_object(char *key, operator_object *op_object)
    {
        return get_operator_list(key, op_object->ol);
    }
    
    char*
    get_leaf_value_eq(char *key, leaf_value *lv)
    {
        char *result = sconcat("%s = %s", key, get_leaf_value(lv), 3);
        free(lv);
        free(key);

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
        return result;
    }

    char *
    get_expression_list(expression_operator_type exp_op, expression_list* exp_list)
    {         
        char   *result = sconcatsingle("(%s)", get_expression(exp_list->exp), 2);
        char   *oprtr = get_expression_operator(exp_op);

        exp_list = exp_list->next_exp;

        while(exp_list)
        {
            char *exprssn = get_expression(exp_list->exp);
            result = sconcat3("%s %s (%s)", result, oprtr, exprssn, 4);
            free(exprssn);
            exp_list = exp_list->next_exp;
        }

        free(exp_list);

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
        return get_expression_list(exp_clause->op, exp_clause->exp);
    }

    char *
    get_text_clause(text_clause* t_clause)
    {
        char   *result = sconcatsingle("* = %s", t_clause->search_str, 4);
        free(t_clause);

        return result;
    }

    char *
    get_clause(clause *cl)
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
    get_clause_list(clause_list *cll)
    {
        char *result = get_clause(cll->cl);
        cll=cll->next_cll;

        while(cll)
        {
            char *cls = get_clause(cll->cl);
            result = sconcat("%s AND %s", result, cls, 5);
            cll=cll->next_cll;
        }

        return result;
    }

    char *
    get_expression(expression * ex)
    {
        char *result = get_clause_list(ex->cll);
        return result;
       
    }

    char *
    get_jsquery(Query *qu)
    {
        char   *expr=get_expression(qu->exp);
        char   *result= sconcatsingle("'%s'", expr, 2); 

        free(expr);

      
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
    get_array_element(array_element *ae)
    {
        char *str = get_leaf_value(ae->value);
        ae = ae->next_ae;   

        while(ae)
        {
            char *ar_element = get_leaf_value(ae->value);
            str=sconcat("%s, %s",str, ar_element,2);

            free(ar_element);
            ae = ae->next_ae;
        }

        printf("%s\n", str);
        return str;
    }

    char *
    get_array(_array *ar)
    { 
        char *ar_elements = get_array_element(ar->first_ae);
        char *result = sconcatsingle("[%s]", ar_elements, 2);

        free(ar_elements);
        free(ar);

        return result;
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

        free(ar);
        free(aop); 

        return result;    
    }



%}

%union {

    Query             *qu;
    expression        *exp;
    clause_list       *cll;
    clause            *cl;
    expression_list   *exp_list;
    value             *vl;
    leaf_value        *lv;

    where_clause_value *wcv;

    char *            strval;
    int               intval;
    double            dubval;
    _array            *arrval;
    _bool              boolval;
    
    array_operator_type         aop_type;
    expression_operator_type    exop_type;
    value_operator_type         valop_type;

    operator_object   *oob;
    operator_list     *ol;
    operator          *op;

    array_element     *ae;
}

%type<qu>         QUERY
%type<exp>        EXPRESSION
%type<cll>        CLAUSE_LIST
%type<cl>         CLAUSE TEXT_CLAUSE EXPRESSION_TREE_CLAUSE LEAF_CLAUSE COMMENT_CLAUSE WHERE_CLAUSE
%type<vl>         VALUE

%type<exp_list>   EXPRESSION_LIST

%type<strval>     KEY 
%type<op>         OPERATOR
%type<oob>        OPEARATOR_OBJECT
%type<ol>         OPERATOR_LIST

%type<strval>     LSCOPE RSCOPE COMMA
    
%type<ae>         LEAF_VALUE_LIST

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

QUERY       : EXPRESSION {$$ = createQuery($1); RET=get_jsquery($$); }
            ;

EXPRESSION  : LSCOPE CLAUSE_LIST RSCOPE { $$ = createExpression($2); }
            ;

CLAUSE_LIST : CLAUSE COMMA CLAUSE_LIST  { $$ = createClauseList($1, $3); }
            | CLAUSE                    { $$ = createClauseList($1, NULL); }
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

EXPRESSION_LIST        : EXPRESSION                       { $$ = createExpressionList( $1, NULL ); }
                       | EXPRESSION COMMA EXPRESSION_LIST { $$ = createExpressionList( $1, $3 ); }
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

OPERATOR_LIST      : OPERATOR                     { $$ = createOperatorList($1, NULL); }
                   | OPERATOR COMMA OPERATOR_LIST { $$ = createOperatorList($1, $3); }
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

ARRAY               : LSQBRACKET LEAF_VALUE_LIST RSQBRACKET {$$ = createArray($2); };

ARRAY_OPERATOR      : __IN | NIN | ALL
                    ;

LEAF_VALUE_LIST     : LEAF_VALUE                         { $$ = createArrayElement($1, NULL); }
                    | LEAF_VALUE COMMA LEAF_VALUE_LIST   { $$ = createArrayElement($1, $3); }
                    ;

LEAF_VALUE          : _INT     { $$ = createIntegerValue($1); }
                    | STRING  { $$ = createStringValue($1); }
                    | __DOUBLE  { $$ = createDoubleValue($1); }
                    | ARRAY   { $$ = createArrayValue($1); }
                    | __BOOLEAN { $$ = createBooleanValue($1); }
                    ;

/* END OF SECTION */

%%


    PG_MODULE_MAGIC;

    PG_FUNCTION_INFO_V1(start_parse2);
    Datum
    start_parse2(PG_FUNCTION_ARGS)
    {
    char *input=PG_GETARG_CSTRING(0);
    YY_BUFFER_STATE buffer = yy_scan_string(input);
    yyparse();
    yy_delete_buffer(buffer);
       
       PG_RETURN_TEXT_P(cstring_to_text(RET));
    }





int yywrap(void){ return 0; }