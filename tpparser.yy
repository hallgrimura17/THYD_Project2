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
%token  t_else;
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
%token  t_then;
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

%type <std::list<AST::StmtNode*>> list_statement
%type <AST::StmtNode*> statement
%type <AST::CompoundStmtNode*> compound_statement

%type <AST::EmptyStmtNode*> empty_statement
%type <AST::AssignmentStmtNode*> assignment_statement
%type <AST::ExprNode*> expression
%type <AST::VariableNode*> variable_lvalue


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
    { $$ = new AST::VariableDeclNode( $1, $3 ); }
;

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
    { $$ = nullptr; }
;


statement:
    assignment_statement    { $$ = $1; }
    |
    empty_statement         { $$ = $1; }
;

empty_statement:
    { $$ = new AST::EmptyStmtNode(); }

assignment_statement:
    variable_lvalue
    t_assign
    expression
    { $$ = new AST::AssignmentStmtNode( $1, $3); }
;


variable_lvalue:
    t_identifier
    {  $$ = new AST::VariableNode( $1, nullptr ); }

expression:
    t_integer_l
    { $$ = new AST::IntegerExprNode( std::stoi($1) ); }
;

%%

  namespace yy
  {
    // Report an error to the user.
    auto parser::error(const location_type& l, const std::string &msg) -> void {
        std::cerr << msg << " at (" << l.begin.line << ',' << l.begin.column << ")\n";
    }
  }
