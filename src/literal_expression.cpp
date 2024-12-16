#include "../include/literal_expression.h"

LiteralExpression::LiteralExpression(int value) : value(value) {}

int LiteralExpression::getValue() const {
    return value;
}

// Implement the evaluate method from the base Expression class
int LiteralExpression::evaluate() const {
    return value;  // The evaluate method simply returns the value for a literal expression
}
