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
