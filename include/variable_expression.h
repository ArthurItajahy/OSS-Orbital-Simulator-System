#ifndef VARIABLE_EXPRESSION_H
#define VARIABLE_EXPRESSION_H

#include "expression.h"
#include <unordered_map>
#include <string>
#include <memory>

class VariableExpression : public Expression {
public:
    VariableExpression(std::string name, std::unordered_map<std::string, std::shared_ptr<Expression>>& symbolTable)
        : name(std::move(name)), symbolTable(symbolTable) {
    }

    std::shared_ptr<Expression> evaluate() {
        // Evaluate the variable (returning from symbolTable)
        if (symbolTable.find(name) != symbolTable.end()) {
            return symbolTable[name];
        }
        else {
            throw std::runtime_error("Undefined variable: " + name);
        }
    }

private:
    std::string name;
    std::unordered_map<std::string, std::shared_ptr<Expression>>& symbolTable;
};

#endif
