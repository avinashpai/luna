//
// Created by Avinash Pai on 9/5/23.
//

#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "token.h"


class Lexer {
public:
   explicit Lexer(std::string_view source) :
        m_src(source) {}

   auto tokenize() -> std::vector<Token>;

private:
    [[nodiscard]] auto build_token(TokenType type) -> Token;
    [[nodiscard]] auto peek(int offset = 0) const -> std::optional<char>;
    auto advance() -> char;

    std::string_view m_src;
    size_t m_index = 0;
    size_t m_line = 1;
    size_t m_column = 1;

    const std::map<std::string_view, TokenType> KEYWORD_LUT = {
            { "if", TokenType::IF }, { "else", TokenType::ELSE },
            { "true", TokenType::TRUE }, { "false", TokenType::FALSE },
            { "while", TokenType::WHILE }, { "for", TokenType::FOR },
            { "continue", TokenType::CONTINUE }, { "break", TokenType::BREAK },
            { "int", TokenType::INT }, { "str", TokenType::STR }, { "bool", TokenType::BOOL },
            { "fn", TokenType::FN }, { "main", TokenType::MAIN },
            { "print", TokenType::PRINT }, { "exit", TokenType::EXIT }
    };
};