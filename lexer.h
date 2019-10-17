#ifndef TURBOPASCAL_LEXER_H
#define TURBOPASCAL_LEXER_H

#include <istream>
#include "common.h"
#include "language.h"

class Lexer {
public:

  class LexerException: public Common::CompilerException {
   public:
    LexerException( const Common::Location& loc, std::string msg ) : CompilerException( loc, msg ) {}
  };

  struct Token {
        Language::TokenName name;
        std::string text;
        Common::Location loc;
    };

  explicit Lexer( std::istream& is )
    : is_(is), c_('\0'), loc_{1,0}
    {
        c_next();
    }

    void get( Token& token );

private:

    inline bool c_eoi() { return is_.eof(); }

    inline void c_next() {
        c_ = '\0';
        is_.get( c_ );
        if ( c_ == '\n' ) {
            ++loc_.line;
            loc_.col = 0;
        }
        else { ++loc_.col; }
    }

    inline char c_peek() { return (char) is_.peek(); }

    inline bool letter( char c ) { return isalpha( c ) || c == '_'; }
    inline bool digit( char c ) { return static_cast<bool>( isdigit( c ) ); }
    inline bool letter_or_digit( char c ) { return letter( c ) || digit( c ); }

    void set( Token& token, Language::TokenName t ) {
        token.name = t;
        token.text.push_back( c_ );
        c_next();
    }

    template<typename... Rest>
    void set( Token& token, Language::TokenName t, char c, Language::TokenName t1, Rest... rest ) {
        if ( c == c_peek() ) {
            set( token, t1 );
            token.text.push_back( c_ );
            c_next();
        }
        else { set( token, t, rest... ); }
    }

    bool remove_whitespaces();
    bool remove_comment( Token& token );
    void process_string( Token& token );
    void process_digits( Token& token );
    void process_number( Token& token );
    void process_identifier( Token& token );

    std::istream& is_;
    char c_;
    Common::Location loc_;
};
#endif //TURBOPASCAL_LEXER_H
