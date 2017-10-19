%{
#include "expression.h"
#include "parser.h"

#include <stdio.h>

%}

%option outfile="lexer.c" header-file="lexer.h"
%option warn nodefault

%option reentrant noyywrap never-interactive nounistd
%option bison-bridge

LPAREN          "("
RPAREN          ")"
NOT             "~"
AND            "/\\"
OR             "\\/"
IMPLIES        "->"
DOUBLE_IMPLIES "<->"

WS          [\r\n\t]*
PROP        [a-zA-Z]

%%

{WS}            { /* Skip blanks. */ }
{PROP}        { sscanf(yytext, "%c", &yylval->value); return TOKEN_PROP; }

{NOT}        { return TOKEN_NOT; }
{AND}        { return TOKEN_AND; }
{OR}        { return TOKEN_OR; }
{IMPLIES}        { return TOKEN_IMPLIES; }
{DOUBLE_IMPLIES}        { return TOKEN_DOUBLE_IMPLIES; }
{LPAREN}        { return TOKEN_LPAREN; }
{RPAREN}        { return TOKEN_RPAREN; }
.               { }

%%

