#include <format>
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


template<typename ... Args>
std::string string_format( const std::string& format, Args ... args )
{
    int size_s = std::snprintf( nullptr, 0, format.c_str(), args ... ) + 1;
    if( size_s <= 0 ){ throw std::runtime_error( "Error during formatting." ); }
    auto size = static_cast<size_t>( size_s );
    std::unique_ptr<char[]> buf( new char[ size ] );
    std::snprintf( buf.get(), size, format.c_str(), args ... );
    return { buf.get(), buf.get() + size - 1 };
}

static void dump_tokens(const std::vector<Token>& tokens) {
    std::cout << "Tokens: \n";
    std::cout << "token[(line:column) TokenType = \"value\" (length)]\n";
    for (const auto& token : tokens) {
        std::cout << string_format("[(%d:%d) %s = %s (%d)]", token.line,
                                   token.column, TOKEN_TYPE_STRS.at(TOKEN_TYPE_AS_INT(token.type)),
                                   token.value.value_or("null").c_str(),
                                   token.value.has_value() ? token.value->length() : 0) << "\n";
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
  // dump_tokens(tokens);

   auto parser = Parser(tokens);
   auto prog = parser.parse_prog();

   if (prog.has_value()) {
       auto stats = prog.value().stats;
       for (auto& stat : stats) {

           struct visitor {
               struct expr_visitor {
                   void operator()(const Box<NodeIdent>& ident) {
                        std::cout << "\t\tIdentifier: " << ident->ident.value.value_or("null") << "\n";
                   }
                   void operator()(const Box<NodeLiteral>& lit) {
                       std::cout << "\t\t" << (lit->literal.type == TokenType::NUMBER_LITERAL ? "Number" : "String")
                        << " literal: " << lit->literal.value.value_or("null") << "\n";
                   }
                   void operator()(const Box<struct NodeBinExpr>& bin_expr) {

                   }
                   void operator()(const Box<struct NodeUnaryExpr>& unary_expr) {

                   }
               };

               void operator()(const Box<struct NodeFuncCall>& stat) {
                    std::cout << "NodeFuncCall: " <<
                        "\n\tfunc: " << "print()" << "\n\t" <<
                        "params: \n";
                    std::visit(expr_visitor{}, stat->param.value());
               }
               void operator()(const Box<struct NodeExprStat>& stat) {

               }
               void operator()(const Box<struct NodeAssignDecl>& stat) {

               }
           };

           std::visit(visitor{}, stat);
       }
   }

   return EXIT_SUCCESS;
}
