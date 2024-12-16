#ifndef LITERAL_EXPRESSION_H
#define LITERAL_EXPRESSION_H

#include "expression.h"

class LiteralExpression : public Expression {
public:
    explicit LiteralExpression(int value);
    
    // Getter for the value
    int getValue() const;
    
    // Override the evaluate function from Expression
    int evaluate() const override;

private: 
    int value;
};

#endif
