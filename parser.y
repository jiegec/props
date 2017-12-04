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
#include "lexer.h"

int yyerror(Expression **exp, yyscan_t scanner, const char *msg) {
    fprintf(stderr,"Lexer error:%s\n",msg);
    return 0;
}

%}

%code requires {
#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void* yyscan_t;
#endif
}

%output  "parser.c"
%defines "parser.h"

%define api.pure full
%lex-param   {yyscan_t scanner}
%parse-param {Expression **expression}
%parse-param {yyscan_t scanner}

%union {
    char value;
    Expression *expression;
}

%left "<->" TOKEN_DOUBLE_IMPLIES
%right "->" TOKEN_IMPLIES
%left "\\/" TOKEN_OR
%left "/\\" TOKEN_AND
%left '-' TOKEN_NOT

%token TOKEN_LPAREN
%token TOKEN_RPAREN
%token TOKEN_NOT
%token TOKEN_AND
%token TOKEN_OR
%token TOKEN_IMPLIES
%token TOKEN_DOUBLE_IMPLIES
%token <value> TOKEN_PROP

%type <expression> expr

%%

input: expr {*expression = $1;}
    ;

expr: TOKEN_NOT expr[L] {$$ = createOp(NOT,NULL,$L);}
    | expr[L] TOKEN_OR expr[R] { $$ = createOp(OR, $L,$R);}
    | expr[L] TOKEN_AND expr[R] { $$ = createOp(AND, $L, $R);}
    | expr[L] TOKEN_IMPLIES expr[R] { $$ = createOp(IMPLIES, $L, $R);}
    | expr[L] TOKEN_DOUBLE_IMPLIES expr[R] { $$ = createOp(DOUBLE_IMPLIES, $L, $R);}
    | TOKEN_LPAREN expr[E] TOKEN_RPAREN { $$ = $E;}
    | TOKEN_PROP { $$ = createProp($1);}
    ;

%%


