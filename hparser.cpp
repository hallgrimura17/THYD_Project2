#include <string>
#include <list>
#include <map>
#include "ast.h"
#include "hparser.h"
#include <memory>

using namespace std;
using namespace AST;

int HParser::parse() {
  ast_ = program();
  return 0;
}


ProgramNode* HParser::program() {
  string name = token_.text;
  match_token(LNG::TN::t_program);
  match_token(LNG::TN::t_identifier);
  match_token(LNG::TN::t_semicolon);
  scope_ = "";
  auto block_node = main_block();
  match_token(LNG::TN::t_dot);
  match_token(LNG::TN::t_eoi);
  return new ProgramNode(name, block_node);
}


BlockNode* HParser::main_block() {
  auto var_decl = variable_declarations();
  auto call_decl = callable_declarations();
  auto cstmt = compound_statement();
  return new BlockNode(var_decl, call_decl, cstmt);
}


VariableDeclarationsNode* HParser::variable_declarations( ) {
  if (match_token_if(LNG::TN::t_var)) {
    list<VariableDeclNode *> declarations;
    VariableDeclNode* decl;
    do {
      decl = variable_declaration();
      declarations.push_back(decl);
      match_token(LNG::TN::t_semicolon);
    } while (token(LNG::TN::t_identifier));
    return new VariableDeclarationsNode(declarations);
  }
  return nullptr;
}


VariableDeclNode* HParser::variable_declaration( ) {
  list<string> identifiers;
  do {
    identifiers.push_back(token_.text);
    match_token(LNG::TN::t_identifier);
  } while (match_token_if(LNG::TN::t_comma));
  match_token(LNG::TN::t_colon);
  LNG::DataType data_type = type();
  for (auto &id : identifiers) {
    auto entry = symbol_table_.lookup(scope_, id);
    if (entry != nullptr) {
      error(token_.loc, "Duplicate identifier '" + id + "'");
    }
    symbol_table_.add_var(scope_, id, data_type);
  }
  return new VariableDeclNode(identifiers, data_type);
}


LNG::DataType HParser::type() {
  LNG::SimpleDataType sdt = LNG::SimpleDataType::tVoid;
  int from = 0, to = 0;
  if (match_token_if(LNG::TN::t_array)) {
    match_token(LNG::TN::t_lbracket);
    std::unique_ptr<IntegerExprNode> p_from(integer_constant());
    from = p_from.get()->get_value();
    match_token(LNG::TN::t_subrange);
    std::unique_ptr<IntegerExprNode> p_to(integer_constant());
    to = p_to.get()->get_value();
    match_token(LNG::TN::t_rbracket);
    match_token(LNG::TN::t_of);
  }
  sdt = simple_type();
  return Language::DataType(sdt, from, to);
}


LNG::SimpleDataType HParser::simple_type() {
  LNG::SimpleDataType sdt = LNG::SimpleDataType::tVoid;
  if (match_token_if(LNG::TN::t_boolean)) {
    sdt = LNG::SimpleDataType::tBoolean;
  } else if (match_token_if(LNG::TN::t_real)) {
    sdt = LNG::SimpleDataType::tReal;
  } else {
    match_token(LNG::TN::t_integer);
    sdt = LNG::SimpleDataType::tInteger;
  }
  return sdt;
}


StringExprNode* HParser::string_constant() {
  const string text = token_.text;
  match_token(LNG::TN::t_string_l);
  return new StringExprNode(text);
}


IntegerExprNode* HParser::integer_constant() {
  int number = 0;
  if (token_.name == LNG::TN::t_integer_l) {
    number = std::stoi(token_.text);
    match_token(LNG::TN::t_integer_l);
  } else {
    error(token_.loc, "Expected integer constant.");
  }
  return new IntegerExprNode(number);
}


VariableNode* HParser::variable_lvalue(SymbolTable::Entry& entry, const string& identifier ) {
  string variable_name;
  ExprNode *expr = nullptr;
  if (identifier.empty()) {
    variable_name = token_.text;
    match_token(LNG::TN::t_identifier);
  } else variable_name = identifier;
  if ( entry.data_type.is_array() ) {
    match_token(LNG::TN::t_lbracket);
    expr = expression();
    match_token(LNG::TN::t_rbracket);
  }
  return new VariableNode(variable_name, expr);
}


