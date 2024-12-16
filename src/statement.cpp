#include "../include/statement.h"
#include "../include/literal_expression.h"
#include <iostream>

// Execute the print statement (prints the evaluated expression's value)
void PrintStatement::execute() {
    auto literal = std::dynamic_pointer_cast<LiteralExpression>(expression);
    if (literal) {
        std::cout << literal->getValue() << std::endl;
    }
    else {
        std::cerr << "Error: Expression is not a LiteralExpression." << std::endl;
    }
}

// Execute the variable declaration (assign the evaluated expression to the variable)
void VariableDeclaration::execute() {
    // Evaluate the expression
    auto literal = std::dynamic_pointer_cast<LiteralExpression>(expression);
    if (literal) {
        // Store the value in the symbol table (simulating assignment)
        std::cout << "Variable " << name << " initialized with value: " << literal->getValue() << std::endl;
    }
    else {
        std::cerr << "Error: Expression is not a LiteralExpression." << std::endl;
    }
}
