#include "../include/interpreter.h"

Interpreter::Interpreter(std::vector<std::shared_ptr<Statement>>& statements)
    : statements(statements) {
}

void Interpreter::interpret() {
    for (auto& statement : statements) {
        statement->execute();
    }
}
