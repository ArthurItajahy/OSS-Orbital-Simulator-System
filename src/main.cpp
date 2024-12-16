#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>

// --- Enums for Token Types ---
enum class TokenType {
    PRINT,
    STRING,
    SEMICOLON,
    LEFT_PAREN,
    RIGHT_PAREN,
    END_OF_FILE,
    UNKNOWN
};

// --- Token Class ---
class Token {
public:
    Token(TokenType type, const std::string& value) : type(type), value(value) {}

    TokenType getType() const { return type; }
    std::string getValue() const { return value; }

private:
    TokenType type;
    std::string value;
};

// --- Lexer Class ---
class Lexer {
public:
    Lexer(const std::string& source) : source(source), pos(0) {}

    std::vector<Token> tokenize() {
        std::vector<Token> tokens;
        while (!isAtEnd()) {
            char c = currentChar();

            if (isspace(c)) {
                advance();  // Skip whitespace
                continue;
            }

            if (c == '"') {  // Handle string literals
                advance();  // Skip the opening quote
                std::string value;
                while (!isAtEnd() && currentChar() != '"') {
                    value += currentChar();
                    advance();
                }
                if (currentChar() == '"') {
                    tokens.push_back(Token(TokenType::STRING, value));
                    advance();  // Skip the closing quote
                }
                else {
                    throw std::runtime_error("Unterminated string literal");
                }
            }
            else if (c == ';') {  // Handle semicolons
                tokens.push_back(Token(TokenType::SEMICOLON, ";"));
                advance();
            }
            else if (source.substr(pos, 5) == "print") {  // Handle "print" keyword
                tokens.push_back(Token(TokenType::PRINT, "print"));
                pos += 5;  // Skip the word "print"
            }
            else if (c == '(') {  // Handle left parenthesis
                tokens.push_back(Token(TokenType::LEFT_PAREN, "("));
                advance();
            }
            else if (c == ')') {  // Handle right parenthesis
                tokens.push_back(Token(TokenType::RIGHT_PAREN, ")"));
                advance();
            }
            else {
                tokens.push_back(Token(TokenType::UNKNOWN, std::string(1, c)));
                advance();
            }
        }

        tokens.push_back(Token(TokenType::END_OF_FILE, ""));
        return tokens;
    }

private:
    std::string source;
    size_t pos;

    char currentChar() const { return source[pos]; }
    void advance() { if (!isAtEnd()) pos++; }
    bool isAtEnd() const { return pos >= source.size(); }
};

// --- Statement Class ---
class Statement {
public:
    virtual ~Statement() = default;
    virtual void execute() = 0;  // All statements must implement execute()
};

// --- PrintStatement Class ---
class PrintStatement : public Statement {
public:
    PrintStatement(const std::string& value) : value(value) {}

    void execute() override {
        std::cout << value << std::endl;
    }

private:
    std::string value;
};

// --- Parser Class ---
class Parser {
public:
    Parser(const std::vector<Token>& tokens) : tokens(tokens), pos(0) {}

    std::shared_ptr<Statement> parse() {
        // Start by parsing the first statement (in this case, only print is supported)
        if (tokens[pos].getType() == TokenType::PRINT) {
            return parsePrintStatement();
        }
        return nullptr;
    }

private:
    std::vector<Token> tokens;
    size_t pos;

    Token currentToken() { return tokens[pos]; }
    Token consume() { return tokens[pos++]; }
    bool isAtEnd() const { return pos >= tokens.size(); }

    // Parse the print statement
    std::shared_ptr<Statement> parsePrintStatement() {
        consume();  // Consume 'print'

        // Expect opening parenthesis
        if (currentToken().getType() != TokenType::LEFT_PAREN) {
            throw std::runtime_error("Expected '(' after 'print'");
        }
        consume();  // Consume '('

        // Expect a string literal
        if (currentToken().getType() != TokenType::STRING) {
            throw std::runtime_error("Expected a string literal after '('");
        }
        std::string value = currentToken().getValue();
        consume();  // Consume string literal

        // Expect closing parenthesis
        if (currentToken().getType() != TokenType::RIGHT_PAREN) {
            throw std::runtime_error("Expected ')' after string literal");
        }
        consume();  // Consume ')'

        // Expect semicolon
        if (currentToken().getType() != TokenType::SEMICOLON) {
            throw std::runtime_error("Expected ';' after 'print' statement");
        }
        consume();  // Consume semicolon

        return std::make_shared<PrintStatement>(value);
    }
};

// --- Main Function ---
int main() {
    try {
        std::string source = "print(\"Hello World\");";  // Simple input program

        // Tokenize the input source
        Lexer lexer(source);
        std::vector<Token> tokens = lexer.tokenize();

        // Parse the tokens into a statement
        Parser parser(tokens);
        auto statement = parser.parse();

        // Execute the statement
        if (statement) {
            statement->execute();
        }
        else {
            std::cerr << "Error: Invalid statement" << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
