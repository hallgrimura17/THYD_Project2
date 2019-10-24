%require "3.2"
%language "c++"

%code requires
{
#include <string>
#include "common.h"
#include "ast.h"
class BParser;
}

%parse-param { BParser& prs }
%lex-param { BParser& prs }
%locations
%define api.value.type variant
%define api.token.constructor
%define parse.assert
%define parse.trace
%define parse.error verbose

%code
{
  using namespace std;
  using namespace AST;
  #include "bparser.h"
  namespace yy
  {
    // Return the next token.
    auto yylex ( BParser& prs ) -> parser::symbol_type
    {
        prs.lexer_.get( prs.token_ );
        yy::position pos( nullptr, prs.token_.loc.line, prs.token_.loc.col );
        parser::location_type loc( pos, pos );

        switch ( prs.token_.name ) {
        case LNG::TN::t_assign:     return parser::make_t_assign(loc);
        case LNG::TN::t_divide:     return parser::make_t_divide(loc);
        case LNG::TN::t_eq:         return parser::make_t_eq(loc);
        case LNG::TN::t_gt:         return parser::make_t_gt(loc);
        case LNG::TN::t_gteq:       return parser::make_t_gteq(loc);
        case LNG::TN::t_lt:         return parser::make_t_lt(loc);
        case LNG::TN::t_lteq:       return parser::make_t_lteq(loc);
        case LNG::TN::t_minus:      return parser::make_t_minus(loc);
        case LNG::TN::t_multiply:   return parser::make_t_multiply(loc);
        case LNG::TN::t_neq:        return parser::make_t_neq(loc);
        case LNG::TN::t_plus:       return parser::make_t_plus(loc);

        case LNG::TN::t_colon:          return parser::make_t_colon(loc);
        case LNG::TN::t_comma:          return parser::make_t_comma(loc);
        case LNG::TN::t_dot:            return parser::make_t_dot(loc);
        case LNG::TN::t_lbracket:       return parser::make_t_lbracket(loc);
        case LNG::TN::t_lparenthesis:   return parser::make_t_lparenthesis(loc);
        case LNG::TN::t_rbracket:       return parser::make_t_rbracket(loc);
        case LNG::TN::t_rparenthesis:   return parser::make_t_rparenthesis(loc);
        case LNG::TN::t_subrange:       return parser::make_t_subrange(loc);
        case LNG::TN::t_semicolon:      return parser::make_t_semicolon(loc);

        case LNG::TN::t_and:        return parser::make_t_and(loc);
        case LNG::TN::t_array:      return parser::make_t_array(loc);
        case LNG::TN::t_begin:      return parser::make_t_begin(loc);
        case LNG::TN::t_boolean:    return parser::make_t_boolean(loc);
        case LNG::TN::t_div:        return parser::make_t_div(loc);
        case LNG::TN::t_do:         return parser::make_t_do(loc);
        case LNG::TN::t_else:       return parser::make_t_else(loc);
        case LNG::TN::t_end:        return parser::make_t_end(loc);
        case LNG::TN::t_false:      return parser::make_t_false(loc);
        case LNG::TN::t_function:   return parser::make_t_function(loc);
        case LNG::TN::t_if:         return parser::make_t_if(loc);
        case LNG::TN::t_integer:    return parser::make_t_integer(loc);
        case LNG::TN::t_not:        return parser::make_t_not(loc);
        case LNG::TN::t_of:         return parser::make_t_of(loc);
        case LNG::TN::t_or:         return parser::make_t_or(loc);
        case LNG::TN::t_procedure:  return parser::make_t_procedure(loc);
        case LNG::TN::t_program:    return parser::make_t_program(loc);
        case LNG::TN::t_read:       return parser::make_t_read(loc);
        case LNG::TN::t_readln:     return parser::make_t_readln(loc);
        case LNG::TN::t_real:       return parser::make_t_real(loc);
        case LNG::TN::t_then:       return parser::make_t_then(loc);
        case LNG::TN::t_true:       return parser::make_t_true(loc);
        case LNG::TN::t_var:        return parser::make_t_var(loc);
        case LNG::TN::t_while:      return parser::make_t_while(loc);
        case LNG::TN::t_write:      return parser::make_t_write(loc);
        case LNG::TN::t_writeln:    return parser::make_t_writeln(loc);

        case LNG::TN::t_identifier: return parser::make_t_identifier(prs.token_.text, loc);

        case LNG::TN::t_integer_l:  return parser::make_t_integer_l(prs.token_.text, loc);
        case LNG::TN::t_real_l:     return parser::make_t_real_l(prs.token_.text, loc);
        case LNG::TN::t_string_l:   return parser::make_t_string_l(prs.token_.text, loc);

        case LNG::TN::t_eoi:        return parser::make_t_eoi(loc);
        default:                    return parser::make_t_unknown(loc);
        }
    }
  }
}

