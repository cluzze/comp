#pragma once

#include <fstream>
#include <string>
#include <vector>

namespace cc {
  struct Token {
  public:
    std::string name;
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
  private:
    size_t lexPos = 0;
    size_t lineNum = 0, charNum = 0;
    std::string sourceFileName;
    std::vector<char> sourceCode{};
    std::vector<Token> tokens{};
  };
}