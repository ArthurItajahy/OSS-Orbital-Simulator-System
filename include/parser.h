#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include "lexer.h"

class Parser {
public:
    Parser(const std::vector<Token>& tokens);
    void parse();

private:
    std::vector<Token> tokens;
    size_t pos;
};

#endif
