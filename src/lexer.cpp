#include "../include/lexer.h"
#include <cctype>

Lexer::Lexer(const std::string& input) : input(input), pos(0) {}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    while (pos < input.length()) {
        char currentChar = input[pos];

        if (std::isspace(currentChar)) {
            pos++;
            continue;
        }

        if (currentChar == 'v') { // 'var' keyword
            tokens.push_back({ TokenType::VAR, "var" });
            pos += 3;
            continue;
        }

        if (std::isalpha(currentChar)) { // Identifiers
            std::string value;
            while (std::isalnum(input[pos])) {
                value += input[pos++];
            }
            tokens.push_back({ TokenType::IDENTIFIER, value });
            continue;
        }

        if (std::isdigit(currentChar)) { // Numbers
            std::string value;
            while (std::isdigit(input[pos])) {
                value += input[pos++];
            }
            tokens.push_back({ TokenType::NUMBER, value });
            continue;
        }

        if (currentChar == '=') { // Assignment operator
            tokens.push_back({ TokenType::ASSIGN, "=" });
            pos++;
            continue;
        }

        if (currentChar == ';') { // Semicolon
            tokens.push_back({ TokenType::SEMICOLON, ";" });
            pos++;
            continue;
        }

        tokens.push_back({ TokenType::UNKNOWN, std::string(1, currentChar) });
        pos++;
    }

    tokens.push_back({ TokenType::END_OF_FILE, "" });
    return tokens;
}
