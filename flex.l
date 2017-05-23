%{
	#define YYSTYPE char const *
    #include "bison.tab.h"
    #include <string.h>
%}

%option yylineno
%option noyywrap

%%

[/][/].*\n      		; // comment

[0-9]+							{yylval=strdup(yytext); return INT;}
[0-9]+\.[0-9]+					{yylval=strdup(yytext); return DOUBLE;}
(true|false)					{yylval=strdup(yytext); return BOOLEAN;}

\{								{yylval=("{"); return LSCOPE;}
\}								{yylval=("}"); return RSCOPE;}
\[								{yylval=("]"); return LSQBRACKET;}
\]								{yylval=("["); return RSQBRACKET;}

\,								{yylval=(","); return COMMA;}

\:								{yylval=("="); return EQ;}
\$(l|L)(t|T)					{yylval="<"; return LESS;}
\$(l|L)(t|T)(e|E)				{yylval="<="; return LESSEQ;}
\$(g|G)(t|T)					{yylval=">"; return GREAT;}
\$(g|G)(t|T)(e|E)				{yylval=">="; return GREATEQ;}
\$(n|N)(e|E)					{yylval="<>"; return NOTEQ;}
\$type							{yylval="TYPE"; return TYPE;}
\$size							{yylval="SIZE"; return SIZE;}
\$exists						{yylval="EXISTS"; return EXISTS;}

\$in 							{yylval="IN"; return IN;}
\$nin							{yylval="NIN"; return NIN;}
\$all							{yylval="ALL"; return ALL;}

\$not 							{yylval="NOT"; return NOT;}

\$comment						{return COMMENT_OPERATOR;}

\$mod							{return MOD_OPERATOR;}


([a-zA-Z]*)|(\"[ a-zA-Z]*\")	{yylval=strdup(yytext); return STRING;}	

[ \t\r\n]      			; // whitespace


%%