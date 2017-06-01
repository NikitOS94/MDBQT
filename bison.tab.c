
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "bison.y"

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include "structures.h"
    #include "get_query.h"

    void yyerror(char *s) { fprintf (stderr, "%s\n", s); exit(0);}

    void ns_error(char *s) { fprintf (stderr, "\n%s not supported by jsquery \n", s); exit(0);}
    
    _array *
    createArray(array_element *first_ae) 
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
    createBooleanValue(bool b)
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

    char* sconcat(char *form, char *s1, char *s2, int plus) 
    {

        size_t len1 = strlen(s1);
        size_t len2 = strlen(s2);                      

        char *result = malloc(len1 + len2 + 1 + plus);

        if (!result) {
            fprintf(stderr, "malloc() failed: insufficient memory!\n");
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
            fprintf(stderr, "malloc() failed: insufficient memory!\n");
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
            fprintf(stderr, "malloc() failed: insufficient memory!\n");
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
        else                                                  ns_error(value_type);
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
    get_jsquery(query *qu)
    {
        char   *expr=get_expression(qu->exp);
        char   *result= sconcatsingle("'%s'", expr, 2); 

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





/* Line 189 of yacc.c  */
#line 743 "bison.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     WHERE_OPERATOR = 258,
     OR = 259,
     NOR = 260,
     AND = 261,
     EQ = 262,
     NOTEQ = 263,
     LESS = 264,
     LESSEQ = 265,
     GREAT = 266,
     GREATEQ = 267,
     TYPE = 268,
     SIZE = 269,
     EXISTS = 270,
     NOT = 271,
     IN = 272,
     NIN = 273,
     ALL = 274,
     MOD_OPERATOR = 275,
     COMMENT_OPERATOR = 276,
     DIACRITIC_SENSITIVE_OPERATOR = 277,
     CASE_SENSITIVE_OPERATOR = 278,
     LANGUAGE_OPERATOR = 279,
     SEARCH_OPERATOR = 280,
     TEXT_OPERATOR = 281,
     INT = 282,
     STRING = 283,
     DOUBLE = 284,
     BOOLEAN = 285,
     LSCOPE = 286,
     RSCOPE = 287,
     COMMA = 288,
     LSQBRACKET = 289,
     RSQBRACKET = 290,
     LRBRACKET = 291,
     RRBRACKET = 292
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 670 "bison.y"


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



/* Line 214 of yacc.c  */
#line 847 "bison.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 859 "bison.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  18
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   110

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  55
/* YYNRULES -- Number of states.  */
#define YYNSTATES  118

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     9,    13,    15,    17,    19,    21,
      23,    25,    35,    57,    65,    67,    73,    79,    83,    85,
      89,    91,    93,    95,    99,   101,   103,   105,   109,   111,
     115,   119,   123,   131,   137,   139,   141,   143,   145,   147,
     149,   151,   153,   155,   157,   159,   163,   165,   167,   169,
     171,   175,   177,   179,   181,   183
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      39,     0,    -1,    40,    -1,    31,    41,    32,    -1,    42,
      33,    41,    -1,    42,    -1,    50,    -1,    46,    -1,    44,
      -1,    47,    -1,    43,    -1,    31,    26,     7,    31,    25,
       7,    28,    32,    32,    -1,    31,    26,     7,    31,    25,
       7,    28,    33,    24,     7,    28,    33,    23,     7,    30,
      33,    22,     7,    30,    32,    32,    -1,    31,     3,     7,
      36,    45,    37,    32,    -1,    28,    -1,    31,    21,     7,
      28,    32,    -1,    49,     7,    34,    48,    35,    -1,    31,
      47,    32,    -1,    40,    -1,    40,    33,    48,    -1,     4,
      -1,     6,    -1,     5,    -1,    51,     7,    52,    -1,    28,
      -1,    62,    -1,    53,    -1,    31,    54,    32,    -1,    55,
      -1,    55,    33,    54,    -1,    56,     7,    62,    -1,    60,
       7,    59,    -1,    20,     7,    34,    57,    33,    58,    35,
      -1,    16,     7,    31,    55,    32,    -1,     7,    -1,     8,
      -1,     9,    -1,    10,    -1,    11,    -1,    12,    -1,    13,
      -1,    14,    -1,    15,    -1,    62,    -1,    62,    -1,    34,
      61,    35,    -1,    17,    -1,    18,    -1,    19,    -1,    62,
      -1,    62,    33,    61,    -1,    27,    -1,    28,    -1,    29,
      -1,    59,    -1,    30,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   765,   765,   768,   771,   772,   775,   776,   777,   778,
     779,   785,   786,   796,   799,   804,   810,   811,   814,   815,
     818,   818,   818,   823,   826,   829,   830,   833,   836,   837,
     840,   841,   842,   843,   846,   846,   846,   846,   846,   846,
     846,   846,   846,   849,   852,   855,   857,   857,   857,   860,
     861,   864,   865,   866,   867,   868
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "WHERE_OPERATOR", "OR", "NOR", "AND",
  "EQ", "NOTEQ", "LESS", "LESSEQ", "GREAT", "GREATEQ", "TYPE", "SIZE",
  "EXISTS", "NOT", "IN", "NIN", "ALL", "MOD_OPERATOR", "COMMENT_OPERATOR",
  "DIACRITIC_SENSITIVE_OPERATOR", "CASE_SENSITIVE_OPERATOR",
  "LANGUAGE_OPERATOR", "SEARCH_OPERATOR", "TEXT_OPERATOR", "INT", "STRING",
  "DOUBLE", "BOOLEAN", "LSCOPE", "RSCOPE", "COMMA", "LSQBRACKET",
  "RSQBRACKET", "LRBRACKET", "RRBRACKET", "$accept", "QUERY", "EXPRESSION",
  "CLAUSE_LIST", "CLAUSE", "TEXT_CLAUSE", "WHERE_CLAUSE",
  "WHERE_CLAUSE_VALUE", "COMMENT_CLAUSE", "EXPRESSION_TREE_CLAUSE",
  "EXPRESSION_LIST", "TREE_OPERATOR", "LEAF_CLAUSE", "KEY", "VALUE",
  "OPEARATOR_OBJECT", "OPERATOR_LIST", "OPERATOR", "VALUE_OPERATOR",
  "DIVISOR", "REMAINDER", "ARRAY", "ARRAY_OPERATOR", "LEAF_VALUE_LIST",
  "LEAF_VALUE", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    38,    39,    40,    41,    41,    42,    42,    42,    42,
      42,    43,    43,    44,    45,    46,    47,    47,    48,    48,
      49,    49,    49,    50,    51,    52,    52,    53,    54,    54,
      55,    55,    55,    55,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    57,    58,    59,    60,    60,    60,    61,
      61,    62,    62,    62,    62,    62
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     3,     3,     1,     1,     1,     1,     1,
       1,     9,    21,     7,     1,     5,     5,     3,     1,     3,
       1,     1,     1,     3,     1,     1,     1,     3,     1,     3,
       3,     3,     7,     5,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     1,     1,     1,
       3,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,    20,    22,    21,    24,     0,     0,
       5,    10,     8,     7,     9,     0,     6,     0,     1,     0,
       0,     0,     0,     0,     3,     0,     0,     0,     0,     0,
       0,    17,     4,     0,    51,    52,    53,    55,     0,     0,
      23,    26,    54,    25,     0,     0,     0,    18,     0,    34,
      35,    36,    37,    38,    39,    40,    41,    42,     0,    46,
      47,    48,     0,     0,    28,     0,     0,     0,    49,    14,
       0,    15,     0,     0,    16,     0,     0,    27,     0,     0,
       0,    45,     0,     0,     0,    19,     0,     0,    29,    30,
      31,    50,    13,     0,     0,     0,    43,     0,     0,    33,
       0,    11,     0,     0,    44,     0,    32,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    12
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,    47,     9,    10,    11,    12,    70,    13,    14,
      48,    15,    16,    17,    40,    41,    63,    64,    65,    95,
     103,    42,    66,    67,    68
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -28
static const yytype_int8 yypact[] =
{
     -26,     2,    18,   -28,   -28,   -28,   -28,   -28,    -2,    -9,
      -8,   -28,   -28,   -28,   -28,    20,   -28,    21,   -28,    24,
      25,    28,     5,    19,   -28,     2,     0,   -14,    17,    31,
      32,   -28,   -28,   -26,   -28,   -28,   -28,   -28,    30,    27,
     -28,   -28,   -28,   -28,    34,    26,    39,    33,    35,   -28,
     -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,    58,   -28,
     -28,   -28,    60,    36,    38,    62,    65,    40,    41,   -28,
      42,   -28,    69,   -26,   -28,    46,    44,   -28,    30,    27,
      47,   -28,    27,    48,    54,   -28,    30,    27,   -28,   -28,
     -28,   -28,   -28,   -11,    51,    52,   -28,    55,    64,   -28,
      27,   -28,    77,    56,   -28,    61,   -28,    53,    67,    85,
      63,    66,    72,    88,    68,    70,    71,   -28
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -28,   -28,    96,    75,   -28,   -28,   -28,   -28,   -28,     4,
      37,   -28,   -28,   -28,   -28,   -28,    23,    11,   -28,   -28,
     -28,    29,   -28,    22,   -27
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      43,    19,     4,     5,     6,     1,     4,     5,     6,     4,
       5,     6,    23,    34,    35,    36,    37,    38,    18,    20,
      39,    97,    98,    24,    21,    25,    23,    26,    27,    22,
       7,    28,    29,     8,    33,    30,    22,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    31,    89,    44,    34,    35,    36,    37,    71,    45,
      96,    39,    69,    46,    72,    75,    73,    76,    77,    79,
      74,    78,    80,   104,    82,    81,    84,    86,    87,    83,
      92,    39,    93,    99,   105,   100,   108,   101,   102,   107,
     109,   106,   110,   111,   113,   114,     3,    94,   115,   112,
      32,    88,   116,   117,    91,     0,     0,     0,     0,    90,
      85
};

static const yytype_int8 yycheck[] =
{
      27,     3,     4,     5,     6,    31,     4,     5,     6,     4,
       5,     6,     8,    27,    28,    29,    30,    31,     0,    21,
      34,    32,    33,    32,    26,    33,    22,     7,     7,    31,
      28,     7,     7,    31,    34,     7,    31,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    32,    79,    36,    27,    28,    29,    30,    32,    28,
      87,    34,    28,    31,    25,     7,    33,     7,    32,     7,
      35,    33,     7,   100,    33,    35,     7,    31,    34,    37,
      32,    34,    28,    32,     7,    33,    33,    32,    24,    28,
      23,    35,     7,    30,    22,     7,     0,    86,    30,    33,
      25,    78,    32,    32,    82,    -1,    -1,    -1,    -1,    80,
      73
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    31,    39,    40,     4,     5,     6,    28,    31,    41,
      42,    43,    44,    46,    47,    49,    50,    51,     0,     3,
      21,    26,    31,    47,    32,    33,     7,     7,     7,     7,
       7,    32,    41,    34,    27,    28,    29,    30,    31,    34,
      52,    53,    59,    62,    36,    28,    31,    40,    48,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    54,    55,    56,    60,    61,    62,    28,
      45,    32,    25,    33,    35,     7,     7,    32,    33,     7,
       7,    35,    33,    37,     7,    48,    31,    34,    54,    62,
      59,    61,    32,    28,    55,    57,    62,    32,    33,    32,
      33,    32,    24,    58,    62,     7,    35,    28,    33,    23,
       7,    30,    33,    22,     7,    30,    32,    32
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 765 "bison.y"
    {(yyval.qu) = create_query((yyvsp[(1) - (1)].exp)); char *result=get_jsquery((yyval.qu)); exit(0); ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 768 "bison.y"
    { (yyval.exp) = create_expression((yyvsp[(2) - (3)].cll)); ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 771 "bison.y"
    { (yyval.cll) = create_clause_list((yyvsp[(1) - (3)].cl), (yyvsp[(3) - (3)].cll)); ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 772 "bison.y"
    { (yyval.cll) = create_clause_list((yyvsp[(1) - (1)].cl), NULL); ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 785 "bison.y"
    { (yyval.cl) = create_text_clause((yyvsp[(7) - (9)].strval), false, "", false, false); ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 789 "bison.y"
    { (yyval.cl) = create_text_clause((yyvsp[(7) - (21)].strval), false, (yyvsp[(11) - (21)].strval), (yyvsp[(15) - (21)].boolval), (yyvsp[(19) - (21)].boolval)); ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 796 "bison.y"
    { (yyval.cl) = create_where_clause((yyvsp[(2) - (7)].strval),(yyvsp[(5) - (7)].wcv)); ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 799 "bison.y"
    { (yyval.wcv) = string_to_where_clause_value((yyvsp[(1) - (1)].strval)); ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 804 "bison.y"
    { (yyval.cl) = create_comment_clause((yyvsp[(2) - (5)].strval), (yyvsp[(4) - (5)].strval)); ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 810 "bison.y"
    { (yyval.cl) = create_expression_tree_clause((yyvsp[(1) - (5)].exop_type), (yyvsp[(4) - (5)].exp_list)); ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 811 "bison.y"
    { (yyval.cl) = (yyvsp[(2) - (3)].cl); ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 814 "bison.y"
    { (yyval.exp_list) = create_expression_list( (yyvsp[(1) - (1)].exp), NULL ); ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 815 "bison.y"
    { (yyval.exp_list) = create_expression_list( (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp_list) ); ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 823 "bison.y"
    { (yyval.cl) = create_leaf_clause((yyvsp[(1) - (3)].strval), (yyvsp[(3) - (3)].vl)); ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 829 "bison.y"
    { (yyval.vl) = create_leaf_value_value((yyvsp[(1) - (1)].lv)); ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 830 "bison.y"
    { (yyval.vl) = create_operator_object_value((yyvsp[(1) - (1)].oob)); ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 833 "bison.y"
    { (yyval.oob) = create_operator_object((yyvsp[(2) - (3)].ol)); ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 836 "bison.y"
    { (yyval.ol) = create_operator_list((yyvsp[(1) - (1)].op), NULL); ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 837 "bison.y"
    { (yyval.ol) = create_operator_list((yyvsp[(1) - (3)].op), (yyvsp[(3) - (3)].ol)); ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 840 "bison.y"
    { (yyval.op) = create_value_operator((yyvsp[(1) - (3)].valop_type), (yyvsp[(3) - (3)].lv)); ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 841 "bison.y"
    { (yyval.op) = create_array_operator((yyvsp[(1) - (3)].aop_type), (yyvsp[(3) - (3)].arrval)); ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 842 "bison.y"
    { (yyval.op) = create_mod_operator((yyvsp[(4) - (7)].lv), (yyvsp[(6) - (7)].lv)); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 843 "bison.y"
    { (yyval.op) = create_not_operator((yyvsp[(4) - (5)].op)); ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 855 "bison.y"
    {(yyval.arrval) = createArray((yyvsp[(2) - (3)].ae)); ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 860 "bison.y"
    { (yyval.ae) = create_array_element((yyvsp[(1) - (1)].lv), NULL); ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 861 "bison.y"
    { (yyval.ae) = create_array_element((yyvsp[(1) - (3)].lv), (yyvsp[(3) - (3)].ae)); ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 864 "bison.y"
    { (yyval.lv) = create_integer_value((yyvsp[(1) - (1)].strval)); ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 865 "bison.y"
    { (yyval.lv) = create_string_value((yyvsp[(1) - (1)].strval)); ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 866 "bison.y"
    { (yyval.lv) = create_double_value((yyvsp[(1) - (1)].strval)); ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 867 "bison.y"
    { (yyval.lv) = create_array_value((yyvsp[(1) - (1)].arrval)); ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 868 "bison.y"
    { (yyval.lv) = createBooleanValue((yyvsp[(1) - (1)].boolval)); ;}
    break;



/* Line 1455 of yacc.c  */
#line 2368 "bison.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 873 "bison.y"


int main () { yydebug=1; yyparse(); return 0;}

int yywrap(void){ return 0; }
