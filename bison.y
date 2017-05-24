%{
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include "structures.h"

    void yyerror(char *s) { fprintf (stderr, "%s\n", s);}

    _array *create_array(array_element *first_ae) {
        _array *new_ar=malloc(sizeof(_array));
        new_ar->first_ae=first_ae;
        return new_ar;
    }

    array_element *create_array_element(leaf_value * value, array_element *next_ae) {
        array_element *new_ae=malloc(sizeof(array_element));
        new_ae->value=value;
        new_ae->next_ae=next_ae;
        return new_ae;
    }

    operator *create_not_operator(operator *op) {
        operator *new_op=malloc(sizeof(operator));
        not_operator *nop=malloc(sizeof(operator));
        nop->op=op;

        new_op->type=NOP;
        new_op->nop=nop;

        return new_op;
    }

    operator *create_mod_operator(leaf_value *divisor, leaf_value *remainder) {
        operator *new_op=malloc(sizeof(operator));
        mod_operator *mop=malloc(sizeof(mod_operator));
        mop->divisor=divisor;
        mop->remainder=remainder;
        new_op->type=MOP;
        new_op->mop=mop;

        return new_op;
    }

    operator *create_array_operator(char* op, _array *ar) {
        operator *new_op=malloc(sizeof(operator));

        array_operator *aop=malloc(sizeof(array_operator));
        aop->array_op=op;
        aop->ar=ar;

        new_op->type=AOP;
        new_op->aop=aop;

        return new_op;
    }

    operator *create_value_operator(char* op, leaf_value * value) {
        operator *new_op=malloc(sizeof(operator));
        value_operator *vop=malloc(sizeof(value_operator));
        vop->value_op=op;
        vop->value=value;

        new_op->type=VOP;
        new_op->vop=vop;
       
        return new_op;
    }

    leaf_value *create_string_value(char *str){
      leaf_value *lv=malloc(sizeof(leaf_value));
      lv->type=S;
      lv->str=str;
      return lv;
    }

    leaf_value *create_double_value(float d){
      leaf_value *lv=malloc(sizeof(leaf_value));
      lv->type=D;
      lv->d=d;
      return lv;
    }

    leaf_value *create_integer_value(int i){
      leaf_value *lv=malloc(sizeof(leaf_value));
      lv->type=I;
      lv->i=i;
      return lv;
    }

    leaf_value *create_array_value(_array *ar){
      leaf_value *lv=malloc(sizeof(leaf_value));
      lv->type=A;
      lv->ar=ar;
      return lv;
    }

    leaf_value *create_boolean_value(bool b){
      leaf_value *lv=malloc(sizeof(leaf_value));
      lv->type=B;
      lv->b=b;
      return lv;
    }

    operator_list *create_operator_list(operator *op, struct operator_list *ol) {
        
        operator_list *new_ol=malloc(sizeof(operator_list));
        new_ol->op=op;
        new_ol->next_op=ol;      
        return new_ol;
    }

    operator_object *create_operator_object(operator_list *ol) {
        
        operator_object *new_oob=malloc(sizeof(operator_object));
        new_oob->ol=ol;
        return new_oob;
    }

    value *create_operator_object_value(operator_object *oob) {
        value *vl=malloc(sizeof(value));
        vl->type=OP_OBJECT;
        vl->oob=oob;
        return vl;
    }

    value *create_leaf_value_value(leaf_value *lv) {
        value *vl=malloc(sizeof(value));
        vl->type=LF_VALUE;
        vl->lv=lv;
        return vl;
    }

    leaf_clause *create_leaf_clause(char* key, value *vl) {
        
        leaf_clause *new_lc=malloc(sizeof(leaf_clause));
        new_lc->key=key;
        new_lc->vl=vl;
        return new_lc;
    }

    comment_clause *create_comment_clause(char *op, char *str) {
        
        comment_clause *new_com_cl=malloc(sizeof(comment_clause));
        new_com_cl->op=op;
        new_com_cl->str=str;
        return new_com_cl;
    }

    clause *leaf_clause_to_clause(leaf_clause *leaf_cl){
      
      clause *clse=malloc(sizeof(clause));
      clse->type=LEAF;
      clse->leaf_cl=leaf_cl;
     
      return clse;
    }

    clause *comment_clause_to_clause(comment_clause *comm_clause){
      
      clause *clse=malloc(sizeof(clause));
      clse->type=COMMENT;
      clse->comm_clause=comm_clause;
     
      return clse;
    }

    where_clause_value *string_to_where_clause_value(char *str){
      
        where_clause_value *wcv=malloc(sizeof(where_clause_value));
        wcv->str=str;   
        return wcv;
    }

    where_clause *create_where_clause(char *op, where_clause_value *wcv){
      
        where_clause *wc=malloc(sizeof(where_clause));
        wc->op=op;
        wc->wcv=wcv;
     
        return wc;
    }

    clause *where_clause_to_clause(where_clause *where_cl){
      
        clause *clse=malloc(sizeof(clause));
        clse->type=WHERE;
        clse->where_cl=where_cl;
        return clse;
    }

    clause_list *create_clause_list(clause *cl,clause_list *next_cll){

        clause_list *cll=malloc(sizeof(clause_list));
        cll->cl=cl;
        cll->next_cll=next_cll;
        return cll;
    }

    expression *create_expression(clause_list *cll){

        expression *exp=malloc(sizeof(expression));
        exp->cll=cll;
        return exp;
    }

    expression_list *create_expression_list(expression *exp, expression_list *next_exp){

        expression_list *exp_list=malloc(sizeof(expression_list));
        exp_list->exp=exp;
        exp_list->next_exp=next_exp;
        return exp_list;
    }

    expression_clause *create_expression_tree_clause(char* op, expression_list *exp){
      expression_clause *exp_cl=malloc(sizeof(expression_clause));
      exp_cl->op=op;
      exp_cl->exp=exp;
      return exp_cl;
    }

    clause *expression_tree_clause_to_clause(expression_clause *exp_cl){
    
        clause *cl=malloc(sizeof(clause));
        cl->type=EXPRESSION;
        cl->exp_cl=exp_cl;
        return cl; 
    }

    text_clause *create_text_clause(char* search_str, bool lang_op, char* lang_str,bool case_sense, bool diacr_sense){
        text_clause *text_cl=malloc(sizeof(text_clause));
        text_cl->search_str=search_str;
        text_cl->lang_op=lang_op;
        text_cl->lang_str=lang_str;
        text_cl->case_sense=case_sense;
        text_cl->diacr_sense=diacr_sense;
        return text_cl;
    }

    clause *text_clause_to_clause(text_clause *text_cl){
    
        clause *cl=malloc(sizeof(clause));
        cl->type=TEXT;
        cl->text_cl=text_cl;
        return cl; 
    }

    query *create_query(expression * exp){

        query *qu=malloc(sizeof(query));
        qu->exp=exp;
        return qu;
    }

%}

