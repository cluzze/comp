#include "lexer.h"

#include <iostream>

namespace cc {
  Lexer::Lexer(const std::string& filename) : sourceFileName(filename) {
    std::ifstream sourceFile(filename);
    if (!sourceFile) {
      std::cerr << "File: " << filename << "not found\n";
      exit(1);
    }
    sourceFile.seekg(0, std::ios::end);
    std::streampos sourceSize = sourceFile.tellg();
    sourceCode.reserve(sourceSize);
    sourceFile.seekg(0, std::ios::beg);
    sourceCode.assign((std::istreambuf_iterator<char>(sourceFile)), std::istreambuf_iterator<char>());
    sourceFile.close();
  }

  void Lexer::printSource() {
    for (const char& c : sourceCode)
      std::cout << c;
  }

  void Lexer::skipWhitespaces() {
    while (lexPos <= sourceCode.size() && std::isspace(sourceCode[lexPos]))
      ++charNum;
      if (sourceCode[lexPos] == '\n') {
        ++lineNum;
        charNum = 0;
      }
      ++lexPos;
  }

  void Lexer::matchKeyWord() {
    
  }

  std::vector<Token> Lexer::lex() {

  }
}