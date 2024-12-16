#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

enum class TokenType {
    VAR, IDENTIFIER, NUMBER, ASSIGN, SEMICOLON, END_OF_FILE, UNKNOWN
};

struct Token {
    TokenType type;
    std::string value;
};

class Lexer {
public:
    Lexer(const std::string& input);
    std::vector<Token> tokenize();

private:
    std::string input;
    size_t pos;
};

#endif
