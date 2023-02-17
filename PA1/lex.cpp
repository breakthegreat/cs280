#include <regex>
#include <fstream>
#include <iostream>
#include <sstream>
#include "lex.h"
using namespace std;


LexItem getNextToken (istream& in, int& linenumber){

string tp;
LexItem obj;

regex IDENT("([a-z]|[A-Z]|_)([a-z A-Z]*[0-9]*[_]*)");
regex NIDENT("\\$([a-z A-Z]|_)([a-z A-Z]|[0-9]|[_])*");
regex SIDENT("@([a-z A-Z]|_)([a-z A-Z]|[0-9]|[_])*");
regex ICONST("[0-9]+");
regex RCONST("([0-9]+)\\.([0-9]*)");
regex SCONST("\\'[.]=\\'");
regex WRITELN("writeln");
regex isIF("if");
regex isELSE("else");
regex PLUS("\\+");
regex MINUS("\\-");
regex MULT("\\*");
regex DIV("\\/");
regex EXPONENT("\\^");
regex ASSOP("=");
regex NEQ("\\(");
regex NGTHAN("\\)");
regex NLTHAN("\\{\\}");
regex CAT("==");
regex SREPEAT("\\+");
regex SEQ("\\+");
regex SLTHAN("\\+");
regex SGTHAN("\\+");
regex COMMENT("#.*");





// CHECK EACH REGEX, IF MATCH THEN ADD THE APPROPRIATE TOKEN IF NOT DISPLAY ERROR

while(getline(in, tp)){
linenumber += 1;
cout << tp << endl;


}






}


LexItem id_or_kw(const string& lexeme, int linenum){


}

ostream& operator<<(ostream& out, const LexItem& tok){



}