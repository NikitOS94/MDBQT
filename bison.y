%{
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

    void yyerror(char *s) {
      fprintf (stderr, "%s\n", s);
    }

    typedef enum bool { false, true } bool;

typedef struct operator{
  char * operation;
  char * value;
} operator;

typedef struct operator_list{
  operator op;
  bool and;
  struct operator_list* next_op;
} operator_list;

typedef struct leaf_clause{
  char * key;
  struct operator_list ol;
} leaf_clause;


operator create_operator(char* o, char* v) {
  operator op;
  op.operation=o;
  op.value=v;
  return op;
};

 operator_list create_operator_list(operator op, bool and, struct operator_list *ol) {
  operator_list new_ol;
  new_ol.op=op;
  new_ol.and=and;
  new_ol.next_op=ol;
  return new_ol;
};

 leaf_clause create_leaf_clause(char* key, operator_list ol) {
  leaf_clause new_lc;
  new_lc.key=key;
  new_lc.ol=ol;
  return new_lc;
};

int show(operator op){
  printf("%s %s",op.operation,op.value);
   return 0;
}

%}

%union {
    char * strval;
    int    intval;
    operator op;
    leaf_clause lf;
    operator_list ol;
}

%type<lf> LEAF_CLAUSE 
%type<strval> INT STRING DOUBLE LEAF_VALUE
%type<strval> KEY VALUE_OPERATOR
%type<op> OPERATOR
%type<ol> VALUE OPERATOR_LIST OPEARATOR_OBJECT

%type<strval> EQ LESS GREAT LESSEQ GREATEQ NOTEQ TYPE SIZE EXISTS NOT IN NIN
%type<strval> LSCOPE RSCOPE COMMA

/* Tree operators */
%type<strval> OR NOR AND

%token INT STRING DOUBLE BOOLEAN
%token EQ NOTEQ LESS LESSEQ GREAT GREATEQ TYPE SIZE EXISTS NOT IN NIN
%token LSCOPE RSCOPE COMMA LSQBRACKET RSQBRACKET LRBRACKET RRBRACKET SEARCH_OPERATOR

/* tree operators */
%token OR NOR AND


%start LEAF_CLAUSE

%%
/*
QUERY : EXPRESSION ;
EXPRESSION : LSCOPE CLAUSE_LIST RSCOPE ;
CLAUSE_LIST : CLAUSE
            | CLAUSE COMMA CLAUSE_LIST
            ;

CLAUSE : LEAF_CLAUSE 
       | COMMENT_CLAUSE
       | EXPRESSION_TREE_CLAUSE
       | WHERE_CLAUSE
       | TEXT_CLAUSE
       ;
*/

/* TEXT CLAUSE SECTION */
TEXT_CLAUSE : LSCOPE TEXT_OPERATOR EQ LSCOPE SEARCH_OPERATOR EQ STRING RSCOPE RSCOPE    
            | LSCOPE TEXT_OPERATOR EQ LSCOPE 
                SEARCH_OPERATOR EQ STRING COMMA
                LANGUAGE_OPERATOR EQ STRING COMMA
                CASE_SENSITIVE_OPERATOR EQ BOOLEAN COMMA
                DIACRITIC_SENSITIVE_OPERATOR EQ BOOLEAN RSCOPE RSCOPE
/* END OF SECTION */

/*WHERE CLAUSE SECTION*/
WHERE_CLAUSE :  LSCOPE WHERE_OPERATOR EQ LRBRACKET WHERE_CLAUSE_VALUE RRBRACKET RSCOPE ;

WHERE_CLAUSE_VALUE : STRING
                   | FUNCTION
/* END OF SECTION */   

/*COMMENT CLAUSE SECTION*/
COMMENT_CLAUSE         : LSCOPE COMMENT_OPERATOR EQ STRING RSCOPE
/* END OF SECTION */

/*TREE CLAUSE SECTION*/
EXPRESSION_TREE_CLAUSE : LSCOPE TREE_OPERATOR EQ LSQBRACKET EXPRESSION_LIST RSQBRACKET RSCOPE ;

EXPRESSION_LIST        : EXPRESSION 
                       | EXPRESSION COMMA EXPRESSION_LIST
                       ;

TREE_OPERATOR          : OR
                       | AND
                       | NOR
                       ;
/* END OF SECTION */

/* LEAF CLAUSE SECTION */
LEAF_CLAUSE        : KEY EQ VALUE {$$=create_leaf_clause($1, $3); printf($$.key); exit(0)};

KEY                : STRING ;

VALUE              : LEAF_VALUE {$$=create_operator_list(create_operator("=",$1), false,NULL);}
                   | OPEARATOR_OBJECT {$$=$1;}
                   ;

OPEARATOR_OBJECT   : LSCOPE OPERATOR_LIST RSCOPE {$$=$2;} ;

OPERATOR_LIST      : OPERATOR {$$=create_operator_list($1, false,NULL);}
                   | OPERATOR COMMA OPERATOR_LIST {$$=create_operator_list($1,true,&$3);}
                   ;

OPERATOR           : VALUE_OPERATOR EQ LEAF_VALUE {$$=create_operator($1,$3); }
                   | ARRAY_OPERATOR EQ ARRAY
                   | MOD_OPERATOR EQ LSQBRACKET DIVISOR COMMA REMAINDER RSQBRACKET
                   | NOT EQ LSCOPE OPERATOR RSCOPE
                   
                   /*
                   | ELEMATCH_EXPRESSION_OPERATOR EQ EXPRESSION 
                   | ELEMATCH_OBJECT_OPERATOR EQ OPEARATOR_OBJECT*/
                   ;

VALUE_OPERATOR     : EQ | NOTEQ | LESS | LESSEQ | GREAT | GREATEQ | TYPE | SIZE | EXISTS ;

DIVISOR            : INT | DOUBLE ;

REMAINDER          : INT | DOUBLE ;

ARRAY              : LSCOPE LEAF_VALUE_LIST RSCOPE ;

ARRAY_OPERATOR     : IN
                   | NIN
                   ;

LEAF_VALUE_LIST    : LEAF_VALUE
                   | LEAF_VALUE COMMA LEAF_VALUE_LIST
                   ;

LEAF_VALUE         : INT | STRING | DOUBLE | ARRAY | BOOLEAN;
/* END OF SECTION */

/* BSON DOCUMENT STRUCTURE SECTION*/
/*
DOCUMENT    : LSCOPE <member-list> RSCOPE

MEMBER_LIST : MEMBER 
            | MEMBER COMMA MEMBER_LIST

MEMBER      : KEY EQ LEAF_VALUE
*/
/* END OF SECTION */

%%




void main () { 
  yydebug=1; yyparse(); 
}



int yywrap(void){
   return 0;
}