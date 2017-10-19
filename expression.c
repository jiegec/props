#include <stdlib.h>
#include "expression.h"

Expression *createProp(char value) {
    Expression *b = (Expression *) malloc(sizeof(Expression));
    b->type = PROP;
    b->value = value;
    b->left = b->right = NULL;
    return b;
}

Expression *createOp(OperationType type,
                     Expression *left, Expression *right) {
    Expression *b = (Expression *) malloc(sizeof(Expression));
    b->type = type;
    b->left = left;
    b->right = right;
    return b;
}