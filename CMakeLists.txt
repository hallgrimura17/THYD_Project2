cmake_minimum_required(VERSION 3.8)
project(TurboPascal)

set(CMAKE_CXX_STANDARD 14)

find_package(BISON REQUIRED)
BISON_TARGET(tpparser tpparser.yy ${CMAKE_CURRENT_BINARY_DIR}/../tpparser.cpp DEFINES_FILE tpparser.h)

add_executable(TurboPascal
        main.cpp lexer.h hparser.cpp hparser.h ${BISON_tpparser_OUTPUTS}
        ast.h print_visitor.h sa_visitor.h sa_visitor.h symbol_table.h
        language.h lexer.cpp lexer.h common.h language.cpp parser.h bparser.h)