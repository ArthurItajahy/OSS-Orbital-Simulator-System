#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <memory>
#include <unordered_map>
#include "token.h"
#include "expression.h"
#include "statement.h"  // Make sure to define Statement class

class Parser {
public:
    explicit Parser(std::vector<Token>& tokens);
    std::vector<std::shared_ptr<Statement>> parse();

private:
    std::vector<Token>& tokens;
    size_t pos;
    std::unordered_map<std::string, std::shared_ptr<Expression>> symbolTable;

    Token currentToken();
    Token consume();
    bool match(TokenType type);

    std::shared_ptr<Statement> parseStatement();
    std::shared_ptr<Statement> parseVariableDeclaration();
    std::shared_ptr<Statement> parsePrintStatement();
    std::shared_ptr<Expression> parseExpression();
    std::shared_ptr<Expression> parsePrimary();
};

#endif
