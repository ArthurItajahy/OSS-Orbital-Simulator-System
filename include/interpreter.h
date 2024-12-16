#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <vector>
#include <memory>
#include "statement.h"
#include "expression.h"

class Interpreter {
public:
    explicit Interpreter(std::vector<std::shared_ptr<Statement>>& statements);
    void interpret();

private:
    std::vector<std::shared_ptr<Statement>>& statements;
};

#endif
