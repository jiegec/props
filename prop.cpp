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

#include "prop.h"

void mark_props(const Expression *root, int prop[], int &prop_num) {
    if (root == nullptr)
        return;
    mark_props(root->left, prop, prop_num);
    if (root->type == PROP && !prop[root->value - 'A']) {
        prop[root->value - 'A'] = 1;
        prop_num++;
    }
    mark_props(root->right, prop, prop_num);
}

bool calc(const Expression *root, const int prop[], const bool permu[]) {
    if (root == nullptr)
        return false;
    bool left = calc(root->left, prop, permu);
    bool right = calc(root->right, prop, permu);
    switch (root->type) {
        case NOT:
            return !right;
        case AND:
            return left && right;
        case OR:
            return left || right;
        case IMPLIES:
            return (!left) || right;
        case DOUBLE_IMPLIES:
            return (left && right) || (!left && !right);
        case PROP:
            return permu[prop[root->value - 'A']];
        default:
            return false;
    }
}

bool next_permutation(const int prop_num, bool permu[]) {
    bool hasZero = false;
    int lastZero = 0;
    for (int i = 1; i <= prop_num; i++) {
        if (!permu[i]) {
            hasZero = true;
            lastZero = i;
        }
    }
    if (!hasZero)
        return false;
    permu[lastZero] = true;
    for (int i = lastZero + 1; i <= prop_num; i++) {
        permu[i] = false;
    }
    return true;
}

void parse_expression(Expression **exp, char buffer[]) {
    yyscan_t scanner;
    YY_BUFFER_STATE state;

    yylex_init(&scanner);
    state = yy_scan_string(buffer, scanner);
    yyparse(exp, scanner);
    yy_delete_buffer(state, scanner);
    yylex_destroy(scanner);
}

void free_expression(Expression **exp) {
    if (*exp != nullptr) {
        free_expression(&(*exp)->left);
        free_expression(&(*exp)->right);
        free(*exp);
        *exp = nullptr;
    }
}

