#ifndef TURBOPASCAL_HPARSER_H
#define TURBOPASCAL_HPARSER_H

#include <string>
#include <exception>
#include "common.h"
#include "language.h"
#include "lexer.h"
#include "symbol_table.h"
#include "ast.h"
#include "parser.h"

class HParser: public Parser {
 public:

  explicit HParser( std::istream &is, bool debug_lexer, bool debug_parser )
      : Parser( is, debug_lexer, debug_parser), lexer_(is) {
    lexer_.get(token_);
  }

  int parse() override;

  virtual std::string get_name() const override { return "Handmade"; }

 private:

  AST::ProgramNode *program();
  AST::BlockNode *main_block();
  AST::BlockNode *block();

  AST::VariableDeclarationsNode *variable_declarations();
  AST::VariableDeclNode *variable_declaration();
  Language::DataType type();
  Language::SimpleDataType simple_type();

  AST::CallableDeclarationsNode *callable_declarations();
  AST::ProcedureDeclNode *procedure_declaration();
  AST::FunctionDeclNode *function_declaration();
  AST::VariableDeclarationsNode *optional_parameters();
  AST::VariableDeclNode *parameter_list();

  AST::CompoundStmtNode *compound_statement();
  AST::StmtNode *statement();
  AST::AssignmentStmtNode *assignment_statement(std::string identifier = "");
  AST::EmptyStmtNode *empty_statement();
  AST::IfStmtNode *if_statement();
  AST::ProcedureCallStmtNode *procedure_call_statement(const std::string &identifier = "");
  AST::WhileStmtNode *while_statement();
  AST::ReadStmtNode *read_statement();
  AST::WriteStmtNode *write_statement();

  AST::VariableNode *variable_lvalue(SymbolTable::Entry &entry, const std::string &identifier = "");
  AST::ExprNode *actual_parameter();

  AST::ExprNode *expression();
  AST::ExprNode *simple_expression();
  AST::ExprNode *term();
  AST::ExprNode *complemented_factor();
  AST::ExprNode *signed_factor();
  AST::ExprNode *factor();

  AST::ExprNode *constant();
  AST::IntegerExprNode *integer_constant();
  AST::RealExprNode *real_constant();
  AST::BooleanExprNode *boolean_constant();
  AST::StringExprNode *string_constant();

  AST::VariableExprNode *variable_rvalue(SymbolTable::Entry &entry);
  AST::FunctionCallExprNode *function_call(const std::string &identifier);

  //////////////////////////////////////////////////////////////////////////

  auto operator_in(const std::map<Language::TokenName, Language::ExprOperator> &op_map) {
    auto it = op_map.find(token_.name);
    if (it != op_map.end()) {
      match_token(token_.name);
    }
    return it;
  }

  inline bool token(Language::TokenName name) {
    return token_.name == name;
  }

  void match_token(Language::TokenName name) {
    if (token_.name == name) {
      try {
        lexer_.get(token_);
      }
      catch (Common::CompilerException &e) {
        error(token_.loc, e.what());
      }
    } else {
      error(token_.loc, Common::to_upper(Language::TokenNameToText[name]) + " expected.");
    }
  }

  bool match_token_if(Language::TokenName name) {
    if (token_.name == name) {
      match_token(name);
      return true;
    }
    return false;
  }

  void error(const Common::Location &loc, const std::string &msg) {
    std::cerr << "(" << loc.line << "," << loc.col << "): " << msg << std::endl;
    exit(1);
  }

  Lexer lexer_;
  Lexer::Token token_;
  SymbolTable symbol_table_;
  std::string scope_;
};
#endif //TURBOPASCAL_HPARSER_H
