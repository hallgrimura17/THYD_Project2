#ifndef TURBOPASCAL_AST_H
#define TURBOPASCAL_AST_H

#include <iostream>
#include <string>
#include <list>
#include "language.h"

namespace AST {

class IntegerExprNode;
class RealExprNode;
class BooleanExprNode;
class StringExprNode;
class OpExprNode;
class VariableExprNode;
class FunctionCallExprNode;

class AssignmentStmtNode;
class CompoundStmtNode;
class EmptyStmtNode;
class IfStmtNode;
class ProcedureCallStmtNode;
class WhileStmtNode;
class ReadStmtNode;
class WriteStmtNode;

class VariableNode;
class VariableDeclNode;
class ProcedureDeclNode;
class FunctionDeclNode;

class VariableDeclarationsNode;
class CallableDeclarationsNode;
class BlockNode;
class ProgramNode;

class Visitor {
 public:
  virtual void visit( const IntegerExprNode* node ) = 0;
  virtual void visit( const RealExprNode* node ) = 0;
  virtual void visit( const BooleanExprNode* node ) = 0;
  virtual void visit( const StringExprNode* node ) = 0;
  virtual void visit( const OpExprNode* node ) = 0;
  virtual void visit( const VariableExprNode* node ) = 0;
  virtual void visit( const FunctionCallExprNode* node ) = 0;

  virtual void visit( const AssignmentStmtNode* node ) = 0;
  virtual void visit( const EmptyStmtNode* node ) = 0;
  virtual void visit( const CompoundStmtNode* node ) = 0;
  virtual void visit( const IfStmtNode* node ) = 0;
  virtual void visit( const ProcedureCallStmtNode* node ) = 0;
  virtual void visit( const WhileStmtNode* node ) = 0;
  virtual void visit( const ReadStmtNode* node ) = 0;
  virtual void visit( const WriteStmtNode* node ) = 0;

  virtual void visit( const VariableNode* node ) = 0;
  virtual void visit( const VariableDeclNode* node ) = 0;
  virtual void visit( const ProcedureDeclNode* node ) = 0;
  virtual void visit( const FunctionDeclNode* node ) = 0;
  virtual void visit( const VariableDeclarationsNode* node ) = 0;
  virtual void visit( const CallableDeclarationsNode* node ) = 0;
  virtual void visit( const BlockNode* node ) = 0;
  virtual void visit( const ProgramNode* node ) = 0;
};


class Node {
 public:
  virtual void accept( AST::Visitor& visitor ) const = 0;
};


class ExprNode : public Node {
};


class IntegerExprNode : public ExprNode {
 public:
  explicit IntegerExprNode(int n) : n_(n) {}

  int get_value() const { return n_; }

  void accept( AST::Visitor& visitor ) const override { visitor.visit( this ); }

 private:
  int n_;
};


class RealExprNode : public ExprNode {
 public:
  explicit RealExprNode(float n) : n_(n) {}

  float get_value() const { return n_; }

  void accept( AST::Visitor& visitor ) const override { visitor.visit( this ); }

 private:
  float n_;
};


class BooleanExprNode : public ExprNode {
 public:
  explicit BooleanExprNode(bool n) : n_(n) {}

  bool get_value() const { return n_; }

  void accept( AST::Visitor& visitor ) const override { visitor.visit( this ); }

 private:
  bool n_;
};


class StringExprNode : public ExprNode {
 public:
  explicit StringExprNode( std::string str ) : str_(std::move(str)) {}

  std::string get_str() const { return str_; }

  void accept( AST::Visitor& visitor ) const override { visitor.visit( this ); }

 private:
  std::string str_;
};


class OpExprNode : public ExprNode {
public:
  OpExprNode( Language::ExprOperator op, ExprNode *lhs, ExprNode *rhs )
      : op_(op), lhs_(lhs), rhs_(rhs) {
  }

  Language::ExprOperator get_op() const { return op_; }
  const ExprNode* get_lhs() const { return lhs_; }
  const ExprNode* get_rhs() const { return rhs_; }

  void accept( AST::Visitor& visitor ) const override { visitor.visit( this ); }

 private:
  Language::ExprOperator op_;
  ExprNode *lhs_, *rhs_;
};


class VariableExprNode : public ExprNode {
 public:
  explicit VariableExprNode( std::string name, ExprNode* expr = nullptr ) :
    name_(std::move(name)), expr_(expr) {}

