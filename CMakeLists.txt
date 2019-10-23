cmake_minimum_required(VERSION 3.8)
project(TurboPascal)

set(CMAKE_CXX_STANDARD 14)

add_executable(TurboPascal main.cpp lexer.h hparser.cpp hparser.h ast.h print_visitor.h sa_visitor.h symbol_table.h language.h lexer.cpp lexer.h common.h language.cpp parser.h)