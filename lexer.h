//
// Created by Avinash Pai on 9/5/23.
//

#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "token.h"

extern void print_usage();

class Lexer {
public:
   inline explicit Lexer(std::string_view source) :
    m_src(source) {}

   std::vector<Token> tokenize();
   inline void dump_source() {
       std::cout << "Dumping Lexer Source: " << m_src << std::endl;
   }

private:
    [[nodiscard]] Token build_token(TokenType type);
    [[nodiscard]] std::optional<char> peek(int offset = 0) const;
    inline char consume() {
        return m_src.at(m_index++);
    }

    std::string_view m_src;
    size_t m_index = 0;
};