//
// Created by Avinash Pai on 9/12/23.
//

#pragma once

#include <array>
#include <optional>
#include <string>

#define TOKEN_TYPE_AS_INT(token) static_cast<int>((token))

enum class TokenType: uint8_t {
    IDENTIFER = 0,
    NUMBER_LITERAL,
    STRING_LITERAL,
    LEFT_PAREN, RIGHT_PAREN,
    LEFT_BRACE, RIGHT_BRACE,
    LEFT_BRACKET, RIGHT_BRACKET,
    EQUALS,
    COMMA, DOT,
    MINUS, PLUS,
    FORWARD_SLASH, STAR,
    SEMI_COLON,
    COLON,
    KEYWORD,
    NONE [[maybe_unused]]
};

constexpr std::array KEYWORDS = {
        // Control Flow
        "if", "else",
        "true", "false",
        "while", "for",
        "continue", "break",
        "return",
        // Types
        "int", "str", "bool",
        // Built-in functions
        "print", "exit"
};

constexpr std::array TOKEN_TYPE_STRS = {
        "Identifier",
        "Number",
        "String",
        "Left Paren",
        "Right Paren",
        "Left Brace",
        "Right Brace",
        "Left Bracket",
        "Right Bracket",
        "Equals",
        "Comma",
        "Dot",
        "Minus",
        "Plus",
        "Forward Slash",
        "Star",
        "Semicolon",
        "Colon",
        "Keyword",
        "Unknown"
};

typedef struct Token {
    size_t pos;
    TokenType type;
    std::optional<std::string> value;
} Token;