  std::string get_name() const { return name_; }
  ExprNode* get_expr() const { return expr_; }

  void accept( AST::Visitor& visitor ) const override { visitor.visit( this ); }

 private:
  std::string name_;
  ExprNode* expr_;   // None-null for array variables (idex expression).
};


class FunctionCallExprNode : public ExprNode {
 public:
  FunctionCallExprNode( std::string name, std::list<ExprNode*> arguments )
      : name_(std::move(name)), arguments_(std::move(arguments)) {
  }

  std::string get_name() const { return name_; }
  const std::list<ExprNode*> get_arguments() const { return arguments_; }

  void accept( AST::Visitor& visitor ) const override { visitor.visit( this ); }

 private:
  std::string name_;
  std::list<ExprNode*> arguments_;
};


class StmtNode : public Node { };


class AssignmentStmtNode : public StmtNode {
 public:
  AssignmentStmtNode( VariableNode *var, ExprNode *expr )
      : var_(var), expr_(expr) {}
  const VariableNode* get_var() const { return var_; }
  const ExprNode* get_expr() const { return expr_; }
  void accept( AST::Visitor& visitor ) const override { visitor.visit( this ); }
 private:
  VariableNode *var_;
  ExprNode *expr_;
};


class CompoundStmtNode : public StmtNode {
 public:
  explicit CompoundStmtNode( std::list<StmtNode*> stmts )
      : stmts_(std::move(stmts)) {
  }

  const std::list<StmtNode*> get_stmts() const { return stmts_; }

  void accept( AST::Visitor& visitor ) const override { visitor.visit( this ); }

 private:
  std::list<StmtNode*> stmts_;
};


class EmptyStmtNode : public StmtNode {
 public:
  void accept( AST::Visitor& visitor ) const override { visitor.visit( this ); }
};


class IfStmtNode : public StmtNode {
 public:
  IfStmtNode( ExprNode *expr, StmtNode *stmt_if, StmtNode *stmt_else = nullptr )
      : expr_(expr), stmt_if_(stmt_if), stmt_else_(stmt_else) {}

  const ExprNode* get_expr() const { return expr_; }
  const StmtNode* get_stmt_if() const { return stmt_if_; }
  const StmtNode* get_stmt_else() const { return stmt_else_; }

  void accept( AST::Visitor& visitor ) const override { visitor.visit( this ); }

 private:
  ExprNode *expr_;
  StmtNode *stmt_if_, *stmt_else_;
};


class ProcedureCallStmtNode : public StmtNode {
 public:
  ProcedureCallStmtNode( std::string name, std::list<ExprNode*> arguments )
      : name_(std::move(name)), arguments_(std::move(arguments)) {
  }

  std::string get_name() const { return name_; }
  const std::list<ExprNode*> get_arguments() const { return arguments_; }

  void accept( AST::Visitor& visitor ) const override { visitor.visit( this ); }

 private:
  std::string name_;
  std::list<ExprNode*> arguments_;
};


class WhileStmtNode : public StmtNode {
 public:
  WhileStmtNode( ExprNode *expr, StmtNode *stmt )
      : expr_(expr), stmt_(stmt) {}

  const ExprNode* get_expr() const { return expr_; }
  const StmtNode* get_stmt() const { return stmt_; }

  void accept( AST::Visitor& visitor ) const override { visitor.visit( this ); }

 private:
  const ExprNode *expr_;
  const StmtNode *stmt_;
};


class ReadStmtNode : public StmtNode {
 public:
  ReadStmtNode(VariableNode* arg, bool newline = false) : arg_(arg), newline_(newline) {}

  VariableNode* get_arg() const { return arg_; }
  bool get_newline() const { return newline_; }

  void accept(AST::Visitor &visitor) const override { visitor.visit(this); }

 private:
  VariableNode* arg_;
  bool newline_;

};


class WriteStmtNode : public StmtNode {
 public:
  WriteStmtNode(ExprNode* expr, bool newline = false) : expr_(expr), newline_(newline) {}

  ExprNode* get_expr() const { return expr_; }
  bool get_newline() const { return newline_; }

  void accept(AST::Visitor &visitor) const override { visitor.visit(this); }

 private:
  ExprNode* expr_;
  bool newline_;
};


class VariableNode : public Node {
 public:
  explicit VariableNode( std::string name, ExprNode* expr = nullptr )
      : name_(std::move(name)), expr_(expr) {}
  std::string get_name() const { return name_; }
  ExprNode* get_expr() const { return expr_; }

