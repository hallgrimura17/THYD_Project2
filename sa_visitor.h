#ifndef TURBOPASCAL_SA_VISITOR_H
#define TURBOPASCAL_SA_VISITOR_H

#include "ast.h"
#include <iostream>
#include <cassert>
#include <string>
#include <stack>
#include "symbol_table.h"


class SemanticAnalysisVisitor : public AST::Visitor {
 public:
  explicit SemanticAnalysisVisitor(SymbolTable &st, std::ostream &os) : st_(st) ,os_(os), indent_(0){}
 private:
  void error(const std::string &msg) {
    std::cerr << msg << std::endl;
    exit(1);
  }

  void visit(const AST::IntegerExprNode *node) override {
    assert(node != nullptr);
    s_.push("IntegerExprNode");
    //output(os_, indent_, "(IntegerExprNode ");
    //output(os_, std::to_string(node->get_value()) + ")\n");
  }

  void visit(const AST::RealExprNode *node) override {
    assert(node != nullptr);
    s_.push("RealExprNode");
    //output(os_, indent_, "(RealExprNode ");
    //output(os_, std::to_string(node->get_value()) + ")\n");
  }

  void visit(const AST::BooleanExprNode *node) override {
    assert(node != nullptr);
    s_.push("BooleanExprNode");
    //output(os_, indent_, "(BooleanExprNode ");
    //output(os_, std::to_string(node->get_value()) + ")\n");

  }

  void visit(const AST::OpExprNode *node) override {
    assert(node != nullptr);
    std::cout << "Op Expr Node: " << std::endl;
    //output(os_, indent_++, "(OpExprNode\n");
    //output(os_, indent_, "[" + op_str(node->get_op()) + "]\n");
    auto lhs = node->get_lhs();
    if (lhs != nullptr) {  // Operand could be a nullptr (e.g. unary operator).
      accept(lhs);
    }
    auto rhs = node->get_rhs();
    if (rhs != nullptr) {  // Operand could (in theory) be nullptr.
      accept(rhs);
    }
    std::cout << "Scope: " << scope_ << std::endl;
    // get latest 2 elements of the stack and compare for operator expr
    std::string rhsPop = s_.top();
    s_.pop();
    std::string lhsPop = s_.top();
    s_.pop();

    //ST lookup
    //std::cout << "Lookup: " << st_.lookup() << std::endl;

    std::cout << "lhs: " << lhsPop << " rhs: " << rhsPop << std::endl;
    if(lhsPop == "VariableExprNode" && (rhsPop == "IntegerExprNode" || rhsPop == "RealExprNode")){
      s_.push("VariableExprNode");
    }
    else if(lhsPop == "FunctionCallExprNode" && ((rhsPop == "IntegerExprNode" || rhsPop == "RealExprNode") || rhsPop == "VariableExprNode")){
      s_.push("AssignmentStmtNode");
    }
    else if((lhsPop == "IntegerExprNode" || lhsPop  == "RealExprNode") && (rhsPop == "IntegerExprNode" || rhsPop == "RealExprNode")) {
      if(rhsPop == "RealExprNode" || lhsPop == "RealExprNode"){
        s_.push("RealExprNode");
      }
      else {
        s_.push("IntegerExprNode");
      }
    }
    else{
      error("RHS and LHS value types are not compatible");
      //std::cout << "Something happened" << std::endl;
    }
    //output(os_, --indent_, ")\n");
  }

  void visit(const AST::StringExprNode *node) override {
    assert(node != nullptr);
    s_.push("StringExprNode");
    //output(os_, indent_, "(StringExprNode ");
    //output(os_, "'" + node->get_str() + "')\n");
  }

  void visit(const AST::VariableExprNode *node) override {
    assert(node != nullptr);
    std::cout << "Variable Expr Node: " << std::endl;

    auto varexpr = st_.lookup(scope_, node->get_name());
    std::cout << "Var expr: " << varexpr->str() << std::endl;
    s_.push("VariableExprNode");
    //std::cout << "GET EXPR: " << node->get_name() << std::endl;
    //s_.push("VariableExprNode");
    //output(os_, indent_, "(VariableExprNode ");
    //output(os_, node->get_name() + ")\n");
  }

