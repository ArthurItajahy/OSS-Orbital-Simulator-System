#include "../include/lexer.h"
#include <cctype>
#include <iostream>

Lexer::Lexer(const std::string& input)
    : input(input), pos(0) {
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    while (pos < input.size()) {
        char current = input[pos];

        if (std::isspace(current)) {
            pos++;
        }
        else if (current == '/' && input[pos + 1] == '/') {
            readComment();
        }
        else if (std::isalpha(current)) {
            std::string identifier = readIdentifier();
            if (identifier == "var") {
                tokens.push_back({ TokenType::VAR, identifier });
            }
            else if (identifier == "print") {
                tokens.push_back({ TokenType::PRINT, identifier });
            }
            else {
                tokens.push_back({ TokenType::IDENTIFIER, identifier });
            }
        }
        else if (std::isdigit(current)) {
            tokens.push_back({ TokenType::NUMBER, readNumber() });
        }
        else if (current == '=') {
            tokens.push_back({ TokenType::ASSIGN, "=" });
            pos++;
        }
        else if (current == ';') {
            tokens.push_back({ TokenType::SEMICOLON, ";" });
            pos++;
        }
        else {
            std::string unknown(1, current);
            tokens.push_back({ TokenType::UNKNOWN, unknown });
            pos++;
        }
    }

    tokens.push_back({ TokenType::END_OF_FILE, "" });
    return tokens;
}

std::string Lexer::readNumber() {
    std::string number;
    while (pos < input.size() && std::isdigit(input[pos])) {
        number.push_back(input[pos]);
        pos++;
    }
    return number;
}

std::string Lexer::readIdentifier() {
    std::string identifier;
    while (pos < input.size() && (std::isalnum(input[pos]) || input[pos] == '<' || input[pos] == '>')) {
        identifier.push_back(input[pos]);
        pos++;
    }
    return identifier;
}

std::string Lexer::readComment() {
    std::string comment;
    pos += 2;  // Skip over "//"
    while (pos < input.size() && input[pos] != '\n') {
        comment.push_back(input[pos]);
        pos++;
    }
    return comment;
}
