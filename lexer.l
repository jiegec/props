%{
/*
 *  This file is part of props
 *  Copyright (c) 2017 props's authors
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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

