#include "lexer.h"

#include <iostream>

namespace cc {
  Lexer::Lexer(const std::string& filename) : sourceFileName(filename) {
    std::ifstream sourceFile(filename);
    if (!sourceFile)
      std::cerr << "File: " << filename << "not found\n";
  }
}