%union {

    query             *qu;
    expression        *exp;
    clause_list       *cll;
    clause            *cl;
    leaf_clause       *leaf_cl;
    comment_clause    *comm_cl;
    expression_clause *exp_cl;
    expression_list   *exp_list;
    value             *vl;
    leaf_value        *lv;
    text_clause       *text_cl;

    where_clause       *wc;
    where_clause_value *wcv;

    char *            strval;
    int               intval;
    double            dubval;
    _array            *arrval;
    bool              boolval;
    
    operator_object   *oob;
    operator_list     *ol;
    operator          *op;

    array_element     *ae;
}

%type<qu>         QUERY
%type<exp>        EXPRESSION
%type<cll>        CLAUSE_LIST
%type<cl>         CLAUSE
%type<leaf_cl>    LEAF_CLAUSE
%type<comm_cl>    COMMENT_CLAUSE
%type<exp_cl>     EXPRESSION_TREE_CLAUSE
%type<text_cl>    TEXT_CLAUSE
%type<vl>         VALUE

%type<exp_list>   EXPRESSION_LIST

%type<strval>     KEY VALUE_OPERATOR ARRAY_OPERATOR
%type<op>         OPERATOR
%type<oob>        OPEARATOR_OBJECT
%type<ol>         OPERATOR_LIST

