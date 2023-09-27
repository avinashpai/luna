//
// Created by Avinash Pai on 9/5/23.
//

#include "lexer.h"

auto Lexer::build_token(TokenType type) -> Token {
    char c = peek().value();
    size_t line = m_line;
    size_t column = m_column;
    std::string temp{c};
    advance();

    switch (type) {
        case TokenType::IDENTIFER:
            while (peek().has_value() && (peek().value() == '_' || isalnum(peek().value()))) {
                temp.push_back(advance());
            }
            if (std::find(KEYWORDS.begin(), KEYWORDS.end(), temp) != KEYWORDS.end())
                type = KEYWORD_LUT.at(temp);
            break;
        case TokenType::NUMBER_LITERAL:
            while (peek().has_value() && isdigit(peek().value())) {
                temp.push_back(advance());
            }
            break;
        case TokenType::STRING_LITERAL:
            while (peek().has_value() && peek().value() != '"' && peek().value() != '\n') {
                temp.push_back(advance());
            }
            if (peek().has_value() && peek().value() == '"') {
                advance();
            } else if (peek().has_value() && peek().value() == '\n') {
                std::cerr << "[" << m_index << "] " << "String literals must be single line. Mult-line strings are TBD.\n";
                exit(EXIT_FAILURE);
            } else {
                std::cerr << "[" << m_index << "] " << "Unterminated string literal, missing closing \"\n";
                exit(EXIT_FAILURE);
            }
            break;
        case TokenType::CHAR_LITERAL:
            while (peek().has_value() && peek().value() != '\'' && peek().value() != '\n') {
                temp.push_back(advance());
            }
            if (peek().has_value() && peek().value() == '\'') {
                advance();
            } else if (peek().has_value() && peek().value() == '\n') {
                std::cerr << "[" << m_index << "] " << "Unexpected newline. Expected: `\'`";
                exit(EXIT_FAILURE);
            } else {
                std::cerr << "[" << m_index << "] " << "Unterminated character literal, missing closing \'\n";
                exit(EXIT_FAILURE);
            }
            break;
        default:
            std::cerr << "Cannot build token for type: " << TOKEN_TYPE_STRS.at(TOKEN_TYPE_AS_INT(type)) << "\n";
            break;
    }


    return {.line = line, .column = column, .type = type, .value = temp};
}

auto Lexer::tokenize() -> std::vector<Token> {
    std::vector<Token> tokens {};
    char c;
    while(peek().has_value()) {
        c = peek().value();
        if (isdigit(c)) {
            if (c == '0') {
                std::cerr << "[" << m_index << "] " << "Leading 0 numbers are not allowed.\n";
                exit(EXIT_FAILURE);
            }
            tokens.push_back(build_token(TokenType::NUMBER_LITERAL));
            continue;
        } else if (c == '_' || isalpha(c)) {
            tokens.push_back(build_token(TokenType::IDENTIFER));
            continue;
        } else if (c == '"') {
            advance();
            if (peek().has_value() && peek().value() != '"') {
                if (peek().has_value() && peek().value() == '\n') {
                    std::cerr << "[" << m_index << "] "
                              << "String literals must be single line. Mult-line strings are TBD.\n";
                    exit(EXIT_FAILURE);
                }
                tokens.push_back(build_token(TokenType::STRING_LITERAL));
                continue;
            } else {
                tokens.push_back(Token{.line = m_line, .column = m_column, .type = TokenType::STRING_LITERAL, .value = {}});
            }
        } else if (c == '\'') {
            advance();
            if (peek().has_value() && peek().value() != '\'') {
                if (peek().has_value() && peek().value() == '\n') {
                    std::cerr << "[" << m_index << "] "
                              << "Unexpected newline. Expected: `\'`\n";
                    exit(EXIT_FAILURE);
                }
                tokens.push_back(build_token(TokenType::CHAR_LITERAL));
                continue;
            } else {
                std::cerr << "[" << m_index << "] " << "Empty character literal has no meaning\n";
                exit(EXIT_FAILURE);
            }
        } else if (c == '/' && peek(1).has_value() && peek(1).value() == '/') {
            while (peek().has_value() && advance() != '\n')
                ;
            continue;
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
                default:
                    std::cerr << "[" << m_index << "] " << "Unknown Token: " << "\"" << c << "\"\n";
                    exit(EXIT_FAILURE);
            }
            tokens.push_back(Token{.line = m_line, .column = m_column, .type = type, .value = {}});
        }
        advance();
    }
    return tokens;
}

 auto Lexer::peek(int offset) const -> std::optional<char> {
    if (m_index + offset< m_src.length()) {
        return m_src.at(m_index + offset);
    } else {
        return {};
    }
}

auto Lexer::advance() -> char {
    char c = m_src.at(m_index++);
    if (c == '\n') {
        m_line++;
        m_column = 1;
    } else {
        m_column++;
    }
    return c;
}