%nonassoc   t_assign;
%left       t_divide;
%nonassoc   t_eq;
%nonassoc   t_gt;
%nonassoc   t_gteq;
%nonassoc   t_lt;
%nonassoc   t_lteq;
%left       t_minus;
%left       t_multiply;
%nonassoc   t_neq;
%left       t_plus;

%token  t_colon;
%token  t_comma;
%token  t_dot;
%token  t_lbracket;
%token  t_lparenthesis;
%token  t_rbracket;
%token  t_rparenthesis;
%token  t_subrange;
%token  t_semicolon;

%left   t_and;
%token  t_array;
%token  t_begin;
%token  t_boolean;
%token  t_div;
%token  t_do;
%token  t_end;
%token  t_false;
%token  t_function;
%token  t_if;
%token  t_integer;
%right  t_not;
%token  t_of;
%left   t_or;
%token  t_procedure;
%token  t_program;
%token  t_read;
%token  t_readln;
%token  t_real;
%right  t_then t_else;
%token  t_true;
%token  t_var;
%token  t_while;
%token  t_write;
%token  t_writeln;

%token  t_identifier;
%token  t_integer_l;
%token  t_real_l;
%token  t_string_l;

%token  t_eoi 0;
%token  t_unknown

%type <std::string> t_identifier
%type <std::string> t_integer_l
%type <std::string> t_real_l
%type <std::string> t_string_l
%type <AST::BlockNode*> main_block

%type <AST::VariableDeclarationsNode*> variable_declarations
%type <std::list<AST::VariableDeclNode*>> list_variable_declaration
%type <AST::VariableDeclNode*> variable_declaration
%type <std::list<std::string>> list_identifier

%type <LNG::SimpleDataType> simple_type
%type <LNG::DataType> array_type
%type <LNG::DataType> type

%type <AST::CallableDeclarationsNode*> callable_declarations
%type <std::list<AST::CallableDeclNode*>> list_callable_declarations

%type <AST::CompoundStmtNode*> statements
%type <std::list<AST::StmtNode*>> list_statement
%type <AST::StmtNode*> statement
%type <AST::StmtNode*> simple_statement
%type <AST::StmtNode*> structured_statement
%type <AST::CompoundStmtNode*> compound_statement

%type <AST::EmptyStmtNode*> empty_statement
%type <AST::AssignmentStmtNode*> assignment_statement
%type <AST::ExprNode*> expression
%type <AST::ExprNode*> argument
%type <AST::VariableNode*> variable_lvalue


%type <AST::BlockNode*> block

%type <AST::ProcedureDeclNode*> procedure_declaration
%type <AST::FunctionDeclNode*> function_declaration
%type <AST::VariableDeclarationsNode*> optional_parameters
%type <std::list<AST::VariableDeclNode*>> list_optional_parameters
%type <AST::VariableDeclNode*> parameter_list
%type <std::list<AST::ExprNode*>> optional_arguments
%type <std::list<AST::ExprNode*>> list_optional_arguments