  void accept( AST::Visitor& visitor ) const override { visitor.visit( this ); }

 private:
  std::string name_;
  ExprNode* expr_;   // None-null for array variables (idex expression).
};


class VariableDeclNode : public Node {
 public:
  explicit VariableDeclNode( std::list<std::string> identifiers, LNG::DataType dt )
      : identifiers_(std::move(identifiers)), dt_(dt) {};

  const std::list<std::string> get_identifiers( ) const { return identifiers_; }
  const LNG::DataType get_data_type() const { return dt_; }

  void accept( AST::Visitor& visitor ) const override { visitor.visit( this ); }
 private:
  const std::list<std::string> identifiers_;
  LNG::DataType dt_;
};


class CallableDeclNode : public Node {};


class ProcedureDeclNode : public CallableDeclNode {
 public:
  ProcedureDeclNode( const std::string& name, VariableDeclarationsNode* var_decl, BlockNode* blck )
      : name_(name), var_decl_(var_decl), blck_(blck) {}
  const std::string get_name() const { return name_; }
  const VariableDeclarationsNode* get_var_decl() const { return var_decl_; }
  const BlockNode* get_block() const { return blck_; }
  void accept( AST::Visitor& visitor ) const override { visitor.visit( this ); }

 private:
  std::string name_;
  VariableDeclarationsNode* var_decl_;
  BlockNode* blck_;
};


class FunctionDeclNode : public CallableDeclNode {
 public:
  FunctionDeclNode( const std::string& name, VariableDeclarationsNode* var_decl, BlockNode* blck, LNG::DataType dt )
      : name_(name), var_decl_(var_decl), blck_(blck), dt_(dt) {}
  const std::string get_name() const { return name_; }
  const VariableDeclarationsNode* get_var_decl() const { return var_decl_; }
  const BlockNode* get_block() const { return blck_; }
  const LNG::DataType get_data_type() const { return dt_; }
  void accept( AST::Visitor& visitor ) const override { visitor.visit( this ); }

 private:
  std::string name_;
  VariableDeclarationsNode* var_decl_;
  BlockNode* blck_;
  LNG::DataType dt_;
};


class DeclPartNode : public Node { };

class VariableDeclarationsNode : public DeclPartNode {
 public:
  explicit VariableDeclarationsNode(std::list<VariableDeclNode*>& declarations )
      : declarations_(std::move(declarations)) {};

  const std::list<VariableDeclNode*> get_declarations( ) const { return declarations_; }
  void accept( AST::Visitor& visitor ) const override { visitor.visit( this ); }
 private:
  const std::list<VariableDeclNode*> declarations_;
};


class CallableDeclarationsNode : public DeclPartNode {
 public:
  explicit CallableDeclarationsNode(std::list<CallableDeclNode*>& declarations )
      : declarations_(std::move(declarations)) {};

  const std::list<CallableDeclNode*> get_declarations( ) const { return declarations_; }
  void accept( AST::Visitor& visitor ) const override { visitor.visit( this ); }
 private:
  const std::list<CallableDeclNode*> declarations_;
};


class BlockNode : public Node {
 public:
  BlockNode(VariableDeclarationsNode* var_decl, CompoundStmtNode* stmt )
      : var_decl_(var_decl), call_decl_(nullptr), stmt_( stmt ) {}

  BlockNode(VariableDeclarationsNode* var_decl, CallableDeclarationsNode* call_decl, CompoundStmtNode* stmt )
      : var_decl_(var_decl), call_decl_(call_decl), stmt_( stmt ) {}

  const VariableDeclarationsNode* get_var_decl() const { return var_decl_; }
  const CallableDeclarationsNode* get_call_decl() const { return call_decl_; }
  const CompoundStmtNode* get_stmt() const { return stmt_; }
  void accept( AST::Visitor& visitor ) const override { visitor.visit( this ); }

 private:
  VariableDeclarationsNode* var_decl_;
  CallableDeclarationsNode* call_decl_;
  CompoundStmtNode* stmt_;
};


class ProgramNode : public Node {
 public:
  ProgramNode( const std::string& name, BlockNode* blck )
    : name_(name), blck_(blck) {}
  const std::string get_name() const { return name_; }
  const BlockNode* get_block() const { return blck_; }
  void accept( AST::Visitor& visitor ) const override { visitor.visit( this ); }

 private:
  std::string name_;
  BlockNode* blck_;
};

};
#endif //TURBOPASCAL_AST_H
