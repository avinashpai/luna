#include <fstream>
#include <iostream>
#include <sstream>

#include "lexer.h"
#include "parser.h"

void print_usage() {
    std::cout << "Usage:\n"
                 "\tluna <input_file>" << std::endl;
}

static std::string get_source_string(const char* source_file) {
    std::stringstream content_stream;
    if (std::filesystem::exists(source_file)) {
        std::fstream input_stream(source_file);
        content_stream << input_stream.rdbuf();
    } else {
        std::cerr << "File not found. Please provide a valid input file.\n";
        print_usage();
        exit(EXIT_FAILURE);

    }

    return { content_stream.str() };
}

static void dump_tokens(const std::vector<Token>& tokens) {
    std::cout << "Tokens: \n";
    for (const auto& token : tokens) {
        std::cout << "[(" << token.pos  << ") Type: " << TOKEN_TYPE_STRS.at(TOKEN_TYPE_AS_INT(token.type)) << " =  " <<
                  token.value.value_or("null") << "]\n";
    }
}

int main(int argc, char* argv[]) {
   if (argc != 2) {
       print_usage();
       exit(EXIT_FAILURE);
   }

   const char* source_file = argv[1];
   std::string source = get_source_string(source_file);

   auto lexer = Lexer(source);
   std::vector<Token> tokens = lexer.tokenize();
   dump_tokens(tokens);

   auto parser = Parser(tokens);


   return EXIT_SUCCESS;
}
