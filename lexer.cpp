//
// Created by Avinash Pai on 9/5/23.
//

#include "lexer.h"

Token Lexer::build_token(TokenType type) {
    char c = peek().value();
    size_t pos = m_index;
    std::string temp{c};
    consume();

    switch (type) {
        case TokenType::IDENTIFER:
            while (peek().has_value() && (peek().value() == '_' || isalnum(peek().value()))) {
                temp.push_back(consume());
            }
            if (std::find(KEYWORDS.begin(), KEYWORDS.end(), temp) != KEYWORDS.end())
                type = TokenType::KEYWORD;
            break;
        case TokenType::NUMBER_LITERAL:
            while (peek().has_value() && isdigit(peek().value())) {
                temp.push_back(consume());
            }
            break;
        case TokenType::STRING_LITERAL:
            while (peek().has_value() && peek().value() != '"') {
                temp.push_back(consume());
            }
            if (peek().has_value() && peek().value() == '"') {
                consume();
            } else {
                std::cerr << "[" << m_index << "] " << "Unterminated string literal, missing closing \"\n";
                exit(EXIT_FAILURE);
            }
            break;
        default:
            std::cerr << "Cannot build token for type: " << TOKEN_TYPE_STRS.at(TOKEN_TYPE_AS_INT(type)) << "\n";
            break;
    }


    return {.pos = pos, .type = type, .value = temp};
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens {};
    char c;
    while(peek().has_value()) {
        c = peek().value();
        if (isdigit(c)) {
            tokens.push_back(build_token(TokenType::NUMBER_LITERAL));
            continue;
        } else if (c == '_' || isalpha(c)) {
            tokens.push_back(build_token(TokenType::IDENTIFER));
            continue;
        } else if (c == '"') {
           consume();
           if (peek().has_value() && peek().value() != '"') {
               tokens.push_back(build_token(TokenType::STRING_LITERAL));
               continue;
           } else {
               tokens.push_back(Token{.pos = m_index, .type = TokenType::STRING_LITERAL, .value = {}});
           }
        } else if (!isspace(c)){
            TokenType type;
            switch (c) {
                case '(':
                    type = TokenType::LEFT_PAREN;
                    break;
                case ')':
                    type = TokenType::RIGHT_PAREN;
                    break;
                case '{':
                    type = TokenType::LEFT_BRACE;
                    break;
                case '}':
                    type = TokenType::RIGHT_BRACE;
                    break;
                case '[':
                    type = TokenType::LEFT_BRACKET;
                    break;
                case ']':
                    type = TokenType::RIGHT_BRACKET;
                    break;
                case ':':
                    type = TokenType::COLON;
                    break;
                case ';':
                    type = TokenType::SEMI_COLON;
                    break;
                case '=':
                    type = TokenType::EQUALS;
                    break;
                case '+':
                    type = TokenType::PLUS;
                    break;
                case '-':
                    type = TokenType::MINUS;
                    break;
                case '*':
                    type = TokenType::STAR;
                    break;
                case '/':
                    type = TokenType::FORWARD_SLASH;
                    break;
                case '.':
                    type = TokenType::DOT;
                    break;
                case ',':
                    type = TokenType::COMMA;
                    break;
//                case '\'':
//                    // TODO char literal?
//                    break;
                default:
                    std::cerr << "Unknown Token: " << "\"" << c << "\"\n";
                    print_usage();
                    exit(EXIT_FAILURE);
            }
            tokens.push_back(Token{.pos = m_index, .type = type, .value = {}});
        }
        consume();
    }
    return tokens;
}

std::optional<char> Lexer::peek(int offset) const {
    if (m_index + offset < m_src.length()) {
        return m_src.at(m_index + offset);
    } else {
        return {};
    }
}