CompoundStmtNode* HParser::compound_statement() {
  list<StmtNode *> statements;
  match_token(LNG::TN::t_begin);
  do {
    statements.push_back(statement());
  } while (match_token_if(LNG::TN::t_semicolon));
  match_token(LNG::TN::t_end);
  return new CompoundStmtNode(statements);
}


StmtNode* HParser::statement() {
  StmtNode *stmt = nullptr;
  if (token(LNG::TN::t_identifier)) {
    auto entry = symbol_table_.lookup("", token_.text);
    if (entry != nullptr && entry->entry_type == SymbolTable::EntryType::sProcedure) {
      stmt = procedure_call_statement();
    } else {
      stmt = assignment_statement();
    }
  } else if (token(LNG::TN::t_begin)) {
    stmt = compound_statement();
  } else if (token(LNG::TN::t_if)) {
    stmt = if_statement();
  } else if (token(LNG::TN::t_while)) {
    stmt = while_statement();
  } else if (token(LNG::TN::t_read) || token(LNG::TN::t_readln) ) {
    stmt = read_statement();
  } else if (token(LNG::TN::t_write) || token( LNG::TN::t_writeln)) {
    stmt = write_statement();
  } else {
    stmt = empty_statement();
  }
  return stmt;
}


AssignmentStmtNode* HParser::assignment_statement(string identifier ) {
  if (identifier.empty()) {
    identifier = token_.text;
    match_token(LNG::TN::t_identifier);
  }
  auto entry = symbol_table_.lookup(scope_, identifier);
  if (entry == nullptr && !scope_.empty()) {
    entry = symbol_table_.lookup("", identifier);
  }
  if (entry == nullptr) {
    error(token_.loc, "Undeclared identifier \"" + token_.text + "\"");
  }
  VariableNode *var = variable_lvalue(*entry, identifier);
  match_token(LNG::TN::t_assign);
  ExprNode *expr = expression();
  return new AssignmentStmtNode(var, expr);
}


EmptyStmtNode* HParser::empty_statement() {
  return new EmptyStmtNode();
}


ReadStmtNode* HParser::read_statement( ) {
  bool newline = false;
  if (match_token_if(LNG::TN::t_readln)) {
    newline = true;
  } else {
    match_token(LNG::TN::t_read);
  }
  match_token(LNG::TN::t_lparenthesis);
  auto entry = symbol_table_.lookup(scope_, token_.text);
  if (entry == nullptr && !scope_.empty()) {
    entry = symbol_table_.lookup("", token_.text);
  }
  if (entry == nullptr) {
    error(token_.loc, "Identifier not found \"" + token_.text + "\"");
  }
  auto var = variable_lvalue( *entry );
  match_token(LNG::TN::t_rparenthesis);
  return new ReadStmtNode(var, newline);
}


WriteStmtNode* HParser::write_statement( ) {
  ExprNode *expr = nullptr;
  bool newline = false;
  if (match_token_if(LNG::TN::t_writeln)) {
    newline = true;
  } else {
    match_token(LNG::TN::t_write);
  }
  match_token(LNG::TN::t_lparenthesis);
  if (token(LNG::TN::t_string_l)) {
    expr = string_constant();
  } else {
    expr = expression();
  }
  match_token(LNG::TN::t_rparenthesis);
  return new WriteStmtNode(expr, newline);
}


ExprNode* HParser::actual_parameter() {
  return expression();
}


ExprNode* HParser::expression() {
  static map<LNG::TN, LNG::EO> relational_op = {
      {LNG::TN::t_eq, LNG::EO::o_eq},
      {LNG::TN::t_neq, LNG::EO::o_neq},
      {LNG::TN::t_lt, LNG::EO::o_lt},
      {LNG::TN::t_lteq, LNG::EO::o_lteq},
      {LNG::TN::t_gt, LNG::EO::o_gt},
      {LNG::TN::t_gteq, LNG::EO::o_gteq}};

  auto expr = simple_expression();
  auto it = operator_in(relational_op);
  while (it != relational_op.end()) {
    auto expr_rhs = simple_expression();
    expr = new OpExprNode(it->second, expr, expr_rhs);
    it = operator_in(relational_op);
  }
  return expr;
}


