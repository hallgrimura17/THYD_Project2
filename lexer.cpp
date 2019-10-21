#include <iostream>

#include <cassert>
#include "common.h"
#include "lexer.h"

void Lexer::get( Token& token )
{
    token.text.clear();
    token.loc = loc_;
    while ( remove_comment( token ) ||
            remove_whitespaces() ) {
        token.loc = loc_;
    }

    if ( c_eoi() ) {
        token.name = LNG::TN::t_eoi;
        return;
    }
    switch ( c_ ) {
        case ';': set( token, LNG::TN::t_semicolon ); break;
        case ':': set( token, LNG::TN::t_colon,
                         '=', LNG::TN::t_assign ); break;
        case '.': set( token, LNG::TN::t_dot,
                         '.', LNG::TN::t_subrange ); break;
        case ',': set( token, LNG::TN::t_comma ); break;
        case '(': set( token, LNG::TN::t_lparenthesis ); break;
        case ')': set( token, LNG::TN::t_rparenthesis ); break;
        case '[': set( token, LNG::TN::t_lbracket ); break;
        case ']': set( token, LNG::TN::t_rbracket ); break;
        case '=': set( token, LNG::TN::t_eq ); break;
        case '>': set( token, LNG::TN::t_gt,
                         '=', LNG::TN::t_gteq ); break;
        case '<': set( token, LNG::TN::t_lt,
                         '=', LNG::TN::t_lteq,
                         '>', LNG::TN::t_neq ); break;
        case '+': set( token, LNG::TN::t_plus ); break;
        case '-': set( token, LNG::TN::t_minus ); break;
        case '*': set( token, LNG::TN::t_multiply ); break;
        case '/': set( token, LNG::TN::t_divide ); break;
        default:
            if ( c_ == '\'' )        { process_string( token ); }
            else if ( digit( c_ ) )  { process_number( token ); }
            else if ( letter( c_ ) ) {
                process_identifier( token );
                auto it = LNG::ReservedWordToTokenName.find( Common::to_lower( token.text ) );
                if ( it != LNG::ReservedWordToTokenName.end() ) {
                    token.name = it->second;
                }
            }
            else { set( token, LNG::TN::t_unknown ); }
    }
}


bool Lexer::remove_whitespaces()
{
    if ( isspace( c_ ) ) {
        for ( ; !c_eoi() && isspace( c_ ); c_next() );
        return true;
    }
    else { return false; }
}


bool Lexer::remove_comment( Token& token )
{
    if (c_ == '{') {
        for ( c_next(); !c_eoi() && c_ != '}'; c_next() );
        if ( c_eoi() ) {
            throw LexerException( token.loc, "Unexpected end of source" );
        }
        else { c_next(); }
        return true;
    }
    else if ( c_ == '(' && c_peek() == '*' ) {
        for ( c_next(), c_next(); !c_eoi() && !(c_ == '*' && c_peek() == ')'); c_next() );
        if ( c_eoi() ) {
            throw LexerException( token.loc, "Unexpected end of source" );
        }
        else { c_next(); c_next(); }
        return true;
    }
    else { return false; }  // No comment removed.
}


void Lexer::process_identifier( Token& token )
{
    assert( letter( c_ ) );

    token.text.push_back( c_ );
    for ( c_next(); !c_eoi() && letter_or_digit( c_ ); c_next() ) {
        token.text.push_back( c_ );
    }
    token.name = LNG::TN::t_identifier;
}


void Lexer::process_string( Token& token )
{
    assert( c_ == '\'' );

    for ( ;; ) {
        c_next();
        if ( c_eoi() ) {
            throw LexerException( token.loc, "Unexpected end of source" );
        }
        else if ( c_ == '\n' ) {
            throw LexerException( token.loc, "String constant exceeds line" );
        }
        if ( c_ == '\'' ) {
            c_next();
            if ( c_ != '\'' ) { break; } // '' is used to represent a ' inside a string
        }
        token.text.push_back( c_ );
    }
    token.name = LNG::TN::t_string_l;
}

void Lexer::process_digits( Token& token )
{
    assert( isdigit( c_ ) );
    for ( ; !c_eoi() && isdigit(c_) ; c_next() ) {
        token.text.push_back(c_);
    }
}

void Lexer::process_number( Token& token )
{
    assert( isdigit( c_ ) );

    // unsigned_integer := digits
    process_digits( token );
    token.name = LNG::TN::t_integer_l;
    // unsigned_real := digits , [ '.' , [ digits ] ] , [ 'E' , [sign] , digits ]
    if ( !c_eoi() && c_ == '.' && c_peek() != '.' ) {   // ... only if not a sub-range, e.g. 1..4
        token.text.push_back( c_ );
        c_next();
        token.name = LNG::TN::t_real_l;
        if ( isdigit( c_ ) ) {
            process_digits(token);
        }
    }
    if ( c_ == 'E' ) {
        token.text.push_back( c_ );
        c_next();
        if ( c_ == '+' || c_ == '-' ) {
            token.text.push_back( c_ );
            c_next();
        }
        if ( isdigit( c_ ) ) {
            process_digits( token );
        }
        else {
            throw LexerException( token.loc, "Error in real constant" );
        }
    }
}
