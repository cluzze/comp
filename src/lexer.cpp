#include "lexer.h"

#include <regex>
#include <iostream>

namespace cc {
  Token::Token(Type k, const std::string& v) : type(k), value(v) {}

  Token::Type Token::getType() const { return type; }
  std::string Token::getValue() const { return value; }

  void Token::print() const {
    switch (type) {
    case Type::IDENTIFIER:
        std::cout << "IDENTIFIER";
        break;
    case Type::INTEGER:
        std::cout << "INTEGER, value: " << value;
        break;
    case Type::IF:
        std::cout << "IF";
        break;
    case Type::WHILE:
        std::cout << "WHILE";
        break;
    case Type::PRINT:
        std::cout << "PRINT";
        break;
    case Type::READ:
        std::cout << "READ";
        break;
    case Type::EQ:
        std::cout << "EQ";
        break;
    case Type::PLUS:
        std::cout << "PLUS";
        break;
    case Type::MINUS:
        std::cout << "MINUS";
        break;
    case Type::MUL:
        std::cout << "MUL";
        break;
    case Type::DIV:
        std::cout << "DIV";
        break;
    case Type::LESS:
        std::cout << "LESS";
        break;
    case Type::GREATER:
        std::cout << "GREATER";
        break;
    case Type::SEMICOLON:
        std::cout << "SEMICOLON";
        break;
    case Type::LEFTPAREN:
        std::cout << "LEFTPAREN";
        break;
    case Type::RIGHTPAREN:
        std::cout << "RIGHTPAREN";
        break;
    case Type::LEFTBRACE:
        std::cout << "LEFTBRACE";
        break;
    case Type::RIGHTBRACE:
        std::cout << "RIGHTBRACE";
        break;
    case Type::UNKNOWN:
        std::cout << "UNKNOWN";
        break;
    case Type::END:
        std::cout << "END";
        break;
    default:
        std::cerr << "Error: Unexpected token type";
        exit(1);
    }
  }

  Lexer::Lexer(const std::string& filename) : sourceFileName(filename) {
    std::ifstream sourceFile(filename);
    if (!sourceFile) {
      std::cerr << "Error: File: " << filename << "not found\n";
      exit(1);
    }
    sourceFile.seekg(0, std::ios::end);
    std::streampos sourceSize = sourceFile.tellg();
    sourceCode.reserve(sourceSize);
    sourceFile.seekg(0, std::ios::beg);
    sourceCode.assign((std::istreambuf_iterator<char>(sourceFile)), std::istreambuf_iterator<char>());
    sourceFile.close();
  }

  void Lexer::printSource() const {
    for (const char& c : sourceCode)
      std::cout << c;
  }

  void Lexer::printTokens() const {
    for (const Token& tok : tokens) {
      tok.print();
      std::cout << " ";
    }
  }

  bool Lexer::skipSpace(char c) {
    if (!std::isspace(c))
      return false;
    lexPos++;
    charNum++;
    if (c == '\n') {
      charNum = 1;
      lineNum++;
    }
    return true;
  }

  static Token getKeywordOrIdentifier(const std::string& Id) {
    if (Id == "if") return Token(Token::Type::IF, Id);
    if (Id == "while") return Token(Token::Type::WHILE, Id);
    if (Id == "print") return Token(Token::Type::PRINT, Id);
    return Token(Token::Type::IDENTIFIER, Id);
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
        return Token(Token::Type::INTEGER, Id);
      }
      switch (Cur) {
        case '=':
          ++lexPos;
          ++charNum;
          return Token(Token::Type::EQ, "=");
        case '+':
          ++lexPos;
          ++charNum;
          return Token(Token::Type::PLUS, "+");
        case '-':
          ++lexPos;
          ++charNum;
          return Token(Token::Type::MINUS, "-");
        case '*':
          ++lexPos;
          ++charNum;
          return Token(Token::Type::MUL, "*");
        case '/':
          ++lexPos;
          ++charNum;
          return Token(Token::Type::DIV, "/");
        case ';':
          ++lexPos;
          ++charNum;
          return Token(Token::Type::SEMICOLON, ";");
        case '>':
          ++lexPos;
          ++charNum;
          return Token(Token::Type::GREATER, ";");
        case '<':
          ++lexPos;
          ++charNum;
          return Token(Token::Type::LESS, ";");
        case '(':
          ++lexPos;
          ++charNum;
          return Token(Token::Type::LEFTPAREN, "(");
        case ')':
          ++lexPos;
          ++charNum;
          return Token(Token::Type::RIGHTPAREN, ")");
        case '{':
          ++lexPos;
          ++charNum;
          return Token(Token::Type::LEFTBRACE, "{");
        case '}':
          ++lexPos;
          ++charNum;
          return Token(Token::Type::RIGHTBRACE, "}");
        case '?':
          ++lexPos;
          ++charNum;
          return Token(Token::Type::READ, "?");
        default:
          ++lexPos;
          ++charNum;
          return Token(Token::Type::UNKNOWN, std::string{Cur});
      }
    }
    return {Token::Type::END, ""};
  }

  std::vector<Token> Lexer::lex() {
    Token tok(Token::Type::UNKNOWN, "");
    while (tok.getType() != Token::Type::END) {
      tok = nextToken();
      if (tok.getType() == Token::Type::UNKNOWN) {
        std::cerr << "Error: Unknown: '" << tok.getValue() << "' at:" << sourceFileName << ":" << lineNum << ":" << charNum << "\n";
        exit(1);
      }
      tokens.push_back(tok);
    }
    return tokens;
  }
}