  void visit(const AST::FunctionCallExprNode *node) override {
    assert(node != nullptr);
    std::cout << "Function Call Expr Node: " << std::endl;
    s_.push("FunctionCallExprNode");
    //output(os_, indent_++, "(FunctionCallExprNode " + node->get_name() + "\n");
    for (auto expr : node->get_arguments()) {
      // compare func call arguements types to func decleration arguements
      accept(expr);
    }
    //output(os_, --indent_, ")\n");
  };

  void visit(const AST::AssignmentStmtNode *node) override {
    assert(node != nullptr);
    //std::cout << node->get_var()->get_name();
    auto variableName = st_.lookup(scope_, node->get_var()->get_name());
    //std::cout << "Scope: " << scope_ << " variableName: " << variableName << std::endl;
    std::cout << "Assignment Statement Node: " << std::endl;

    accept(node->get_var());
    /*if(st_.lookup(scope_, node->get_var()->get_name()) == nullptr) {
      error("Variable does not exist");
    }*/
    accept(node->get_expr());
    /*auto rhsVar = s_.top();
    s_.pop();
    std::cout << "rhsVar: " << rhsVar << std::endl;
    auto lhsVar = s_.top();
    s_.pop();
    std::cout << "lhsVar: " << lhsVar << std::endl;
    */
    //s_.push("AssignmentStmtNode");
    //output(os_, indent_++, "(AssignmentStmtNode\n");
    //output(os_, --indent_, ")\n");
  };

  void visit(const AST::CompoundStmtNode *node) override {
    assert(node != nullptr);
    //output(os_, indent_++, "(CompoundStmtNode\n");
    for (const auto stmt : node->get_stmts()) {
      accept(stmt);
    }
    //output(os_, --indent_, ")\n");
  };

  void visit(const AST::EmptyStmtNode *node) override {
    assert(node != nullptr);
    s_.push("EmptyStmtNode");
    //output(os_, indent_, "(EmptyStmtNode)\n");
  }

  void visit(const AST::IfStmtNode *node) override {
    assert(node != nullptr);
    //std::cout << "If Stmt Node: " << std::endl;
    scope_ = "conditional statement scope";
    //s_.push("IfStmtNode");
    //output(os_, indent_++, "(IfStmtNode\n");
    accept(node->get_expr());
    accept(node->get_stmt_if());
    auto stmt = node->get_stmt_else();
    if (stmt != nullptr) {
      accept(stmt);  // The else statement-pointer could legitimately be nullptr (when else is omitted).
      //s_.push("ElseStmtNode"); // practically no difference
      std::cout << "Else Stmt Node: " << std::endl;
    }
    //output(os_, --indent_, ")\n");
  };

  void visit(const AST::ProcedureCallStmtNode *node) override {
    assert(node != nullptr);
    //output(os_, indent_++, "(ProcedureCallStmtNode " + node->get_name() + "\n");
    for (auto expr : node->get_arguments()) {
      accept(expr);
    }
    //output(os_, --indent_, ")\n");
  };

  void visit(const AST::WhileStmtNode *node) override {
    assert(node != nullptr);

    //output(os_, indent_++, "(WhileStmtNode\n");
    accept(node->get_expr());
    accept(node->get_stmt());
    //output(os_, --indent_, ")\n");
  }

  void visit(const AST::ReadStmtNode *node) override {
    assert(node != nullptr);
    s_.push("ReadStmtNode");
    std::string nl(node->get_newline() ? "Ln" : "");
    //output(os_, indent_++, "(ReadStmtNode " + nl + "\n");
    accept(node->get_arg());
    //output(os_, --indent_, ")\n");
  }

  void visit(const AST::WriteStmtNode *node) override {
    assert(node != nullptr);
    std::cout << "Write Stmt Node: " << std::endl;
    std::string nl(node->get_newline() ? "Ln" : "");
    //output(os_, indent_++, "(WriteStmtNode " + nl + "\n");
    accept(node->get_expr());
    output(os_, --indent_, ")\n");
  }

