
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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

/* Line 1676 of yacc.c  */
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



/* Line 1676 of yacc.c  */
#line 120 "bison.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