%type <AST::IfStmtNode*> if_statement
%type <AST::ProcedureCallStmtNode*> procedure_statement
%type <AST::WhileStmtNode*> while_statement
%type <AST::ReadStmtNode*> read_statement
%type <AST::VariableNode*> input_variable
%type <AST::WriteStmtNode*> write_statement
%type <AST::ExprNode*> output_value

%type <AST::ExprNode*> simple_expression
%type <AST::ExprNode*> term
%type <AST::ExprNode*> complemented_factor
%type <AST::ExprNode*> signed_factor
%type <AST::ExprNode*> factor

%type <LNG::ExprOperator> sign
%type <LNG::ExprOperator> mult_op
%type <LNG::ExprOperator> add_op
%type <LNG::ExprOperator> rel_op


%type <AST::ExprNode*> constant
%type <AST::IntegerExprNode*> integer_constant
%type <AST::RealExprNode*> real_constant
%type <AST::BooleanExprNode*> boolean_constant
%type <AST::StringExprNode*> string_constant

%type <std::string> variable_identifier
%type <std::string> function_identifier
%type <std::string> procedure_identifier
%type <AST::VariableExprNode*> variable_rvalue
%type <AST::FunctionCallExprNode*> function_call
%type <AST::VariableExprNode*> variable
%type <AST::VariableExprNode*> indexed_variable
%type <std::string> array_variable
%type <std::string> entire_variable


%%
program:
    t_program t_identifier t_semicolon
    main_block
    t_dot
    { prs.set_AST( new AST::ProgramNode( $2, $4 ) ); }
;

main_block:
    variable_declarations
    callable_declarations
    compound_statement
    { $$ = new AST::BlockNode( $1, nullptr, $3 ); }   // NOTE
;

variable_declarations:
    t_var list_variable_declaration
    { $$ = new AST::VariableDeclarationsNode( $2 ); }
    |
    { $$ = nullptr; }
;

list_variable_declaration:
    list_variable_declaration variable_declaration t_semicolon
    { $1.push_back( $2 ); $$ = $1; }
    |
    variable_declaration t_semicolon
    { std::list<AST::VariableDeclNode*> lst; lst.push_back( $1 ); $$ = lst; }
;

variable_declaration:
    list_identifier t_colon type
    {
        auto st = prs.get_SymbolTable();
        for (auto &id : $1) {
            auto entry = st->lookup(prs.scope_, id);
            if (entry != nullptr) {
              error(@2, "Duplicate identifier '" + id + "'");
              exit(1);
            }
            st->add_var(prs.scope_, id, $3);
        }
        $$ = new AST::VariableDeclNode( $1, $3 );
    }

list_identifier:
    list_identifier t_comma t_identifier
    { $1.push_back( $3 ); $$ = $1; }
    |
    t_identifier
    { std::list<std::string> lst; lst.push_back( $1 ); $$ = lst; }
;

type:
    simple_type     { $$ = LNG::DataType($1); }
    |
    array_type      { $$ = $1; }
;

simple_type:
    t_integer       { $$ = LNG::SimpleDataType::tInteger; }
    |
    t_boolean       { $$ = LNG::SimpleDataType::tBoolean; }
    |
    t_real          { $$ = LNG::SimpleDataType::tReal; }
;

array_type:
    t_array
    t_lbracket
    t_integer_l
    t_subrange
    t_integer_l
    t_rbracket
    t_of
    simple_type
    { $$ = $$ = LNG::DataType( $8, std::stoi($3), std::stoi($5) ); }
;

compound_statement:
    t_begin
    list_statement
    t_end
    { $$ = new AST::CompoundStmtNode($2); };
;

list_statement:
    list_statement t_semicolon statement
    { $1.push_back( $3 ); $$ = $1; }
    |
    statement
    { std::list<AST::StmtNode*> lst; lst.push_back( $1 ); $$ = lst; }
;

////////////////////////////////////////////////////////////////////////////////////////
//
// Your implementation. Note that the existing entires below are only placeholders,
// which you need to replace with proper code.
//
////////////////////////////////////////////////////////////////////////////////////////

callable_declarations:
    list_callable_declarations
    { $$ = new AST::CallableDeclarationsNode( $1 ); }
    |
    { $$ = nullptr;}
