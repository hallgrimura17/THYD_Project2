/* SC-T-603-THYD Fall 2019. Project, lexical analysis. */
%option c++
%option noyywrap
%option yylineno
%{
#include "language.h"
%}
ws [ \t\r\n]+
alpha  [a-zA-Z_]
digit  [0-9]
singleQuotationComment ’([^"\n]*)’
parentAstComment \(\*[^.)]*\*\)
%%

{ws}                        /* empty space, tabs, newline, do nothing */
"{"[^}\n]*"}"               /* single line comment, do nothing */
\(\*[^\*][^\)]*\*\)         /* multi line comment, do nothing */
\'(\\.|[^'\n])*\'           { return LNG::TokenName::t_string; } /* string literal */
"true"                      { return LNG::TokenName::t_boolean; }
"false"                     { return LNG::TokenName::t_boolean; }
{digit}+("."{digit}+)?("e"|"E")("+"|"-")?{digit}+ { return LNG::TokenName::t_real; }
{digit}+"."{digit}+         { return LNG::TokenName::t_real; }
{digit}+                    { return LNG::TokenName::t_integer; }
(?i:absolute)               { return LNG::TokenName::t_absolute; }
(?i:and)                    { return LNG::TokenName::t_and; }
(?i:array)                  { return LNG::TokenName::t_array; }
(?i:begin)                  { return LNG::TokenName::t_begin; }
(?i:boolean)                { return LNG::TokenName::t_boolean; }
(?i:byte)                   { return LNG::TokenName::t_byte; }
(?i:case)                   { return LNG::TokenName::t_case; }
(?i:char)                   { return LNG::TokenName::t_char; }
(?i:const)                  { return LNG::TokenName::t_const; }
(?i:div)                    { return LNG::TokenName::t_div; }
(?i:downto)                 { return LNG::TokenName::t_downto; }
(?i:do)                     { return LNG::TokenName::t_do; }
(?i:else)                   { return LNG::TokenName::t_else; }
(?i:end)                    { return LNG::TokenName::t_end; }
(?i:external)               { return LNG::TokenName::t_external; }
(?i:false)                  { return LNG::TokenName::t_false; }
(?i:file)                   { return LNG::TokenName::t_file; }
(?i:forward)                { return LNG::TokenName::t_forward; }
(?i:function)               { return LNG::TokenName::t_function; }
(?i:goto)                   { return LNG::TokenName::t_goto; }
(?i:if)                     { return LNG::TokenName::t_if; }
(?i:integer)                { return LNG::TokenName::t_integer; }
(?i:in)                     { return LNG::TokenName::t_in; }
(?i:inline)                 { return LNG::TokenName::t_inline; }
(?i:label)                  { return LNG::TokenName::t_label; }
(?i:mod)                    { return LNG::TokenName::t_mod; }
(?i:nil)                    { return LNG::TokenName::t_nil; }
(?i:not)                    { return LNG::TokenName::t_not; }
(?i:of)                     { return LNG::TokenName::t_of; }
(?i:or)                     { return LNG::TokenName::t_or; }
(?i:overlay)                { return LNG::TokenName::t_overlay; }
(?i:packed)                 { return LNG::TokenName::t_packed; }
(?i:procedure)              { return LNG::TokenName::t_procedure; }
(?i:program)                { return LNG::TokenName::t_program; }
(?i:real)                   { return LNG::TokenName::t_real; }
(?i:record)                 { return LNG::TokenName::t_record; }
(?i:repeat)                 { return LNG::TokenName::t_repeat; }
(?i:set)                    { return LNG::TokenName::t_set; }
(?i:shl)                    { return LNG::TokenName::t_shl; }
(?i:shr)                    { return LNG::TokenName::t_shr; }
(?i:string)                 { return LNG::TokenName::t_string; }
(?i:then)                   { return LNG::TokenName::t_then; }
(?i:to)                     { return LNG::TokenName::t_to; }
(?i:true)                   { return LNG::TokenName::t_true; }
(?i:name)                   { return LNG::TokenName::t_type; }
(?i:until)                  { return LNG::TokenName::t_until; }
(?i:var)                    { return LNG::TokenName::t_var; }
(?i:while)                  { return LNG::TokenName::t_while; }
(?i:with)                   { return LNG::TokenName::t_with; }
(?i:xor)                    { return LNG::TokenName::t_xor; }
{alpha}({alpha}|{digit})*   { return LNG::TokenName::t_identifier; }
’([^"\n]*)’                 { return LNG::TokenName::t_string; }
"["                         { return LNG::TokenName::t_lbracket; }
"]"                         { return LNG::TokenName::t_rbracket; }
":="                        { return LNG::TokenName::t_assign; }
">="                        { return LNG::TokenName::t_gteq; }
"<="                        { return LNG::TokenName::t_lteq; }
"<>"                        { return LNG::TokenName::t_neq; }
"="                         { return LNG::TokenName::t_eq; }
">"                         { return LNG::TokenName::t_gt; }
"<"                         { return LNG::TokenName::t_lt; }
"-"                         { return LNG::TokenName::t_minus; }
"*"                         { return LNG::TokenName::t_multiply; }
"+"                         { return LNG::TokenName::t_plus; }
".."                        { return LNG::TokenName::t_subrange; }
":"                         { return LNG::TokenName::t_colon; }
","                         { return LNG::TokenName::t_comma; }
"."                         { return LNG::TokenName::t_dot; }
"("                         { return LNG::TokenName::t_lparenthesis; }
")"                         { return LNG::TokenName::t_rparenthesis; }
";"                         { return LNG::TokenName::t_semicolon; }
.                           { return LNG::TokenName::t_unknown; }
w
%%
 // No need to add any code here.
/*        // Operators
          t_assign = 256,
          t_divide,
          t_eq,
          t_gt, t_gteq,
          t_lt, t_lteq,
          t_minus, t_multiply,
          t_neq,
          t_plus,
          // Punctuation marks.
          t_caret, t_colon, t_comma,
          t_dot,
          t_lbracket, t_lparenthesis,
          t_rbracket, t_rparenthesis,
          t_subrange, t_semicolon,
          // Reserved words.
          t_absolute, t_and, t_array,
          t_begin,
          t_case, t_const,
          t_div, t_do, t_downto,
          t_else, t_end, t_external,
          t_file, t_forward, t_for, t_function,
          t_goto,
          t_if, t_in, t_inline,
          t_label,
          t_mod,
          t_nil, t_not,
          t_of, t_or, t_overlay,
          t_packed, t_procedure, t_program,
          t_record, t_repeat,
          t_set, t_shl, t_shr, t_string,
          t_then, t_to, t_type,
          t_until,
          t_var, t_while, t_with,
          t_xor,
          // Standard scalars
          t_boolean, t_byte, t_char, t_integer, t_real,
          t_false, t_true,
          // ... other words are matched as identifiers.
          t_identifier,
          // Literals.
          t_integer_l, t_real_l, t_string_l,
          // End of input.
          t_eoi,
          // Otherwise matched as an unknown token.
          t_unknown*/