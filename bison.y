%{
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include "structures.h"
    #include "get_query.h"

    void yyerror(char *s) { fprintf (stderr, "%s\n", s); exit(0);}

    void ns_error(char *s) { fprintf (stderr, "\n%s not supported by jsquery \n", s); exit(0);}
    
    _array *
    create_array(array_element *first_ae) 
    {
        _array *new_ar = (_array *) malloc(sizeof(_array));
        new_ar->first_ae = first_ae;
        return new_ar;
    }

    array_element *
    create_array_element(leaf_value * value, array_element *next_ae) 
    {
        array_element *new_ae=(array_element *) malloc(sizeof(array_element));
        new_ae->value = value;
        new_ae->next_ae = next_ae;
        return new_ae;
    }

    operator *
    create_not_operator(operator *op) 
    {
        not_operator *new_op = (not_operator *) malloc(sizeof(operator));
        new_op->type = NOP;
        new_op->op = op;
        return (operator*) new_op;
    }

    operator *
    create_mod_operator(leaf_value *divisor, leaf_value *remainder) 
    {
        mod_operator *new_op = (mod_operator *) malloc(sizeof(mod_operator));
        new_op->type = MOP;
        new_op->divisor = divisor;
        new_op->remainder = remainder;
        return (operator*) new_op;
    }

    operator *
    create_array_operator(array_operator_type op, _array *ar) 
    {
        array_operator *new_op = (array_operator *) malloc(sizeof(array_operator));
        new_op->type = AOP;
        new_op->array_op = op;
        new_op->ar = ar;
        return (operator*) new_op;
    }

    operator *
    create_value_operator(value_operator_type op, leaf_value * value) 
    {
        value_operator *new_op = (value_operator *) malloc(sizeof(value_operator));
        new_op->type = VOP;  
        new_op->value_op = op;
        new_op->value = value;
        return (operator*) new_op;
    }

    leaf_value *
    create_string_value(char *str)
    {
        leaf_value *lv = (leaf_value *) malloc(sizeof(leaf_value));
        lv->type = S;
        lv->str = str;
        return lv;
    }

    leaf_value *
    create_double_value(char* d)
    {
        leaf_value *lv = (leaf_value *) malloc(sizeof(leaf_value));
        lv->type = D;
        lv->d = d;
        return lv;
    }

    leaf_value *
    create_integer_value(char* i)
    {
        leaf_value *lv = (leaf_value *) malloc(sizeof(leaf_value));
        lv->type = I;
        lv->i = i;
        return lv;
    }

    leaf_value *
    create_array_value(_array *ar)
    {
      leaf_value *lv = (leaf_value *) malloc(sizeof(leaf_value));
      lv->type = A;
      lv->ar = ar;
      return lv;
    }

    leaf_value *
    create_boolean_value(bool b)
    {
      leaf_value *lv = (leaf_value *) malloc(sizeof(leaf_value));
      lv->type = B;
      lv->b = b;
      return lv;
    }

    operator_list *
    create_operator_list(operator *op, struct operator_list *ol) 
    {
        operator_list *new_ol = (operator_list *) malloc(sizeof(operator_list));
        new_ol->op = op;
        new_ol->next_op = ol;      
        return new_ol;
    }

    operator_object *
    create_operator_object(operator_list *ol) 
    {
        operator_object *new_oob = (operator_object *) malloc(sizeof(operator_object));
        new_oob->ol = ol;
        return new_oob;
    }

    value *
    create_operator_object_value(operator_object *oob) 
    {
        value *vl = (value *) malloc(sizeof(value));
        vl->type = OP_OBJECT;
        vl->oob = oob;
        return vl;
    }

    value *
    create_leaf_value_value(leaf_value *lv) 
    {
        value *vl = (value *) malloc(sizeof(value));
        vl->type = LF_VALUE;
        vl->lv = lv;
        return vl;
    }

    clause *
    create_leaf_clause(char* key, value *vl) 
    {
        leaf_clause *new_lc = (leaf_clause *) malloc(sizeof(leaf_clause));
        new_lc->type = LEAF;
        new_lc->key = key;
        new_lc->vl = vl;
        return ( clause* ) new_lc;
    }

    clause *
    create_comment_clause(char *op, char *str) 
    {
        comment_clause *new_com_cl = (comment_clause *) malloc(sizeof(comment_clause));
        new_com_cl->type = COMMENT;
        new_com_cl->op = op;
        new_com_cl->str = str;
        return ( clause* ) new_com_cl;
    }

    where_clause_value *
    string_to_where_clause_value(char *str)
    {
        where_clause_value *wcv = (where_clause_value *) malloc(sizeof(where_clause_value));
        wcv->str = str;   
        return wcv;
    }

    clause *
    create_where_clause(char *op, where_clause_value *wcv)
    {
        where_clause *wc = (where_clause *) malloc(sizeof(where_clause));
        wc->type = WHERE;
        wc->op = op;
        wc->wcv = wcv;
        return (clause *) wc;
    }

    clause_list *
    create_clause_list(clause *cl,clause_list *next_cll)
    {
        clause_list *cll = (clause_list *) malloc(sizeof(clause_list));
        cll->cl = cl;
        cll->next_cll = next_cll;
        return cll;
    }

    expression *
    create_expression(clause_list *cll)
    {
        expression *exp = (expression *) malloc(sizeof(expression));
        exp->cll = cll;
        return exp;
    }

    expression_list *
    create_expression_list(expression *exp, expression_list *next_exp)
    {
        expression_list *exp_list = (expression_list *) malloc(sizeof(expression_list));
        exp_list->exp = exp;
        exp_list->next_exp = next_exp;
        return exp_list;
    }

    clause *
    create_expression_tree_clause(expression_operator_type op, expression_list *exp)
    {
        expression_clause *exp_cl = (expression_clause *) malloc(sizeof(expression_clause));
        exp_cl->type = EXPRESSION;
        exp_cl->op = op;
        exp_cl->exp = exp;
        return (clause *) exp_cl;
    }

    clause *
    create_text_clause(char* search_str, bool lang_op, char* lang_str,bool case_sense, bool diacr_sense)
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

    query *
    create_query(expression *exp)
    {
        query *qu = (query *) malloc(sizeof(query));
        qu->exp = exp;
        return qu;
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
        else                                                  ns_error(value_type);
    }

    char *
    get_value_operator(char *key, value_operator *vop)
    {
        char *result;
        char *opr = get_value_operator_type(vop->value_op);

        if(vop->value_op == _EXISTS)
        {
            if(vop->value->b)
            {   
                size_t length = 1+ strlen(key)+strlen(opr)+1;
                result = (char *) malloc(sizeof(*result) * length);
                sprintf(result,"%s %s",key,opr);
            }
            else
            {
                size_t length = 1+ strlen(key)+strlen(opr)+7;
                result = (char *) malloc(sizeof(*result) * length);
                sprintf(result,"NOT (%s %s)",key,opr);
            }

            free(vop);
            return result;
        }

        char *value = get_leaf_value(vop->value);

        if(vop->value_op == _TYPE)
        {
            char *value_type = get_value_type(value);
            size_t length = strlen(key)+strlen(value_type)+1;
            result = (char *) malloc(sizeof(*result) * length);

            sprintf(result,"%s %s", key, value_type);
            free(value_type);
            free(vop);
            return result;
        }

        if(vop->value_op == _NOTEQ)
        {
            size_t length = 8+strlen(key)+strlen(opr)+strlen(value);
            char *result = (char*) malloc(sizeof(*result) * length);

            sprintf(result,"NOT (%s %s %s)", key, opr, value);
            free(vop);
            free(value);
            return result;
       }

        size_t length=strlen(key)+strlen(opr)+strlen(value)+2;
        result = (char *) malloc(sizeof(*result) * length);

        sprintf(result,"%s %s %s", key, opr, value);
        free(value);
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
                ns_error("Module operator not suppported by jsquery"); //not supported by jsquery
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
        size_t length = 1+ strlen(oper) + 6;
        char *result = (char *) malloc(sizeof(*result) * length);

        sprintf(result, "NOT (%s)",oper);
        free(op);
        free(oper);
        return result;
    }

    void copy_string(char *target, char *source) 
    {
       while (*source) {
          *target = *source;
          source++;
          target++;
       }
       *target = '\0';
    }

    char *
    get_operator_list(char *key, operator_list *op_list)
    {
        char *result=get_operator(key, op_list->op);
        op_list=op_list->next_op;
        while(op_list)
        {
            char *op = get_operator(key, op_list->op);
            result=realloc(result,sizeof(char)*(strlen(result)+strlen(op)));
            strcat(result,op);
            free(op);
            op_list=op_list->next_op;
        }

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
        char *leaf_val = get_leaf_value(lv);
        size_t length = strlen(key) + 3 + strlen(leaf_val);
        char *result = (char *) malloc(sizeof(*result) * length);

        sprintf(result,"%s = %s",key,leaf_val);
        free(key);
        free(leaf_val);

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
        printf("%s\n", result);
        return result;
    }

    char *
    get_expression_list(expression_operator_type exp_op, expression_list* exp_list)
    {         
        char   *exp = get_expression(exp_list->exp);

        if(exp_list->next_exp != NULL)
        {
            char   *next_exp = get_expression_list(exp_op, exp_list->next_exp);
            char   *op = get_expression_operator(exp_op);
            size_t  length = 4+strlen(exp)+strlen(op)+strlen(next_exp);
            char   *result = (char *) malloc(sizeof(*result) * length);

            sprintf(result,"(%s) %s %s",exp,op,next_exp);
            free(next_exp);
            free(exp);

            return result;
        }

        return exp; 
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
        char   *str=t_clause->search_str;
        size_t  length=4+strlen(str);
        char   *result = (char *) malloc(sizeof(*result) * length);

        sprintf(result,"* = %s",str);
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
                ns_error("COMMENT clause");  //Not supported by jsquery
            case TEXT :
                return get_text_clause((text_clause*) cl);
            case WHERE :
                ns_error("WHERE clause");  //Not supported by jsquery
            case EXPRESSION :
                return get_expression_clause((expression_clause*) cl);
        }
    }

    char *
    get_clause_list(clause_list *cll)
    {
        char *cl = get_clause(cll->cl);
        if(cll->next_cll != NULL)
        {
            char   *cl_list = get_clause_list(cll->next_cll);
            size_t  length=strlen(cl)+5+strlen(cl_list);
            char   *result = (char*) malloc(sizeof(*result) * length);

            sprintf(result,"%s AND %s",cl,cl_list);
            free(cl);
            free(cl_list);

            return result;
        }

        return cl;
    }

    char *
    get_expression(expression * ex)
    {
        char *result = get_clause_list(ex->cll);
        return result;
       
    }

    char *
    get_jsquery(query *qu)
    {
        char   *expr=get_expression(qu->exp);
        size_t  length=2+strlen(expr);

        char   *result= malloc(sizeof(*result) * length);

        sprintf(result,"'%s'",expr); 
        free(expr);

        printf("%s\n", result);
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
                val = (value->b==false ? "false" : "true");
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
        if(ae->next_ae == NULL)
            return get_leaf_value(ae->value);
        else
        {
            char   *ar_el = get_leaf_value(ae->value);
            char   *next_ar_el = get_array_element(ae->next_ae);
            size_t  length=2+strlen(ar_el)+strlen(next_ar_el);
            char   *result = (char *) malloc(sizeof(*result) * length);

            sprintf(result,"%s, %s",ar_el,next_ar_el);
            return result;
        }
    }

    char *
    get_array(_array * ar)
    { 
        char* ar_elements = get_array_element(ar->first_ae);
        size_t length=2+strlen(ar_elements);
        char* result = (char *) malloc(sizeof(*result) * length);
        sprintf(result,"[%s]",ar_elements);
        free(ar_elements);
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
        char *ar_operator = get_array_operator_type(aop->array_op);
        char *result;

        if(aop->array_op == _NIN)
        {
            size_t length=8+strlen(key)+strlen(ar_operator)+strlen(ar);
            result = (char *) malloc(sizeof(*result) * length);
            sprintf(result,"NOT (%s %s %s)", key, ar_operator, ar);
            free(ar);
            free(ar_operator);
            free(aop);
            printf("%s\n1", result);
            return result;
        }

        size_t length=2+strlen(key)+strlen(ar_operator)+strlen(ar);
        result = (char *) malloc(sizeof(*result) * length);
        sprintf(result,"%s %s %s",key, ar_operator, ar);
        free(ar);
        free(ar_operator);
        free(aop); 
        return result;    
    }



