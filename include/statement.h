#ifndef STATEMENT_H
#define STATEMENT_H

#include <memory>
#include "expression.h"

class Statement {
public:
    virtual ~Statement() = default;
    virtual void execute() = 0;  // Method to execute the statement
};

class PrintStatement : public Statement {
public:
    explicit PrintStatement(std::shared_ptr<Expression> expr) : expression(std::move(expr)) {}
    void execute() override;

private:
    std::shared_ptr<Expression> expression;
};

class VariableDeclaration : public Statement {
public:
    VariableDeclaration(std::string type, std::string name, std::shared_ptr<Expression> expr)
        : type(std::move(type)), name(std::move(name)), expression(std::move(expr)) {
    }

    void execute() override;

private:
    std::string type;
    std::string name;
    std::shared_ptr<Expression> expression;
};

#endif