ExprNode* HParser::factor() {
  ExprNode *expr = nullptr;
  if (token(LNG::TN::t_identifier)) {
    auto entry = symbol_table_.lookup(scope_, token_.text);
    if (entry == nullptr && !scope_.empty()) {
      entry = symbol_table_.lookup("", token_.text);
    }
    if (entry == nullptr) {
      error(token_.loc, "Identifier not found \"" + token_.text + "\"");
    }
    if (entry->entry_type == SymbolTable::EntryType::sFunction) {
      expr = function_call("");
    } else {
      expr = variable_rvalue( *entry );
    }
  } else if (token(LNG::TN::t_lparenthesis)) {
    match_token(LNG::TN::t_lparenthesis);
    expr = expression();
    match_token(LNG::TN::t_rparenthesis);
  } else {
    expr = constant();
  }
  return expr;
}


ExprNode* HParser::constant() {
  ExprNode *expr = nullptr;
  if (token(LNG::TN::t_true) || token(LNG::TN::t_false)) {
    expr = boolean_constant();
  } else if (token(LNG::TN::t_real_l)) {
    expr = real_constant();
  } else {
    expr = integer_constant();
  }
  return expr;
}


//////////////////////////////////////////////////////////////////////////////


ProcedureDeclNode* HParser::procedure_declaration() {
  match_token(LNG::TN::t_procedure);
  string identifier = token_.text;
  match_token(LNG::TN::t_identifier);
  scope_ = identifier;
  auto params = optional_parameters();
  string signature = "";
  if(params != NULL){
    for(auto s: params->get_declarations()){
      signature += "::" + s->get_data_type().str();
    } 
  }
  symbol_table_.add_procedure(identifier, signature);
  match_token(LNG::TN::t_semicolon);
  auto block_node = block();
  match_token(LNG::TN::t_semicolon);
  scope_ = "";
  return new ProcedureDeclNode(identifier, params, block_node);
}


//////////////////////////////////////////////////////////////////////////////

CallableDeclarationsNode* HParser::callable_declarations() {
  list<CallableDeclNode *> declarations;
  while (token(LNG::TN::t_procedure) || token(LNG::TN::t_function)) {
    if(token(LNG::TN::t_procedure)) {
      declarations.push_back(procedure_declaration());
    }
    else {
      declarations.push_back(function_declaration());
    }
    
  }
  return new CallableDeclarationsNode(declarations);
}


VariableDeclarationsNode* HParser::optional_parameters() {
  if(match_token_if(LNG::TN::t_lparenthesis)){
    list<VariableDeclNode*> parameter_lists;
    do {
      parameter_lists.push_back(parameter_list());
    } while (match_token_if(LNG::TN::t_semicolon));
    match_token(LNG::TN::t_rparenthesis);
    return new VariableDeclarationsNode(parameter_lists);
  }
  return nullptr;
}

VariableDeclNode* HParser::parameter_list() {
  return variable_declaration();
}


FunctionDeclNode* HParser::function_declaration() {
  match_token(LNG::TN::t_function);
  string identifier = token_.text;
  match_token(LNG::TN::t_identifier);
  scope_ = identifier;
  auto params = optional_parameters();
  string signature = "";
  if(params != NULL){
    for(auto s: params->get_declarations()){
      signature += "::" + s->get_data_type().str();
    } 
  }
  match_token(LNG::TN::t_colon);  
  auto simple_type = type();
  symbol_table_.add_function(identifier, signature, simple_type);
  match_token(LNG::TN::t_semicolon);
  auto block_node = block();
  match_token(LNG::TN::t_semicolon);
  scope_ = "";
  return new FunctionDeclNode(identifier, params, block_node, simple_type);
}


BlockNode* HParser::block() {
  return new BlockNode(variable_declarations(), compound_statement());
}


IfStmtNode* HParser::if_statement() {
  match_token(LNG::TN::t_if);
  auto expr_ = expression();
  match_token(LNG::TN::t_then);
  auto stmt = statement();
  StmtNode* elseStmt = nullptr;
  if(match_token_if(LNG::TN::t_else)){
    elseStmt = statement();
  }
  return new IfStmtNode(expr_, stmt, elseStmt);
}


