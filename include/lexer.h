#pragma once

#include <fstream>
#include <string>
#include <vector>

namespace cc {
  class Token {
  public:
    enum class Kind {
      ID = 0,
      I_CONST,
      IF,
      WHILE,
      PRINT,
      READ,
      EQ,
      LESS,
      GREATER,
      S_COLON,
      L_PAREN,
      R_PAREN,
      L_BRACE,
      R_BRACE,
      UNKNOWN
    };
  public:
    Token(Kind k = Kind::UNKNOWN, int v = 0);

    Kind getType() const;
    void print() const;
  private:
    Kind kind;
    int value;
  };

  class Lexer {
  public:
    Lexer(const std::string& filename);

    void printSource();
    void printTokens();

    std::vector<Token> lex();
  private:
    void skipWhitespaces();
    std::string readNextWord();
    Token matchToken(const std::string& word);

  private:
    size_t lexPos = 0;
    size_t lineNum = 0, charNum = 0;
    std::string sourceFileName;
    std::vector<char> sourceCode{};
    std::vector<Token> tokens{};
  };
}