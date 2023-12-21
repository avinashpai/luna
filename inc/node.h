//
// Created by Avinash Pai on 9/19/23.
//

#pragma once

#include <memory>
#include <variant>
#include <vector>

#include "token.h"

template <typename T>
class Box {
public:
    Box(T &&obj) : _impl(new T(std::move(obj))) {}
    Box(const T &obj) : _impl(new T(obj)) {}

    Box(const Box &other) : Box(*other._impl) {}
    Box &operator=(const Box &other)
    {
        *_impl = *other._impl;
        return *this;
    }

    Box(Box &&other) : Box(std::move(*other._impl)) {}
    Box &operator=(Box &&other) {
        *_impl = std::move(*other._impl);
        return *this;
    }

    ~Box() = default;

    T &operator*() { return *_impl; }
    const T &operator*() const { return *_impl; }

    T *operator->() { return _impl.get(); }
    const T *operator->() const { return _impl.get(); }

private:
    std::unique_ptr<T> _impl;
};

namespace Node {
    struct NodeLiteral {
        Token literal;
    };

    struct NodeIdent {
        Token ident;
    };

    using NodeExpr = std::variant<Box<NodeIdent>, Box<NodeLiteral>, Box<struct NodeBinExpr>, Box<struct NodeUnaryExpr>>;

    struct NodeBinExpr {
        Token op;
        NodeExpr lhs, rhs;
    };

    struct NodeUnaryExpr {
        Token op;
        NodeExpr lhs;
    };

    using NodeStatement = std::variant<Box<struct NodeExprStat>, Box<struct NodeAssignDecl>, Box<struct NodeFuncCall>>;

    struct NodeExprStat {
        NodeExpr lhs;
    };

    struct NodeAssignDecl {
        NodeIdent indet;
        // TODO: Types
        NodeExpr rhs;
    };

    struct NodeFuncCall {
        NodeIdent ident;
        // TODO: Function call parameters
        std::optional<NodeExpr> param;
    };

    struct NodeProg {
        std::vector<NodeStatement> stats;
    };
}
