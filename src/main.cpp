#include <iostream>
#include <vector>
#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/interpreter.h"

int main() {
    std::string input = "var x = 5;"; // Example program

    Lexer lexer(input);
    std::vector<Token> tokens = lexer.tokenize();

    Parser parser(tokens);
    parser.parse();

    Interpreter interpreter;
    interpreter.interpret(tokens);

    return 0;
}
