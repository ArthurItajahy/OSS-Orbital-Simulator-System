#include "../include/parser.h"
#include <iostream>

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), pos(0) {}

void Parser::parse() {
    while (tokens[pos].type != TokenType::END_OF_FILE) {
        if (tokens[pos].type == TokenType::VAR) {
            pos++; // Move to the variable name
            if (tokens[pos].type == TokenType::IDENTIFIER) {
                std::string varName = tokens[pos].value;
                pos++; // Move to the '=' symbol
                if (tokens[pos].type == TokenType::ASSIGN) {
                    pos++; // Move to the value
                    if (tokens[pos].type == TokenType::NUMBER) {
                        int value = std::stoi(tokens[pos].value);
                        std::cout << "Assigned value " << value << " to variable " << varName << std::endl;
                        pos++; // Move past the number
                        if (tokens[pos].type == TokenType::SEMICOLON) {
                            pos++; // End of statement
                        }
                    }
                }
            }
        }
    }
}
