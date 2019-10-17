#include "language.h"

const std::map<std::string,Language::TokenName> Language::ReservedWordToTokenName = {
    {"and", TokenName::t_and},
    {"array", TokenName::t_array},
    {"begin", TokenName::t_begin},
    {"boolean", TokenName::t_boolean},
    {"div", TokenName::t_div},
    {"do", TokenName::t_do},
    {"else", TokenName::t_else},
    {"end", TokenName::t_end},
    {"false", TokenName::t_false},
    {"function", TokenName::t_function},
    {"if", TokenName::t_if},
    {"integer", TokenName::t_integer},
    {"not", TokenName::t_not},
    {"of", TokenName::t_of},
    {"or", TokenName::t_or},
    {"procedure", TokenName::t_procedure},
    {"program", TokenName::t_program},
    {"read", TokenName::t_read},
    {"readln", TokenName::t_readln},
    {"real", TokenName::t_real},
    {"then", TokenName::t_then},
    {"true", TokenName::t_true},
    {"var", TokenName::t_var},
    {"while", TokenName::t_while},
    {"write", TokenName::t_write},
    {"writeln", TokenName::t_writeln}
};

const std::map<std::string,Language::TokenName> Language::SpecialSymbolToTokenName = {
    {":=", TokenName::t_assign},
    {"=", TokenName::t_eq},
    {"/", TokenName::t_divide},
    {">", TokenName::t_gt},
    {">=", TokenName::t_gteq},
    {"<", TokenName::t_lt},
    {"<=", TokenName::t_lteq},
    {"-", TokenName::t_minus},
    {"*", TokenName::t_multiply},
    {"<>", TokenName::t_neq},
    {"+", TokenName::t_plus},
    {":", TokenName::t_colon},
    {",", TokenName::t_comma},
    {".", TokenName::t_dot},
    {"[", TokenName::t_lbracket},
    {"(", TokenName::t_lparenthesis},
    {"]", TokenName::t_rbracket},
    {")", TokenName::t_rparenthesis},
    {"..", TokenName::t_subrange},
    {";", TokenName::t_semicolon}
};

std::map<Language::TokenName,std::string> Language::TokenNameToText;
std::map<Language::SimpleDataType,std::string> Language::SimpleTypeToText;

void Language::populate_tokenname_to_text()
{
  for ( auto& elem : ReservedWordToTokenName ) {
    TokenNameToText[elem.second] = elem.first;
  }
  TokenNameToText[TokenName::t_identifier] = "<identifier>";
  for ( auto& elem : SpecialSymbolToTokenName ) {
    TokenNameToText[elem.second] = elem.first;
  }
  TokenNameToText[TokenName::t_integer_l] = "<integer-literal>";
  TokenNameToText[TokenName::t_real_l] = "<real-literal>";
  TokenNameToText[TokenName::t_string_l] = "<string-literal>";
  TokenNameToText[TokenName::t_eoi] = "<eoi>";
  TokenNameToText[TokenName::t_unknown] = "<unknown>";

  SimpleTypeToText[LNG::SimpleDataType::tVoid] = "void";
  SimpleTypeToText[LNG::SimpleDataType::tInteger] = "integer";
  SimpleTypeToText[LNG::SimpleDataType::tReal] = "real";
  SimpleTypeToText[LNG::SimpleDataType::tBoolean] = "boolean";
}


