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

#ifndef __EXPRESSION_H__
#define __EXPRESSION_H__

typedef enum tagOperationType {
    PROP,
    NOT,
    OR,
    AND,
    IMPLIES,
    DOUBLE_IMPLIES
} OperationType;

typedef struct tagExpression {
    OperationType type;
    char value;
    struct tagExpression *left;
    struct tagExpression *right;
} Expression;


Expression *createProp(char value);

Expression *createOp(OperationType type,
                     Expression *left, Expression *right);

#endif // __EXPRESSION_H__
