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
