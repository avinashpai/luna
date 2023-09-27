//
// Created by Avinash Pai on 9/12/23.
//

#include <iostream>
#include "parser.h"

auto Parser::parse_prog() -> std::optional<NodeProg> {
    std::vector<NodeStatement> stats;
    while (peek().has_value()) {
        while (auto stat = parse_stat()) {
            stats.push_back(stat.value());
        }
    }
    if (stats.empty()) {
        return {};
    } else {
        return NodeProg {
            .stats = stats
        };
    }
}

auto Parser::parse_stat() -> std::optional<NodeStatement> {
    if (peek().has_value()) {
        switch(peek().value().type) {
            case TokenType::PRINT: {
                advance();
                if (peek().has_value() &&
                    peek().value().type == TokenType::LEFT_PAREN) {
                    // Assume single token expr ?
                    NodeStatement stat = NodeFuncCall {
                        .ident = {advance()},
                        .param = parse_expr()
                    };

                    if (peek().has_value() && peek().value().type == TokenType::RIGHT_PAREN) {
                       advance();
                       if (peek().has_value() && peek().value().type == TokenType::SEMI_COLON) {
                           advance();
                           return stat;
                       } else {
                           if (peek().has_value()) {
                               std::cerr << "Missing semi-colon at " << peek().value().line << ":" << peek().value().column <<
                                "\n";
                           } else {
                               // TODO:
                           }
                           return {};
                       }
                    } else {
                        if (peek().has_value()) {
                            std::cerr << "Missing closing paren after function call. Expected: `)` at " << peek().value().line <<
                                ":" << peek().value().column << "\n";
                        } else {
                            // TODO:
                        }
                        return {};
                    }
                }
            }
            default:
                return {};
        }
    } else {
       return {};
    }
}

auto Parser::parse_expr() -> std::optional<NodeExpr> {
    if (peek().has_value()) {
        // TODO: Unary and Binary Expressions
        switch(peek().value().type) {
            case TokenType::IDENTIFER:
                return NodeIdent { .ident = advance() };
            case TokenType::NUMBER_LITERAL:
            case TokenType::STRING_LITERAL:
                return NodeLiteral { .literal = advance() };
            default:
                return {};
        }
    }
    else {
        return {};
    }
}

auto Parser::peek(int offset) const -> std::optional<Token> {
    if (m_index + offset< m_tokens.size()) {
        return m_tokens.at(m_index + offset);
    } else {
        return {};
    }
}

auto Parser::advance() -> Token {
    return m_tokens.at(m_index++);
}

