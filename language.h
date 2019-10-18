
#ifndef TURBOPASCAL_LANGUAGE_H
#define TURBOPASCAL_LANGUAGE_H

#include <string>
#include <sstream>
#include <map>
#include <cassert>

class Language {
 public:

  enum class TokenName {
    // Special symbols.
    t_assign,                    // ... some of the operators.
    t_divide,
    t_eq,
    t_gt, t_gteq,
    t_lt, t_lteq,
    t_minus, t_multiply,
    t_neq,
    t_plus,
    t_colon, t_comma,   // ... various punctuation marks.
    t_dot,
    t_lbracket, t_lparenthesis,
    t_rbracket, t_rparenthesis,
    t_subrange, t_semicolon,
    // Reserved words.
    t_and, t_array,
    t_begin, t_boolean,
    t_div, t_do,
    t_else, t_end,
    t_false, t_function,
    t_if, t_integer,
    t_not,
    t_of, t_or,
    t_procedure, t_program,
    t_read, t_readln, t_real,
    t_then, t_true,
    t_var, t_while, t_write, t_writeln,
    // ... other words are matched as identifiers.
    t_identifier,
    // Literals.
    t_integer_l, t_real_l, t_string_l,
    // End of input.
    t_eoi,
    // Otherwise matched as an unknown token.
    t_unknown
  };
  using TN = TokenName;

  static const std::map<std::string,TokenName> SpecialSymbolToTokenName;

  // The language is case-insensitive, i.e. keywords (and identifiers) can be written
  // as any combination of upper-and lower-case (e.g., 'program', 'Program', or 'PROGRAM').
  static const std::map<std::string,TokenName> ReservedWordToTokenName;
  static std::map<TokenName,std::string> TokenNameToText;

  // Expression operators, listed in order of high-to-low precedence.
  // All the operators are binary except 'o_uminus' and 'o_not', which are unary.
  // The binary operators are left-associative, whereas the unary are right-associative.
  enum class ExprOperator {
    o_uminus,
    o_not,
    o_and, o_multiply, o_div, o_divide,        // 'multiplying' operators
    o_minus, o_or, o_plus,                     // 'adding' operators
    o_eq, o_gt, o_gteq, o_neq, o_lt, o_lteq    // 'relational' operators
  };
  using EO = ExprOperator;

  enum class SimpleDataType {
    tBoolean, tInteger, tReal, tVoid   // Standard scalar types.
  };
  static std::map<Language::SimpleDataType,std::string> SimpleTypeToText;

  class DataType {
  public:
      explicit DataType( SimpleDataType sdt = SimpleDataType:: tVoid, int from = 0 , int to = 0 ) : sdt_(sdt), from_(from), to_(to) {
          assert( from_ >= 0 && from_ <= to_ );
      }
      SimpleDataType get_sdt() const { return sdt_; }
      int get_from_index() const { return from_; }
      int get_to_index() const { return to_; }
      bool is_array() const { return !(from_ == 0 && to_ == 0); }
      std::string str() const {
        std::stringstream ss;
        ss << SimpleTypeToText[get_sdt()];
        if ( is_array() ) {
          ss << "[" << get_from_index() << ".." << get_to_index() << "]";
        }
        return ss.str();
      }
   private:
      SimpleDataType sdt_;
      int from_, to_;
  };

  static void init() {
    populate_tokenname_to_text();
  }

 private:

  static void populate_tokenname_to_text();

  Language() = default; // Do not want the class instantiated, thus private.
};

using LNG = Language;

#endif //TURBOPASCAL_LANGUAGE_H
