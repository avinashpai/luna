cmake_minimum_required(VERSION 3.21)
project(luna)

set(CMAKE_CXX_STANDARD 17)

add_executable(luna main.cpp lexer.cpp lexer.h parser.cpp parser.h token.h node.h)
