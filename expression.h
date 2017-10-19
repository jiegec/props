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