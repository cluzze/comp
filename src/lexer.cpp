#include "lexer.h"

#include <regex>
#include <iostream>

namespace cc {
  Token::Token(Kind k, const std::string& v) : kind(k), value(v) {}

  Token::Kind Token::getType() const { return kind; }

  void Token::print() const {
    switch (kind) {
    case Kind::IDENTIFIER:
        std::cout << "IDENTIFIER\n";
        break;
    case Kind::INTEGER:
        std::cout << "INTEGER, value: " << value << "\n";
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
    case Kind::PLUS:
        std::cout << "PLUS\n";
        break;
    case Kind::MINUS:
        std::cout << "MINUS\n";
        break;
    case Kind::MUL:
        std::cout << "MUL\n";
        break;
    case Kind::DIV:
        std::cout << "DIV\n";
        break;
    case Kind::LESS:
        std::cout << "LESS\n";
        break;
    case Kind::GREATER:
        std::cout << "GREATER\n";
        break;
    case Kind::SEMICOLON:
        std::cout << "SEMICOLON\n";
        break;
    case Kind::LEFTPAREN:
        std::cout << "LEFTPAREN\n";
        break;
    case Kind::RIGHTPAREN:
        std::cout << "RIGHTPAREN\n";
        break;
    case Kind::LEFTBRACE:
        std::cout << "LEFTBRACE\n";
        break;
    case Kind::RIGHTBRACE:
        std::cout << "RIGHTBRACE\n";
        break;
    case Kind::UNKNOWN:
        std::cout << "UNKNOWN\n";
        break;
    case Kind::END:
        std::cout << "END\n";
        break;
    default:
        std::cerr << "Unexpected token type\n";
        exit(1);
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

  bool Lexer::skipSpace(char c) {
    if (!std::isspace(c))
      return false;
    lexPos++;
    charNum++;
    if (c == '\n') {
      charNum = 0;
      lineNum++;
    }
    return true;
  }

  static Token getKeywordOrIdentifier(const std::string& Id) {
    if (Id == "if") return Token(Token::Kind::IF, Id);
    if (Id == "while") return Token(Token::Kind::WHILE, Id);
    if (Id == "print") return Token(Token::Kind::PRINT, Id);
    return Token(Token::Kind::IDENTIFIER, Id);
  }

  Token Lexer::nextToken() {
    while (lexPos < sourceCode.size()) {
      char Cur = sourceCode[lexPos];
      if (skipSpace(Cur))
        continue;
      if (std::isalpha(Cur)) {
        std::string Id;
        while (lexPos < sourceCode.size() && std::isalnum(sourceCode[lexPos]) || sourceCode[lexPos] == '_') {
            Id += sourceCode[lexPos];
            ++lexPos;
        }
        return getKeywordOrIdentifier(Id);
      }
      if (std::isdigit(Cur)) {
        std::string Id;
        while (lexPos < sourceCode.size() && std::isdigit(sourceCode[lexPos])) {
            Id += sourceCode[lexPos];
            ++lexPos;
        }
        return Token(Token::Kind::INTEGER, Id);
      }
      switch (Cur) {
        case '=':
          ++lexPos;
          ++charNum;
          return Token(Token::Kind::EQ, "=");
        case '+':
          ++lexPos;
          ++charNum;
          return Token(Token::Kind::PLUS, "+");
        case '-':
          ++lexPos;
          ++charNum;
          return Token(Token::Kind::MINUS, "-");
        case '*':
          ++lexPos;
          ++charNum;
          return Token(Token::Kind::MUL, "*");
        case '/':
          ++lexPos;
          ++charNum;
          return Token(Token::Kind::DIV, "/");
        case ';':
          ++lexPos;
          ++charNum;
          return Token(Token::Kind::SEMICOLON, ";");
        case '>':
          ++lexPos;
          ++charNum;
          return Token(Token::Kind::GREATER, ";");
        case '<':
          ++lexPos;
          ++charNum;
          return Token(Token::Kind::LESS, ";");
        case '(':
          ++lexPos;
          ++charNum;
          return Token(Token::Kind::LEFTPAREN, "(");
        case ')':
          ++lexPos;
          ++charNum;
          return Token(Token::Kind::RIGHTPAREN, ")");
        case '{':
          ++lexPos;
          ++charNum;
          return Token(Token::Kind::LEFTBRACE, "{");
        case '}':
          ++lexPos;
          ++charNum;
          return Token(Token::Kind::RIGHTBRACE, "}");
        case '?':
          ++lexPos;
          ++charNum;
          return Token(Token::Kind::READ, "?");
        default:
          ++lexPos;
          ++charNum;
          return Token(Token::Kind::UNKNOWN, std::string{Cur});
      }
    }
    return {Token::Kind::END, "\\0"};
  }

  std::vector<Token> Lexer::lex() {
    Token tok(Token::Kind::UNKNOWN, "");
    while (tok.getType() != Token::Kind::END) {
      tok = nextToken();
      tokens.push_back(tok);
    }
    return tokens;
  }
}