;

list_callable_declarations:
    list_callable_declarations procedure_declaration
    { $1.push_back( $2 ); $$ = $1; }
    |
    list_callable_declarations function_declaration
    { $1.push_back( $2 ); $$ = $1; }
    |
    { std::list<AST::CallableDeclNode*> lst; $$ = lst; }
;

procedure_declaration:
    t_procedure procedure_identifier optional_parameters t_semicolon block t_semicolon
    {prs.scope_ = $2;  $$ = new AST::ProcedureDeclNode($2, $3, $5); prs.scope_ = ""; }
;

function_declaration:
    t_function function_identifier optional_parameters t_colon type t_semicolon block t_semicolon
    {prs.scope_ = $2;  $$ = new AST::FunctionDeclNode($2, $3, $7, $5); prs.scope_ = ""; }
;

procedure_identifier:
    t_identifier { $$ = $1; }
;
function_identifier:
    t_identifier { $$ = $1; }
;
variable_identifier:
    t_identifier { $$ = $1; }
;

parameter_list:
    list_identifier t_colon type
    { $$ = new AST::VariableDeclNode( $1, $3 ); }
;
optional_parameters:
    t_lparenthesis list_optional_parameters t_rparenthesis
    { $$ = new AST::VariableDeclarationsNode( $2 ); }
    |
    {$$ = nullptr;}
;

list_optional_parameters:
    list_optional_parameters t_semicolon parameter_list
    { $1.push_back( $3 ); $$ = $1; }
    |
    variable_declaration
    { std::list<AST::VariableDeclNode*> lst; lst.push_back( $1 ); $$ = lst; }
;

block:
    variable_declarations statements
    { $$ = new AST::BlockNode( $1, $2); }
;

statements:
    compound_statement { $$ = $1;}
;

statement:
    simple_statement     { $$ = $1; }
    |
    structured_statement { $$ = $1; }
;

simple_statement:
    assignment_statement { $$ = $1; }
    |
    procedure_statement { $$ = $1; }
    |
    read_statement { $$ = $1; }
    |
    write_statement { $$ = $1; }
    |
    empty_statement { $$ = $1; }
;

function_call:
    function_identifier optional_arguments
    { $$ = new AST::FunctionCallExprNode($1, $2); }
;

optional_arguments:
    t_lparenthesis list_optional_arguments t_rparenthesis
    { $$ = $2; }
    |
    {std::list<ExprNode*> lst; $$ = lst; }
;

list_optional_arguments:
    list_optional_arguments t_comma argument
    { $1.push_back( $3 ); $$ = $1; }
    |
    argument
    { std::list<AST::ExprNode*> lst; lst.push_back( $1 ); $$ = lst; }
;
argument:
    expression { $$ = $1; }
;

assignment_statement:
    variable_lvalue
    t_assign
    expression
    { $$ = new AST::AssignmentStmtNode( $1, $3); }
    |
    function_identifier
    t_assign
    expression
    { $$ = new AST::AssignmentStmtNode( new AST::VariableNode($1), $3); }
;

procedure_statement:
    procedure_identifier optional_arguments
    { $$ = new AST::ProcedureCallStmtNode($1, $2); }
;

read_statement:
    t_read t_lparenthesis input_variable t_rparenthesis { $$ = new ReadStmtNode($3, false); }
    |
    t_readln t_lparenthesis input_variable t_rparenthesis { $$ = new ReadStmtNode($3, true); }
;

write_statement:
    t_write t_lparenthesis output_value t_rparenthesis { $$ = new AST::WriteStmtNode($3, false); }
    |
    t_writeln t_lparenthesis output_value t_rparenthesis { $$ = new AST::WriteStmtNode($3, true); }
;

input_variable:
    variable_lvalue { $$ = $1; }
;

output_value:
    string_constant { $$ = $1; }
    |
    expression { $$ = $1; }
;

empty_statement:
    { $$ = new AST::EmptyStmtNode(); }
;

