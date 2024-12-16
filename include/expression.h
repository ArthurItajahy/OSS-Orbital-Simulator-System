#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>
#include <memory>
#include <iostream>

class Expression {
public:
    virtual ~Expression() = default;

    // Evaluate the expression and return its value
    virtual int evaluate() const = 0;
};

#endif
