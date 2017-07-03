%{
    #include <stdlib.h>
    #include <stdio.h>
 	#include "structures.h"
    #include "mdbqs_gram.h"
    #include <string.h>

%}

%option yylineno
%option noyywrap

%%

[/][/].*\n      		; // comment

[0-9]+							{ yylval.strval=strdup(yytext); return _INT; }
[0-9]+\.[0-9]+					{ yylval.strval=strdup(yytext); return __DOUBLE; }
(true|false)					{ yylval.boolval=(strcmp(strdup(yytext),"true")==0 ? _true : _false); return __BOOLEAN; }

\{								{ return LSCOPE; }
\}								{ return RSCOPE; }
\[								{ return LSQBRACKET; }
\]								{ return RSQBRACKET; }

\,								{ return COMMA; }

\:								{ yylval.valop_type=_EQ; return EQ; }
\$(e|E)(q|Q)					{ yylval.valop_type=_EQ; return EQ; }
\$(l|L)(t|T)					{ yylval.valop_type=_LESS; return LESS; }
\$(l|L)(t|T)(e|E)				{ yylval.valop_type=_LESSEQ; return LESSEQ; }
\$(g|G)(t|T)					{ yylval.valop_type=_GREAT; return GREAT; }
\$(g|G)(t|T)(e|E)				{ yylval.valop_type=_GREATEQ; return GREATEQ; }
\$(n|N)(e|E)					{ yylval.valop_type=_NOTEQ; return NOTEQ; }
\$type							{ yylval.valop_type=_TYPE; return TYPE; }
\$size							{ yylval.valop_type=_SIZE; return __SIZE; }
\$exists						{ yylval.valop_type=_EXISTS; return EXISTS; }

\$in 							{ yylval.aop_type=_IN; return __IN; }
\$nin							{ yylval.aop_type=_NIN; return NIN; }
\$all							{ yylval.aop_type=_ALL; return ALL; }

\$not 							{ return NOT;}

\$where							{ return WHERE_OPERATOR; }

\$or 							{ yylval.exop_type=_OR; return OR; }
\$nor 							{ yylval.exop_type=_NOR; return NOR; }
\$and							{ yylval.exop_type=_AND; return AND; }

\$search						{ return SEARCH_OPERATOR; }
\$text							{ return TEXT_OPERATOR; }
\$language						{ return LANGUAGE_OPERATOR; }
\$caseSensitive					{ return CASE_SENSITIVE_OPERATOR; }
\$diacriticSensitive			{ return DIACRITIC_SENSITIVE_OPERATOR; }

\$comment						{ return COMMENT_OPERATOR; }

\$mod							{ return MOD_OPERATOR; }

([\.0-9a-zA-Z])*				{yylval.strval=strdup(yytext); return KEY;}
(\"[(\\0)\.\, 0-9a-zA-Z]*\")	{yylval.strval=strdup(yytext); return STRING;}	

[ \t\r\n]      			; // whitespace


%%
