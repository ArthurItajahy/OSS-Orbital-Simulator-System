#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <vector>
#include "lexer.h"

class Interpreter {
public:
    void interpret(const std::vector<Token>& tokens);
};

#endif
