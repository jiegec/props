//
// Created by MacBookAir on 06/11/2017.
//

#ifndef PROPS_PROP_H
#define PROPS_PROP_H

extern "C" {
#include "expression.h"
#include "parser.h"
#include "lexer.h"
}

void mark_props(const Expression *root, int prop[], int &prop_num);

bool calc(const Expression *root, const int prop[], const bool permu[]);

bool next_permutation(int prop_num, bool permu[]);

void parse_expression(Expression **exp, char buffer[]);

void free_expression(Expression **exp);

#endif //PROPS_PROP_H
