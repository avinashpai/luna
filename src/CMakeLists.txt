SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} '-std=c++17'")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} '-std=c++17'")

include_directories(${luna_SOURCE_DIR}/inc)
add_executable(luna main.cpp lexer.cpp parser.cpp)
