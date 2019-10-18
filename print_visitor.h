#ifndef TURBOPASCAL_PRINT_VISITOR_H
#define TURBOPASCAL_PRINT_VISITOR_H

#include <iostream>
#include <cassert>
#include "ast.h"

class PrintVisitor : public AST::Visitor {
 public:

  explicit PrintVisitor(std::ostream &os) : os_(os), indent_(0) {}

  void visit(const AST::IntegerExprNode *node) override {
    assert(node != nullptr);

    output(os_, indent_, "(IntegerExprNode ");
    output(os_, std::to_string(node->get_value()) + ")\n");
  }

  void visit(const AST::RealExprNode *node) override {
    assert(node != nullptr);

    output(os_, indent_, "(RealExprNode ");
    output(os_, std::to_string(node->get_value()) + ")\n");
  }

  void visit(const AST::BooleanExprNode *node) override {
    assert(node != nullptr);

    output(os_, indent_, "(BooleanExprNode ");
    output(os_, std::to_string(node->get_value()) + ")\n");
  }

  void visit(const AST::OpExprNode *node) override {
    assert(node != nullptr);

    output(os_, indent_++, "(OpExprNode\n");
    output(os_, indent_, "[" + op_str(node->get_op()) + "]\n");
    auto lhs = node->get_lhs();
    if (lhs != nullptr) {  // Operand could be a nullptr (e.g. unary operator).
      accept(lhs);
    }
    auto rhs = node->get_rhs();
    if (rhs != nullptr) {  // Operand could (in theory) be nullptr.
      accept(rhs);
    }
    output(os_, --indent_, ")\n");
  }

  void visit(const AST::StringExprNode *node) override {
    assert(node != nullptr);

    output(os_, indent_, "(StringExprNode ");
    output(os_, "'" + node->get_str() + "')\n");
  }

  void visit(const AST::VariableExprNode *node) override {
    assert(node != nullptr);

    output(os_, indent_, "(VariableExprNode ");
    output(os_, node->get_name() + ")\n");
  }

  void visit(const AST::FunctionCallExprNode *node) override {
    assert(node != nullptr);
    output(os_, indent_++, "(FunctionCallExprNode " + node->get_name() + "\n");
    for (auto expr : node->get_arguments()) {
      accept(expr);
    }
    output(os_, --indent_, ")\n");
  };

  void visit(const AST::AssignmentStmtNode *node) override {
    assert(node != nullptr);

    output(os_, indent_++, "(AssignmentStmtNode\n");
    accept(node->get_var());
    accept(node->get_expr());
    output(os_, --indent_, ")\n");
  };

  void visit(const AST::CompoundStmtNode *node) override {
    assert(node != nullptr);

    output(os_, indent_++, "(CompoundStmtNode\n");
    for (const auto stmt : node->get_stmts()) {
      accept(stmt);
    }
    output(os_, --indent_, ")\n");
  };

  void visit(const AST::EmptyStmtNode *node) override {
    assert(node != nullptr);

    output(os_, indent_, "(EmptyStmtNode)\n");
  }

  void visit(const AST::IfStmtNode *node) override {
    assert(node != nullptr);

    output(os_, indent_++, "(IfStmtNode\n");
    accept(node->get_expr());
    accept(node->get_stmt_if());
    auto stmt = node->get_stmt_else();
    if (stmt != nullptr) {
      accept(stmt);  // The else statement-pointer could legitimately be nullptr (when else is omitted).
    }
    output(os_, --indent_, ")\n");
  };

  void visit(const AST::ProcedureCallStmtNode *node) override {
    assert(node != nullptr);
    output(os_, indent_++, "(ProcedureCallStmtNode " + node->get_name() + "\n");
    for (auto expr : node->get_arguments()) {
      accept(expr);
    }
    output(os_, --indent_, ")\n");
  };

  void visit(const AST::WhileStmtNode *node) override {
    assert(node != nullptr);

    output(os_, indent_++, "(WhileStmtNode\n");
    accept(node->get_expr());
    accept(node->get_stmt());
    output(os_, --indent_, ")\n");
  }