%type<strval>     LSCOPE RSCOPE COMMA
    
%type<ae>         LEAF_VALUE_LIST

%type<wc>         WHERE_CLAUSE
%type<wcv>        WHERE_CLAUSE_VALUE
%type<strval>     WHERE_OPERATOR
%token            WHERE_OPERATOR

/* Operators */

/* Tree */
%type<strval> TREE_OPERATOR OR NOR AND
%token OR NOR AND

/* Compare */
 %type<strval>    EQ LESS GREAT LESSEQ GREATEQ NOTEQ TYPE SIZE EXISTS NOT
 %token           EQ NOTEQ LESS LESSEQ GREAT GREATEQ TYPE SIZE EXISTS NOT

/* Array */
%type<strval>     IN NIN ALL
%token            IN NIN ALL

/* Mod */
%type<strval>     MOD_OPERATOR 
%type<lv>         DIVISOR REMAINDER
%token            MOD_OPERATOR

/* Comment */
%type<strval>     COMMENT_OPERATOR
%token            COMMENT_OPERATOR

/* Text clause */
%type<strval>     DIACRITIC_SENSITIVE_OPERATOR CASE_SENSITIVE_OPERATOR LANGUAGE_OPERATOR SEARCH_OPERATOR TEXT_OPERATOR
%token            DIACRITIC_SENSITIVE_OPERATOR CASE_SENSITIVE_OPERATOR LANGUAGE_OPERATOR SEARCH_OPERATOR TEXT_OPERATOR

/* Bson document structure */
//%type<strval> DOCUMENT MEMBER_LIST MEMBER


/* Type of values */
%type<lv> LEAF_VALUE
%type<intval> INT
%type<strval> STRING
%type<dubval> DOUBLE
%type<arrval> ARRAY
%type<boolval> BOOLEAN    

%token INT STRING DOUBLE BOOLEAN

%token LSCOPE RSCOPE COMMA LSQBRACKET RSQBRACKET LRBRACKET RRBRACKET



%start QUERY

%%

QUERY       : EXPRESSION {$$=create_query($1); 
            printf("adsasdad %s\n", ($$->exp->cll->cl->leaf_cl->vl->oob->ol->op->vop->value->i)); exit(0); };

EXPRESSION  : LSCOPE CLAUSE_LIST RSCOPE { $$=create_expression( $2 ); };

CLAUSE_LIST : CLAUSE COMMA CLAUSE_LIST  { $$=create_clause_list( $1, $3 ); }
            | CLAUSE                    { $$=create_clause_list( $1, NULL ); }
            ;

CLAUSE      : LEAF_CLAUSE             { $$=leaf_clause_to_clause($1); }
            | COMMENT_CLAUSE          { $$=comment_clause_to_clause($1); }
            | WHERE_CLAUSE            { $$=where_clause_to_clause($1); }
            | EXPRESSION_TREE_CLAUSE  { $$=expression_tree_clause_to_clause($1); }
            | TEXT_CLAUSE             { $$=text_clause_to_clause($1); }
            ;


/* TEXT CLAUSE SECTION */

TEXT_CLAUSE : LSCOPE TEXT_OPERATOR EQ LSCOPE SEARCH_OPERATOR EQ STRING RSCOPE RSCOPE { $$=create_text_clause($7,false,"",false,false); }
            | LSCOPE TEXT_OPERATOR EQ LSCOPE SEARCH_OPERATOR EQ STRING COMMA
                LANGUAGE_OPERATOR EQ STRING COMMA
                CASE_SENSITIVE_OPERATOR EQ BOOLEAN COMMA
                DIACRITIC_SENSITIVE_OPERATOR EQ BOOLEAN RSCOPE RSCOPE { $$=create_text_clause($7,false,$11,$15,$19); }
            ;

/* END OF SECTION */

/*WHERE CLAUSE SECTION*/
                
