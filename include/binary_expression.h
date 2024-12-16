#ifndef BINARY_EXPRESSION_H
#define BINARY_EXPRESSION_H

#include "expression.h"

class BinaryExpression : public Expression {
public:
    BinaryExpression(std::shared_ptr<Expression> left, char op, std::shared_ptr<Expression> right)
        : left(std::move(left)), op(op), right(std::move(right)) {
    }

    // Implement evaluation logic for binary operations
    int evaluate() {
        int leftValue = std::dynamic_pointer_cast<LiteralExpression>(left)->getValue();
        int rightValue = std::dynamic_pointer_cast<LiteralExpression>(right)->getValue();

        switch (op) {
        case '+': return leftValue + rightValue;
        case '-': return leftValue - rightValue;
        case '*': return leftValue * rightValue;
        case '/': return leftValue / rightValue;
        default: throw std::runtime_error("Unknown operator: " + std::string(1, op));
        }
    }

private:
    std::shared_ptr<Expression> left;
    char op;
    std::shared_ptr<Expression> right;
};

#endif
