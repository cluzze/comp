#include <iostream>

#include "lexer.h"

int main(int argc, char **argv) {
  if (argc != 2)
    std::cerr << "Not enough arguments, Usage: ./cc filename\n";
  cc::Lexer lexer{std::string(argv[1])};
  lexer.printSource();
}