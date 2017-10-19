%{
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