%}

%union {

    query             *qu;
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
    bool              boolval;
    
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
 %type<valop_type>    EQ LESS GREAT LESSEQ GREATEQ NOTEQ TYPE SIZE EXISTS NOT VALUE_OPERATOR
 %token               EQ NOTEQ LESS LESSEQ GREAT GREATEQ TYPE SIZE EXISTS NOT

/* Array operator */
%type<aop_type>   IN NIN ALL ARRAY_OPERATOR
%token            IN NIN ALL

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
%type<strval> INT
%type<strval> STRING
%type<strval> DOUBLE
%type<arrval> ARRAY
%type<boolval> BOOLEAN    
%token INT STRING DOUBLE BOOLEAN

/* Scope types */
%token LSCOPE RSCOPE COMMA LSQBRACKET RSQBRACKET LRBRACKET RRBRACKET



%start QUERY

%%

QUERY       : EXPRESSION {$$ = create_query($1); char *result=get_jsquery($$); exit(0); }
            ;

EXPRESSION  : LSCOPE CLAUSE_LIST RSCOPE { $$ = create_expression($2); }
            ;

CLAUSE_LIST : CLAUSE COMMA CLAUSE_LIST  { $$ = create_clause_list($1, $3); }
            | CLAUSE                    { $$ = create_clause_list($1, NULL); }
            ;

CLAUSE      : LEAF_CLAUSE             
            | COMMENT_CLAUSE         
            | WHERE_CLAUSE            
            | EXPRESSION_TREE_CLAUSE  
            | TEXT_CLAUSE             
            ;


/* TEXT CLAUSE SECTION */

TEXT_CLAUSE : LSCOPE TEXT_OPERATOR EQ LSCOPE SEARCH_OPERATOR EQ STRING RSCOPE RSCOPE { $$ = create_text_clause($7, false, "", false, false); }
            | LSCOPE TEXT_OPERATOR EQ LSCOPE SEARCH_OPERATOR EQ STRING COMMA
                LANGUAGE_OPERATOR EQ STRING COMMA
                CASE_SENSITIVE_OPERATOR EQ BOOLEAN COMMA
                DIACRITIC_SENSITIVE_OPERATOR EQ BOOLEAN RSCOPE RSCOPE                { $$ = create_text_clause($7, false, $11, $15, $19); }
            ;

/* END OF SECTION */

/*WHERE CLAUSE SECTION*/
                
WHERE_CLAUSE : LSCOPE WHERE_OPERATOR EQ LRBRACKET WHERE_CLAUSE_VALUE RRBRACKET RSCOPE { $$ = create_where_clause($2,$5); }
             ;

WHERE_CLAUSE_VALUE     : STRING { $$ = string_to_where_clause_value($1); }
                       ;
/* END OF SECTION */   

/*COMMENT CLAUSE SECTION*/
COMMENT_CLAUSE         : LSCOPE COMMENT_OPERATOR EQ STRING RSCOPE { $$ = create_comment_clause($2, $4); }
                       ;
/* END OF SECTION */

/*TREE CLAUSE SECTION*/

EXPRESSION_TREE_CLAUSE : TREE_OPERATOR EQ LSQBRACKET EXPRESSION_LIST RSQBRACKET { $$ = create_expression_tree_clause($1, $4); }
                       | LSCOPE EXPRESSION_TREE_CLAUSE RSCOPE                   { $$ = $2; }
                       ;

EXPRESSION_LIST        : EXPRESSION                       { $$ = create_expression_list( $1, NULL ); }
                       | EXPRESSION COMMA EXPRESSION_LIST { $$ = create_expression_list( $1, $3 ); }
                       ;

TREE_OPERATOR          : OR | AND | NOR ;

/* END OF SECTION */

/* LEAF CLAUSE SECTION */
LEAF_CLAUSE        : KEY EQ VALUE { $$ = create_leaf_clause($1, $3); }
                   ;

KEY                : STRING
                   ;

VALUE              : LEAF_VALUE       { $$ = create_leaf_value_value($1); }
                   | OPEARATOR_OBJECT { $$ = create_operator_object_value($1); }
                   ;

OPEARATOR_OBJECT   : LSCOPE OPERATOR_LIST RSCOPE { $$ = create_operator_object($2); }
                   ;

OPERATOR_LIST      : OPERATOR                     { $$ = create_operator_list($1, NULL); }
                   | OPERATOR COMMA OPERATOR_LIST { $$ = create_operator_list($1, $3); }
                   ;

OPERATOR           : VALUE_OPERATOR EQ LEAF_VALUE                                  { $$ = create_value_operator($1, $3); }
                   | ARRAY_OPERATOR EQ ARRAY                                       { $$ = create_array_operator($1, $3); }
                   | MOD_OPERATOR EQ LSQBRACKET DIVISOR COMMA REMAINDER RSQBRACKET { $$ = create_mod_operator($4, $6); }
                   | NOT EQ LSCOPE OPERATOR RSCOPE                                 { $$ = create_not_operator($4); }
                   ;

VALUE_OPERATOR      : EQ | NOTEQ | LESS | LESSEQ | GREAT | GREATEQ | TYPE | SIZE | EXISTS 
                    ;

DIVISOR             : LEAF_VALUE
                    ;

REMAINDER           : LEAF_VALUE
                    ;

ARRAY               : LSQBRACKET LEAF_VALUE_LIST RSQBRACKET {$$ = create_array($2); };

ARRAY_OPERATOR      : IN | NIN | ALL
                    ;

LEAF_VALUE_LIST     : LEAF_VALUE                         { $$ = create_array_element($1, NULL); }
                    | LEAF_VALUE COMMA LEAF_VALUE_LIST   { $$ = create_array_element($1, $3); }
                    ;

LEAF_VALUE          : INT     { $$ = create_integer_value($1); }
                    | STRING  { $$ = create_string_value($1); }
                    | DOUBLE  { $$ = create_double_value($1); }
                    | ARRAY   { $$ = create_array_value($1); }
                    | BOOLEAN { $$ = create_boolean_value($1); }
                    ;

/* END OF SECTION */

%%

int main () { yydebug=1; yyparse(); return 0;}

int yywrap(void){ return 0; }