#pragma once

#include <fstream>
#include <string>
#include <vector>

namespace cc {
  class Token {
  public:
    enum class Kind {
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
    Token(Kind k = Kind::UNKNOWN, const std::string& v = 0);

    Kind getType() const;
    void print() const;
  private:
    Kind kind;
    std::string value;
  };

  class Lexer {
  public:
    Lexer(const std::string& filename);

    void printSource();
    void printTokens();

    std::vector<Token> lex();
  private:
    Token nextToken();
    bool skipSpace(char c);
  private:
    size_t lexPos = 0;
    size_t lineNum = 0, charNum = 0;
    std::string sourceFileName;
    std::vector<char> sourceCode{};
    std::vector<Token> tokens{};
  };
}