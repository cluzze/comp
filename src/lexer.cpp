#include "lexer.h"

#include <regex>
#include <iostream>

namespace cc {
  Token::Token(Kind k, int v) : kind(k), value(v) {}

  Token::Kind Token::getType() const { return kind; }

  void Token::print() const {
    switch (kind) {
    case Kind::ID:
        std::cout << "ID\n";
        break;
    case Kind::I_CONST:
        std::cout << "I_CONST, value: " << value << "\n";
        break;
    case Kind::IF:
        std::cout << "IF\n";
        break;
    case Kind::WHILE:
        std::cout << "WHILE\n";
        break;
    case Kind::PRINT:
        std::cout << "PRINT\n";
        break;
    case Kind::READ:
        std::cout << "READ\n";
        break;
    case Kind::EQ:
        std::cout << "EQ\n";
        break;
    case Kind::LESS:
        std::cout << "LESS\n";
        break;
    case Kind::GREATER:
        std::cout << "GREATER\n";
        break;
    case Kind::S_COLON:
        std::cout << "S_COLON\n";
        break;
    case Kind::L_PAREN:
        std::cout << "L_PAREN\n";
        break;
    case Kind::R_PAREN:
        std::cout << "R_PAREN\n";
        break;
    case Kind::L_BRACE:
        std::cout << "L_BRACE\n";
        break;
    case Kind::R_BRACE:
        std::cout << "R_BRACE\n";
        break;
    case Kind::UNKNOWN:
    default:
        std::cout << "UNKNOWN\n";
        break;
    }
  }

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

  void Lexer::printTokens() {
    for (const Token& tok : tokens) {
      tok.print();
    }
  }

  void Lexer::skipWhitespaces() {
    while (lexPos < sourceCode.size() && std::isspace(sourceCode[lexPos])) {
      ++charNum;
      if (sourceCode[lexPos] == '\n') {
        ++lineNum;
        charNum = 0;
      }
      ++lexPos;
    }
  }

  std::string Lexer::readNextWord() {
    std::string nextWord;
    while (lexPos < sourceCode.size() && !std::isspace(sourceCode[lexPos])) {
      nextWord.push_back(sourceCode[lexPos]);
      ++charNum;
      ++lexPos;
    }
    return nextWord;
  }

  Token Lexer::matchToken(const std::string& word) {
    if (word == "if")
      return {Token::Kind::IF};
    if (word == "while")
      return {Token::Kind::WHILE};
    if (word == "print")
      return {Token::Kind::PRINT};
    if (word == "?")
      return {Token::Kind::READ};
    if (word == "=")
      return {Token::Kind::EQ};
    if (word == "<")
      return {Token::Kind::LESS};
    if (word == ">")
      return {Token::Kind::GREATER};
    if (word == ";")
      return {Token::Kind::S_COLON};
    if (word == "(")
      return {Token::Kind::L_PAREN};
    if (word == ")")
      return {Token::Kind::R_PAREN};
    if (word == "{")
      return {Token::Kind::L_BRACE};
    if (word == "}")
      return {Token::Kind::R_BRACE};

    const std::regex decimalIConstRegex(R"([-+]?[0-9]+)");
    const std::regex identifierRegex(R"(^[a-zA-Z_][a-zA-Z0-9_]*$)");
    std::cout << "\n" << word << "\n";
    if (std::regex_match(word, decimalIConstRegex))
      return {Token::Kind::L_BRACE, std::stoi(word)};
    if (std::regex_match(word, identifierRegex))
      return {Token::Kind::ID};
    return {Token::Kind::UNKNOWN};
  }

  std::vector<Token> Lexer::lex() {
    skipWhitespaces();
    while (lexPos < sourceCode.size() - 1) {
      std::string nextWord = readNextWord();
      Token tok = matchToken(nextWord);
      if (tok.getType() == Token::Kind::UNKNOWN) {
        std::cerr << "Unknown token: " << nextWord << " at: " 
            << sourceFileName << ":" << lineNum << ":" << charNum << "\n";
        exit(1);
      }
      tokens.push_back(tok);
      skipWhitespaces();
    }
    return tokens;
  }
}