structured_statement:
    compound_statement { $$ = $1; }
    |
    if_statement { $$ = $1; }
    |
    while_statement { $$ = $1; }

;

if_statement:
    t_if expression t_then statement t_else statement
    { $$ = new AST::IfStmtNode($2, $4, $6); }
    |
    t_if expression t_then statement
    { $$ = new AST::IfStmtNode($2, $4, nullptr); }
;

while_statement:
    t_while expression t_do statement
    { $$ = new AST::WhileStmtNode($2, $4); }
;

variable_lvalue:
    variable
    {  $$ = new AST::VariableNode( $1->get_name(), $1->get_expr() ); }
;

expression:
    simple_expression
    { $$ = $1; }
    |
    expression rel_op simple_expression
    { $$ = new AST::OpExprNode($2, $1, $3); }
;

simple_expression:
    term
    { $$ = $1; }
    |
    simple_expression add_op term
    { $$ = new AST::OpExprNode($2, $1, $3); }
;

term:
    complemented_factor
    { $$ = $1; }
    |
    term mult_op complemented_factor
    { $$ = new AST::OpExprNode($2, $1, $3); }
;

complemented_factor:
    signed_factor { $$ = $1; }
    |
    t_not signed_factor { $$ = $2; }
;

signed_factor:
    sign factor { $$ = new AST::OpExprNode($1, nullptr, $2); }
    |
    factor { $$ = $1; }
;

factor:
    variable_rvalue { $$ = $1; }
    |
    constant { $$ = $1; }
    | 
    t_lparenthesis expression t_rparenthesis { $$ = $2; }
    |
    function_call { $$ = $1; }
;
rel_op:
    t_eq { $$ = LNG::EO::o_eq; }
    |
    t_neq { $$ = LNG::EO::o_neq; }
    |
    t_lt { $$ = LNG::EO::o_lt; }
    |
    t_lteq { $$ = LNG::EO::o_lteq; }
    |
    t_gt { $$ = LNG::EO::o_gt; }
    |
    t_gteq { $$ = LNG::EO::o_gteq; }
;

add_op:
    t_plus { $$ = LNG::EO::o_plus; }
    |
    t_minus { $$ = LNG::EO::o_minus; }
    |
    t_or { $$ = LNG::EO::o_or; }
;

mult_op:
    t_multiply { $$ = LNG::EO::o_multiply; }
    |
    t_divide { $$ = LNG::EO::o_divide; }
    |
    t_div { $$ = LNG::EO::o_div; }
    |
    t_and { $$ = LNG::EO::o_and; }
;

sign:
    t_plus { $$ = LNG::EO::o_plus; }
    |
    t_minus { $$ = LNG::EO::o_minus; }
;

boolean_constant:
    t_true { $$ = new AST::BooleanExprNode(true); }
    |
    t_false { $$ = new AST::BooleanExprNode(false); }
;

constant:
    integer_constant { $$ = $1; }
    |
    real_constant { $$ = $1; }
    |
    boolean_constant { $$ = $1; }
;

variable_rvalue:
    variable { $$ = $1; }
;

variable:
    entire_variable { $$ = new AST::VariableExprNode($1); }
    |
    indexed_variable { $$ = $1; }
;

indexed_variable:
    array_variable t_lbracket expression t_rbracket { $$ = new AST::VariableExprNode($1, $3); }
;

array_variable:
    entire_variable { $$ = $1; }
;

entire_variable:
    variable_identifier { $$ = $1; }
;

integer_constant:
    t_integer_l { $$ = new AST::IntegerExprNode(std::stoi($1)); }
;

real_constant:
    t_real_l { $$ = new AST::RealExprNode(std::stod($1)); }
;

string_constant:
    t_string_l { $$ = new AST::StringExprNode($1); }
;
%%

  namespace yy
  {
    // Report an error to the user.
    auto parser::error(const location_type& l, const std::string &msg) -> void {
        std::cerr << msg << " at (" << l.begin.line << ',' << l.begin.column << ")\n";
    }
  }
