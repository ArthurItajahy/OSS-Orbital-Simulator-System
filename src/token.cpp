#include <string>
enum class TokenType {
    VAR, IDENTIFIER, NUMBER, ASSIGN, SEMICOLON, END_OF_FILE, UNKNOWN
};

struct Token {
    TokenType type;
    std::string value;

}; 