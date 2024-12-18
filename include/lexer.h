#pragma once

#include <fstream>
#include <string>
#include <vector>

namespace cc {
  class Token {
  public:
    enum class Type {
      IDENTIFIER = 0,
      INTEGER,
      IF,
      WHILE,
      PRINT,
      READ,
      EQ,
      LESS,
      PLUS,
      MINUS,
      MUL,
      DIV,
      GREATER,
      SEMICOLON,
      LEFTPAREN,
      RIGHTPAREN,
      LEFTBRACE,
      RIGHTBRACE,
      UNKNOWN,
      END
    };
  public:
    Token(Type k = Type::UNKNOWN, const std::string& v = 0);

    Type getType() const;
    std::string getValue() const;
    void print() const;
  private:
    Type type;
    std::string value;
  };

  class Lexer {
  public:
    Lexer(const std::string& filename);
    Lexer(const std::string& s);

    void printSource() const;
    void printTokens() const;

    std::vector<Token> lex();
  private:
    Token nextToken();
    bool skipSpace(char c);
  private:
    size_t lexPos = 0;
    size_t lineNum = 1, charNum = 1;
    std::string sourceFileName;
    std::vector<char> sourceCode{};
    std::vector<Token> tokens{};
  };
}