  void visit(const AST::VariableNode *node) override {
    assert(node != nullptr);
    std::cout << "Variable Node: " << node->get_name() << std::endl;
    //output(os_, indent_, "(VariableNode ");
    //output(os_, node->get_name() + ")\n");
  }

  void visit(const AST::VariableDeclNode *node) override {
    assert(node != nullptr);
    //std::cout << "Variable Decl Node: " << std::endl;
    //output(os_, indent_++, "(VarDeclNode\n");
    //output(os_, indent_, "");
    for (const auto &id : node->get_identifiers()) {
      //output(os_, " " + id + " ");
      std::cout << node->get_data_type().str() << std::endl;
      if(node->get_data_type().str() == "integer") {
        st_.add(scope_, id, SymbolTable::EntryType::sVariable, "",node->get_data_type());
        s_.push("IntegerExprNode");
      }
      else if(node->get_data_type().str() == "real") {
        st_.add(scope_, id, SymbolTable::EntryType::sVariable, "",node->get_data_type());
        s_.push("RealExprNode");
      }
      else if(node->get_data_type().str() == "boolean") {
        //std::cout << "id: "<< id << std::endl;
        st_.add(scope_, id, SymbolTable::EntryType::sVariable, "",node->get_data_type());
        s_.push("BooleanExprNode");
      }
      else if(node->get_data_type().str() == "string") {
        st_.add(scope_, id, SymbolTable::EntryType::sVariable, "",node->get_data_type());
        s_.push("StringExprNode");
      }
    }
    //output(os_, node->get_data_type().str() + "\n"); // NOTE.
    //output(os_, --indent_, ")\n");
  }

  void visit(const AST::ProcedureDeclNode *node) override {
    assert(node != nullptr);

    //output(os_, indent_++, "(ProcedureDeclNode " + node->get_name() + "\n");
    accept(node->get_var_decl());
    accept(node->get_block());
    //output(os_, --indent_, ")\n");
  }

  void visit(const AST::FunctionDeclNode *node) override {
    assert(node != nullptr);
    std::string tmpScope = scope_;
    scope_ = node->get_name();
    std::cout << "Scope: " << scope_ << std::endl;
    //std::cout << "scope name: " << scope_ << std::endl;
    //output(os_, indent_++, "(FunctionDeclNode " + node->get_name() + "\n");
    accept(node->get_block());
    //output(os_, --indent_, ")\n");
    //st_.add(scope_, node->get_name(), , node->get_var_decl(), node->get_data_type());
    scope_ = tmpScope;
    std::cout << "Scope: " << scope_ << std::endl;
  }

  void visit(const AST::VariableDeclarationsNode *node) override {
    assert(node != nullptr);

    //output(os_, indent_++, "(VariableDeclarationsNode\n");
    for (auto declaration : node->get_declarations()) {
      accept(declaration);
    }
    //output(os_, --indent_, ")\n");
  }

  void visit(const AST::CallableDeclarationsNode *node) override {
    assert(node != nullptr);

    //output(os_, indent_++, "(CallableDeclarationsNode\n");
    for (auto declaration : node->get_declarations()) {
      accept(declaration);
    }
    //output(os_, --indent_, ")\n");
  }

  void visit(const AST::BlockNode *node) override {
    assert(node != nullptr);

    //output(os_, indent_++, "(BlockNode\n");
    if (node->get_var_decl() != nullptr)  // Could legitimately be a nullprt.
      accept(node->get_var_decl());
    accept(node->get_call_decl());
    accept(node->get_stmt());
    //output(os_, --indent_, ")\n");
  }

  void visit(const AST::ProgramNode *node) override {
    assert(node != nullptr);
    scope_ = node->get_name();
    //output(os_, indent_++, "(ProgramNode " + node->get_name() + "\n");
    accept(node->get_block());
    //output(os_, --indent_, ")\n");
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
    //output(os, 0, text);
  }

 private:
  std::ostream &os_;
  int indent_;
  std::stack<std::string> s_;
  SymbolTable st_;
  std::string scope_;
};

#endif //TURBOPASCAL_SA_VISITOR_H
