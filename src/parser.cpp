#include "../include/parser.h"
#include <iostream>
#include "../include/literal_expression.h"
#include "../include/variable_expression.h"
#include "../include/binary_expression.h"
#include "../include/lexer.h"  // Include lexer.h to make sure Token is recognized

Parser::Parser(std::vector<Token>& tokens) : tokens(tokens), pos(0), symbolTable() {}

Token Parser::currentToken() {
    return tokens[pos];
}

Token Parser::consume() {
    return tokens[pos++];
}

bool Parser::match(TokenType type) {
    if (currentToken().type == type) {
        consume();
        return true;
    }
    return false;
}

std::vector<std::shared_ptr<Statement>> Parser::parse() {
    std::vector<std::shared_ptr<Statement>> statements;

    while (currentToken().type != TokenType::END_OF_FILE) {
        statements.push_back(parseStatement());
    }

    return statements;
}

std::shared_ptr<Statement> Parser::parseStatement() {
    if (match(TokenType::VAR)) {
        return parseVariableDeclaration();
    }
    else if (match(TokenType::PRINT)) {
        return parsePrintStatement();
    }
    else {
        throw std::runtime_error("Unexpected token: " + currentToken().value);
    }
}

std::shared_ptr<Statement> Parser::parseVariableDeclaration() {
    consume();  // Consume 'var'

    std::string type = consume().value;  // Variable type (can be used later if needed)
    std::string name = consume().value;  // Variable name

    match(TokenType::ASSIGN);  // Consume '='

    auto expression = parseExpression();

    match(TokenType::SEMICOLON);  // Consume ';'

    symbolTable[name] = expression;  // Insert variable into symbol table

    return std::make_shared<VariableDeclaration>(type, name, expression);
}

std::shared_ptr<Statement> Parser::parsePrintStatement() {
    match(TokenType::IDENTIFIER);  // Expect "print"
    auto expression = parseExpression();
    match(TokenType::SEMICOLON);  // Consume ';'
    return std::make_shared<PrintStatement>(expression);
}

std::shared_ptr<Expression> Parser::parseExpression() {
    return parsePrimary();  // Start parsing expressions
}

std::shared_ptr<Expression> Parser::parsePrimary() {
    if (currentToken().type == TokenType::NUMBER) {
        int value = std::stoi(consume().value);
        return std::make_shared<LiteralExpression>(value);
    }
    else if (currentToken().type == TokenType::IDENTIFIER) {
        std::string name = consume().value;
        return std::make_shared<VariableExpression>(name, symbolTable);
    }
    else {
        throw std::runtime_error("Unexpected token in expression: " + currentToken().value);
    }
}
