#include <iostream>
#include <vector>
#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/interpreter.h"
#include <string>
#include <sstream>
#include <fstream>
#include <stdexcept>

std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::string goToTheScript() {
    return "C:/Users/User/Desktop/StarOrbit/OSS/orb_script_examples/script.orb";
}

int main() {
    try {
        std::string filePath = goToTheScript();
        std::cout << "Attempting to read file: " << filePath << std::endl;

        std::string fileContent = readFile(filePath);
        if (fileContent.empty()) {
            throw std::runtime_error("File is empty: " + filePath);
        }

        Lexer lexer(fileContent);
        std::vector<Token> tokens = lexer.tokenize();

        Parser parser(tokens);
        std::vector<std::shared_ptr<Statement>> statements = parser.parse();

        Interpreter interpreter;
        interpreter.interpret(statements);

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