  void visit(const AST::ReadStmtNode *node) override {
    assert(node != nullptr);

    std::string nl(node->get_newline() ? "Ln" : "");
    output(os_, indent_++, "(ReadStmtNode " + nl + "\n");
    accept(node->get_arg());
    output(os_, --indent_, ")\n");
  }

  void visit(const AST::WriteStmtNode *node) override {
    assert(node != nullptr);

    std::string nl(node->get_newline() ? "Ln" : "");
    output(os_, indent_++, "(WriteStmtNode " + nl + "\n");
    accept(node->get_expr());
    output(os_, --indent_, ")\n");
  }

  void visit(const AST::VariableNode *node) override {
    assert(node != nullptr);

    output(os_, indent_, "(VariableNode ");
    output(os_, node->get_name() + ")\n");
  }

  void visit(const AST::VariableDeclNode *node) override {
    assert(node != nullptr);

    output(os_, indent_++, "(VarDeclNode\n");
    output(os_, indent_, "");
    for (const auto &id : node->get_identifiers()) {
      output(os_, " " + id + " ");
    }
    output(os_, node->get_data_type().str() + "\n"); // NOTE.
    output(os_, --indent_, ")\n");
  }

  void visit(const AST::ProcedureDeclNode *node) override {
    assert(node != nullptr);

    output(os_, indent_++, "(ProcedureDeclNode " + node->get_name() + "\n");
    accept(node->get_block());
    output(os_, --indent_, ")\n");
  }

  void visit(const AST::FunctionDeclNode *node) override {
    assert(node != nullptr);

    output(os_, indent_++, "(FunctionDeclNode " + node->get_name() + "\n");
    accept(node->get_block());
    output(os_, --indent_, ")\n");
  }

  void visit(const AST::VariableDeclarationsNode *node) override {
    assert(node != nullptr);

    output(os_, indent_++, "(VariableDeclarationsNode\n");
    for (auto declaration : node->get_declarations()) {
      accept(declaration);
    }
    output(os_, --indent_, ")\n");
  }

  void visit(const AST::CallableDeclarationsNode *node) override {
    assert(node != nullptr);

    output(os_, indent_++, "(CallableDeclarationsNode\n");
    for (auto declaration : node->get_declarations()) {
      accept(declaration);
    }
    output(os_, --indent_, ")\n");
  }

  void visit(const AST::BlockNode *node) override {
    assert(node != nullptr);

    output(os_, indent_++, "(BlockNode\n");
    if (node->get_var_decl() != nullptr)  // Could legitimately be a nullprt.
      accept(node->get_var_decl());
    accept(node->get_call_decl());
    accept(node->get_stmt());
    output(os_, --indent_, ")\n");
  }

  void visit(const AST::ProgramNode *node) override {
    assert(node != nullptr);

    output(os_, indent_++, "(ProgramNode " + node->get_name() + "\n");
    accept(node->get_block());
    output(os_, --indent_, ")\n");
  }

 private:

  void accept(const AST::Node *node) {
    if (node != nullptr) node->accept(*this);
  }

  std::string op_str(Language::ExprOperator op) {
    switch (op) {
      case Language::ExprOperator::o_plus: return "+";
      case Language::ExprOperator::o_minus:
      case Language::ExprOperator::o_uminus: return "-";
      case Language::ExprOperator::o_multiply: return "*";
      case Language::ExprOperator::o_div: return "div";
      case Language::ExprOperator::o_divide: return "/";
      case Language::ExprOperator::o_and: return "and";
      case Language::ExprOperator::o_not: return "not";
      case Language::ExprOperator::o_or: return "or";
      case Language::ExprOperator::o_eq: return "=";
      case Language::ExprOperator::o_lt: return "<";
      case Language::ExprOperator::o_lteq: return "<=";
      case Language::ExprOperator::o_neq: return "<>";
      case Language::ExprOperator::o_gt: return ">";
      case Language::ExprOperator::o_gteq: return ">=";
      default: return "?";
    }
  }

  void output(std::ostream &os, int indent, const std::string &text) {
    for (int i = 0; i < indent; ++i) {
      os << "  ";
    }
    os << text;
  }

  void output(std::ostream &os, const std::string &text) {
    output(os, 0, text);
  }

  std::ostream &os_;
  int indent_;
};

#endif //TURBOPASCAL_PRINT_VISITOR_H