WHERE_CLAUSE :  LSCOPE WHERE_OPERATOR EQ LRBRACKET WHERE_CLAUSE_VALUE RRBRACKET RSCOPE {$$=create_where_clause($2,$5);} ;

WHERE_CLAUSE_VALUE     : STRING {$$=string_to_where_clause_value($1);}
                     //| FUNCTION
                       ;
/* END OF SECTION */   

/*COMMENT CLAUSE SECTION*/
COMMENT_CLAUSE         : LSCOPE COMMENT_OPERATOR EQ STRING RSCOPE { $$=create_comment_clause($2,$4); } ;
/* END OF SECTION */

/*TREE CLAUSE SECTION*/

EXPRESSION_TREE_CLAUSE : LSCOPE TREE_OPERATOR EQ LSQBRACKET EXPRESSION_LIST RSQBRACKET RSCOPE { $$=create_expression_tree_clause($2,$5); } ;

EXPRESSION_LIST        : EXPRESSION                       { $$=create_expression_list( $1, NULL ); };
                       | EXPRESSION COMMA EXPRESSION_LIST { $$=create_expression_list( $1, $3 ); };
                       ;

TREE_OPERATOR          : OR | AND | NOR ;

/* END OF SECTION */

/* LEAF CLAUSE SECTION */
LEAF_CLAUSE        : KEY EQ VALUE {$$=create_leaf_clause($1, $3);};

KEY                : STRING ;

VALUE              : LEAF_VALUE       {$$=create_leaf_value_value($1);}
                   | OPEARATOR_OBJECT {$$=create_operator_object_value($1);}
                   ;

OPEARATOR_OBJECT   : LSCOPE OPERATOR_LIST RSCOPE {$$=create_operator_object($2);} ;

OPERATOR_LIST      : OPERATOR                     {$$=create_operator_list($1, NULL);}
                   | OPERATOR COMMA OPERATOR_LIST {$$=create_operator_list($1,$3);}
                   ;

OPERATOR           : VALUE_OPERATOR EQ LEAF_VALUE                                  {$$=create_value_operator($1,$3);}
                   | ARRAY_OPERATOR EQ ARRAY                                       {$$=create_array_operator($1,$3); }
                   | MOD_OPERATOR EQ LSQBRACKET DIVISOR COMMA REMAINDER RSQBRACKET {$$=create_mod_operator($4,$6); }
                   | NOT EQ LSCOPE OPERATOR RSCOPE                                 {$$=create_not_operator($4); }
                   
                   /*
                   | ELEMATCH_EXPRESSION_OPERATOR EQ EXPRESSION 
                   | ELEMATCH_OBJECT_OPERATOR EQ OPEARATOR_OBJECT*/
                   ;

VALUE_OPERATOR     : EQ | NOTEQ | LESS | LESSEQ | GREAT | GREATEQ | TYPE | SIZE | EXISTS ;

DIVISOR            : LEAF_VALUE ;

REMAINDER          : LEAF_VALUE ;

ARRAY              : LSQBRACKET LEAF_VALUE_LIST RSQBRACKET {$$=create_array($2); };

ARRAY_OPERATOR     : IN | NIN | ALL ;

LEAF_VALUE_LIST    : LEAF_VALUE                         { $$=create_array_element($1,NULL); }
                   | LEAF_VALUE COMMA LEAF_VALUE_LIST   { $$=create_array_element($1,$3); }
                   ;

LEAF_VALUE         : INT     { $$=create_integer_value($1); }
                   | STRING  { $$=create_string_value($1); }
                   | DOUBLE  { $$=create_double_value($1); }
                   | ARRAY   { $$=create_array_value($1); }
                   | BOOLEAN { $$=create_boolean_value($1); }
                   ;

/* END OF SECTION */

/* BSON DOCUMENT STRUCTURE SECTION*/
/*
DOCUMENT    : LSCOPE MEMBER_LIST RSCOPE

MEMBER_LIST : MEMBER 
            | MEMBER COMMA MEMBER_LIST

MEMBER      : KEY EQ LEAF_VALUE
*/
/* END OF SECTION */

%%

void main () { yydebug=1; yyparse(); }

int yywrap(void){ return 0; }