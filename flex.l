%{
	#define YYSTYPE char const *
    #include "calc.tab.h"
    #include <string.h>
%}

%option yylineno
%option noyywrap

%%

[/][/].*\n      		; // comment

[a-zA-Z]*				{yylval=strdup(yytext); return STRING;}
[0-9]+					{yylval=strdup(yytext); return INT;}
[0-9]+\.[0-9]+			{yylval=strdup(yytext); return DOUBLE;}
\{						{yylval=("{"); return LSCOPE;}
\}						{yylval=("}"); return RSCOPE;}

\,						{yylval=(","); return COMMA;}

\:						{yylval=("="); return EQ;}
\$(l|L)(t|T)			{yylval="<"; return LESS;}
\$(l|L)(t|T)(e|E)		{yylval="<="; return LESSEQ;}
\$(g|G)(t|T)			{yylval=">"; return GREAT;}
\$(g|G)(t|T)(e|E)		{yylval=">="; return GREATEQ;}
\$(n|N)(e|E)			{yylval="<>"; return NOTEQ;}
\$type					{yylval="TYPE"; return TYPE;}
\$size					{yylval="SIZE"; return SIZE;}
\$exists				{yylval="EXISTS"; return EXISTS;}

\$in 					{yylval="IN"; return IN;}
\$nin					{yylval="NIN"; return NIN;}

\$not 					{yylval="NOT"; return NOT;}

\$or 					{yylval="OR"; return OR;}
\$nor 					{yylval="NOR"; return NOR;}
\$and					{yylval="AND"; return AND;}

\$where					{return WHERE_OPERATOR;}

\$search				{return SEARCH_OPERATOR;}
\$text					{return TEXT_OPERATOR;}
\$language				{return LANGUAGE_OPERATOR;}
\$caseSensitive			{return CASE_SENSITIVE_OPERATOR;}
\$diacriticSensitive	{return DIACRITIC_SENSITIVE_OPERATOR;}

\$elemMatch				{return ELEMATCH_EXPRESSION_OPERATOR;}

\$comment				{return COMMENT_OPERATOR;}

[ \t\r\n]      			; // whitespace

%%