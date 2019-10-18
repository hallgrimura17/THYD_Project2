#include <iostream>
#include <fstream>
#include <iomanip>
#include "language.h"
#include "hparser.h"
#include "ast.h"
#include "print_visitor.h"
#include "sa_visitor.h"

// NOTE: BParser will be released shortly.

using namespace AST;

using namespace std;
int main( int argc, char* argv[] ) {

  Language::init();

  /*
  std::cout << "Testing lexer ..." << std::endl;
  Lexer lexer(ifs);
  Lexer::Token token;
  lexer.get( token );
  while ( token.name != Language::TokenName::t_eoi ) {
    cout << std::setw( 3) << token.loc.line << '\t'
         << std::setw( 3) << token.loc.col << '\t'
         << std::setw(20) << Language::TokenNameToText[token.name] << '\t'
         << '\'' << token.text << '\'' << endl;
      if ( token.name == Language::TokenName::t_unknown ) {
          cout << "\t<=" << endl;
          break;
      }
      lexer.get( token );
  }
  return 0;
*/

  // Process the command-line arguments, if any.
  // Usage: program [ option [ filename ] ]  (option -h or -b)
  bool use_bison = false;
  if (argc >= 2 && string(argv[1]) == "-b") {
    use_bison = true;
  }
  string filename("test/test.pas");
  if (argc >= 3) {
    filename = argv[2];
  }

  // Open file with Pascal program, exit if error opening file.
  ifstream ifs(filename);
  if (!ifs) {
    cerr << "Could not open input file '" << filename << "'." << endl;
    return -1;
  }

  // Instantiate the right parser.
  Parser *parser;
  if (use_bison) {
    //parser = new BParser(file, false, false); // Change flags to true for debugging.
  } else {
    parser = new HParser(ifs, false, false);
  }

  // Parse and output the generated abstract syntax tree.
  cout << "====> PARSING FILE " << filename
       << " USING PARSER " << parser->get_name() << endl;
  parser->parse();
  cout << "====> AST" << endl;
  Node *ast = parser->get_AST();

  if (ast != nullptr) {
    PrintVisitor pvisitor(cout);
    ast->accept(pvisitor);
  }

  // Clean up and return.
  delete parser;
  return 0;
}