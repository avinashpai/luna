//
// Created by Avinash Pai on 9/12/23.
//

#pragma once

#include <vector>
#include "token.h"
#include "node.h"

template<class... Ts>
struct visitor: Ts... { using Ts::operator()...; };
template<class... Ts>
visitor(Ts...) -> visitor<Ts...>;

using namespace Node;

class Parser {
public:
    explicit Parser(std::vector<Token> tokens) :
        m_tokens(std::move(tokens)) {}

    auto parse_prog() -> std::optional<NodeProg>;
    auto parse_stat() -> std::optional<NodeStatement>;
    auto parse_expr() -> std::optional<NodeExpr>;

private:
    [[nodiscard]] auto peek(int offset = 0) const -> std::optional<Token>;
    auto advance() -> Token;
    std::vector<Token> m_tokens;
    size_t m_index = 0;
};