#pragma once

#include <fstream>
#include <string>
#include <vector>

namespace cc {
  class Lexer {
  public:
    Lexer(const std::string& filename);
  private:
    std::string sourceFileName;
    std::vector<char> sourceCode;
  };
}