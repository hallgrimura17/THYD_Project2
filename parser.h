
#ifndef TURBOPASCAL_PARSER_H
#define TURBOPASCAL_PARSER_H

#include <iostream>
#include <string>
#include "ast.h"

class Parser {
 public:
  // Constructor, input stream to read provided.
  Parser( std::istream& is, bool debug_lexer, bool debug_parser ) :
        is_(is), debug_lexer_(debug_lexer), debug_parser_(debug_parser), ast_(nullptr) {}

  // Parse the input. This method could potentially throw IO-related exceptions.
  virtual int parse( ) = 0;

  // Return a name given to the parser (e.g., "Bison" or "Handmade").
  virtual std::string get_name() const = 0;

  // Keep the root node of the abstract syntax tree.
  void set_AST( AST::Node* node ) { ast_ = node; }

  // Return the root node of the abstract syntax tree.
  AST::Node* get_AST( ) { return ast_; }

  // Destructor.
  virtual ~Parser() = default;

 protected:
  std::istream& is_;
  bool debug_lexer_;
  bool debug_parser_;
  AST::Node *ast_;
};
#endif //TURBOPASCAL_PARSER_H