ProcedureCallStmtNode* HParser::procedure_call_statement(const string &identifier ) {
  list<ExprNode*> args;
  string variable_name = identifier;
  if ( identifier.empty()){
    variable_name = token_.text;
  }
  match_token(LNG::TN::t_identifier);
  match_token(LNG::TN::t_lparenthesis);
  do {
    args.push_back(expression());
  }while(match_token_if(LNG::TN::t_semicolon));
  match_token(LNG::TN::t_rparenthesis);

  return new ProcedureCallStmtNode(identifier, args);
}

WhileStmtNode* HParser::while_statement() {
  match_token(LNG::TN::t_while);
  auto expr = expression();
  match_token(LNG::TN::t_do);
  auto stmt = statement();
  return new WhileStmtNode(expr, stmt);
}


VariableExprNode* HParser::variable_rvalue(SymbolTable::Entry& entry ) {
  ExprNode *expr = nullptr;
  string variable_name = token_.text;
  match_token(LNG::TN::t_identifier);
  if ( entry.data_type.is_array() ) {
    match_token(LNG::TN::t_lbracket);
    expr = expression();
    match_token(LNG::TN::t_rbracket);
  }
  return new VariableExprNode(variable_name, expr);
}


ExprNode* HParser::simple_expression() {
  static map<LNG::TN, LNG::EO> add_op = {
      {LNG::TN::t_plus, LNG::EO::o_plus},
      {LNG::TN::t_minus, LNG::EO::o_minus},
      {LNG::TN::t_or, LNG::EO::o_or}};

  auto term_ = term();
  auto it = operator_in(add_op);
  while (it != add_op.end()) {
    auto term_rhs = term();
    term_ = new OpExprNode(it->second, term_, term_rhs);
    it = operator_in(add_op);
  }
  return term_;
}


ExprNode* HParser::term() {
    static map<LNG::TN, LNG::EO> mult_op = {
      {LNG::TN::t_multiply, LNG::EO::o_multiply},
      {LNG::TN::t_divide, LNG::EO::o_divide},
      {LNG::TN::t_div, LNG::EO::o_div},
      {LNG::TN::t_and, LNG::EO::o_and}};

  auto compf = complemented_factor();
  auto it = operator_in(mult_op);
  while (it != mult_op.end()) {
    auto compfr = complemented_factor();
    compf = new OpExprNode(it->second, compf, compfr);
    it = operator_in(mult_op);
  }
  return compf;
}


ExprNode* HParser::complemented_factor() {
  if(match_token_if(LNG::TN::t_not)) {
    return new OpExprNode(LNG::EO::o_not, nullptr, signed_factor());
  }
  return signed_factor();
}


ExprNode* HParser::signed_factor() {
  if(match_token_if(LNG::TN::t_plus) ){
    return new OpExprNode(LNG::EO::o_plus, nullptr, factor());
  }
  else if(match_token_if(LNG::TN::t_minus) ){
    return new OpExprNode(LNG::EO::o_minus, nullptr, factor());
  }
  return factor();
}


BooleanExprNode* HParser::boolean_constant() {
  if(match_token_if(LNG::TN::t_true)){
    return new BooleanExprNode(true);
  }
  else if (match_token_if(LNG::TN::t_false)) {
    return new BooleanExprNode(false);
  }
  else {
    error(token_.loc, "Expected boolean constant.");
  }
  return nullptr;
}


RealExprNode* HParser::real_constant() {
    double number = 0;
  if (token_.name == LNG::TN::t_real_l) {
    number = std::stoi(token_.text);
    match_token(LNG::TN::t_real_l);
  } else {
    error(token_.loc, "Expected real constant.");
  }
  return new RealExprNode(number);
}


FunctionCallExprNode* HParser::function_call(const string &identifier ) {
  list<ExprNode*> args;
  string variable_name = identifier;
  if ( identifier.empty()){
    variable_name = token_.text;
  }
  match_token(LNG::TN::t_identifier);
  match_token(LNG::TN::t_lparenthesis);
  do {
    args.push_back(expression());
  }while(match_token_if(LNG::TN::t_semicolon));
  match_token(LNG::TN::t_rparenthesis);

  return new FunctionCallExprNode(identifier, args);
}
