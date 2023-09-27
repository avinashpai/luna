//
// Created by Avinash Pai on 9/12/23.
//

#pragma once

#include <array>
#include <map>
#include <optional>
#include <string>

#define TOKEN_TYPE_AS_INT(token) static_cast<int>((token))

enum class TokenType: uint8_t {
    IDENTIFER = 0,
    NUMBER_LITERAL,
    STRING_LITERAL,
    CHAR_LITERAL,
    LEFT_PAREN, RIGHT_PAREN,
    LEFT_BRACE, RIGHT_BRACE,
    LEFT_BRACKET, RIGHT_BRACKET,
    EQUALS,
    COMMA, DOT,
    MINUS, PLUS,
    FORWARD_SLASH, STAR,
    SEMI_COLON,
    COLON,
    // KEYWORDS
    IF, ELSE,
    TRUE, FALSE,
    FOR, BREAK,
    WHILE, CONTINUE,
    INT, STR, BOOL,
    PRINT, EXIT,
    FN, MAIN,
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
        "fn", "main",
        // Built-in functions
        "print", "exit"
};

constexpr std::array TOKEN_TYPE_STRS = {
        "Identifier",
        "Number",
        "String",
        "Character",
        "\'(\'",
        "\')\'",
        "\'{\'",
        "\'}\'",
        "\'[\'",
        "\']\'",
        "\'=\'",
        "\',\'",
        "\'.\'",
        "\'-\'",
        "\'+\'",
        "\'/\'",
        "\'*\'",
        "\';\'",
        "\':\'",
        "IF", "ELSE",
        "TRUE", "FALSE",
        "FOR", "BREAK",
        "WHILE", "CONTINUE",
        "INT", "STR", "BOOL",
        "PRINT", "EXIT",
        "FN", "MAIN",
        "Unknown"
};

typedef struct Token {
    size_t line;
    size_t column;
    TokenType type;
    std::optional<std::string> value;
} Token;