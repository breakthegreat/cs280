#include <regex>
#include <fstream>
#include <iostream>
#include <sstream>
#include "lex.h"


using namespace std;



enum tokState {

START,
VARIABLE,
IDENTIFIER, //[Letter _] {( Letter | Digit | _ )}
NUMS, //[0-9] CAN ALSO BE FLOAT POINT
STRING // WORDS IN BETWEEN QUOTATION MARKS




} ;


LexItem getNextToken(istream& in, int& linenumber)
{


tokState lexState = tokState::START;
char ch;

// DRAW DFA FIRST !!!
int line = linenumber;




string lexeme = "";
while(in.get(ch)){ // WHile loop reads each character, in.get(ch) different for each iteration
    
   if (ch =='\n'){
     
      linenumber = linenumber + 1;
      
   }
    
  
  
  
    lexeme = lexeme + ch;
    
    switch(lexState){  
    case START:
    
   /*  if(in.eof() || ch == '\0'){ MIGHT BE USEFUL...

      LexItem temp(DONE,lexeme,linenumber);
      return temp;
   }*/

    
    if(ch == '+'){
        
      LexItem temp(PLUS,lexeme,linenumber);
       
    return temp;
   

       
    }
    else if (ch == '-'){

        LexItem temp(MINUS,lexeme,linenumber);
       
    

       return temp;
      

    }
    else if (ch == '*'){
        // USE PEEK SLIDE NUMBER 12 ON PA 1 DESCRIPTION
        
        
        LexItem temp(MULT,lexeme,linenumber);
        return temp;
    }
    else if (ch == '/'){
        
        LexItem temp(DIV,lexeme,linenumber);
       
    

       return temp;

    }
    else if (ch == '='){
// USE PEEK
        
        
        
        LexItem temp(ASSOP,lexeme,linenumber);

        return temp;
        
        

    }
    else if (ch == '<'){
LexItem temp(NLTHAN,lexeme,linenumber);
       
    

       return temp;


    }
       else if (ch == '>'){
LexItem temp(NGTHAN,lexeme,linenumber);
       
    

       return temp;


    }
    else if (ch == '^'){

        
        LexItem temp(EXPONENT,lexeme,linenumber);
       
    

       return temp;

    }
    else if (ch == '.'){
        
        LexItem temp(CAT,lexeme,linenumber);
       
    

       return temp;

    }
    else if (ch == '('){
LexItem temp(LPAREN,lexeme,linenumber);
       
    

       return temp;


    }

   else if (ch == ')'){
LexItem temp(RPAREN,lexeme,linenumber);
       
    

       return temp;


    }




    else if (ch == '{'){

        LexItem temp(LBRACES,lexeme,linenumber);
       
    

       return temp;


    }

     else if (ch == '}'){

        LexItem temp(RBRACES,lexeme,linenumber);
       
    

       return temp;


    }

     else if (ch == ','){

        LexItem temp(COMMA,lexeme,linenumber);
       
    

       return temp;


    }
      else if (ch == ';'){

        LexItem temp(SEMICOL,lexeme,linenumber);
       
    

       return temp;


    }
   else if (ch == '#' || ' '){
      //cout << "CHECK NEWLINE " << endl;
     
   }


    else if(ch == '_' || isalpha(ch)){

         lexState = tokState::IDENTIFIER;

    }
    else if(isdigit(ch)){

      lexState = tokState::NUMS;

    }
    else if(ch == '$' || ch == '@'){

      lexState = tokState::IDENTIFIER;
    }
    else if (ch == '\''){

      lexState = tokState::STRING;
      

    }

 
   else{

         LexItem temp(ERR,lexeme,linenumber);
         return temp;
   }


    
    break;
    
    case VARIABLE:

    break;
    case IDENTIFIER:

    break;
    case NUMS:

    break;
    case STRING:

    break;
    case DONE:

    break;




    default: // ERROR
    break;




    }

   




} // END WHILE LOOP

LexItem temp(DONE,lexeme,linenumber);
   return temp;



// Do we proceed character by characters?





























/*

    LexItem obj;

    regex IDENT("([a-z]|[A-Z]|_)([a-z A-Z]*[0-9]*[_]*)");
    regex NIDENT("\\$([a-z A-Z]|_)([a-z A-Z]|[0-9]|[_])*");
    regex SIDENT("@([a-z A-Z]|_)([a-z A-Z]|[0-9]|[_])*");
    regex ICONST("[0-9]+");
    regex RCONST("([0-9]+)\\.([0-9]*)");
    regex SCONST("\\'.+\\'");
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
*/
    

    // CHECK EACH REGEX, IF MATCH THEN ADD THE APPROPRIATE TOKEN IF NOT DISPLAY ERROR

    /* LINE COUNTER
    while(getline(in, tp)){
    linenumber += 1;



    }
    */

    
}

LexItem id_or_kw(const string &lexeme, int linenum)
{
}

ostream &operator<<(ostream &out, const LexItem &tok)
{

if(tok.GetToken() == IDENT || tok.GetToken() == NIDENT || tok.GetToken() == SIDENT ||
tok.GetToken() == ICONST ||tok.GetToken() == RCONST || tok.GetToken() == SCONST){
out << tok.GetToken() << "(" << tok.GetLexeme() << ")"<< endl;

}
else{
out << tok.GetToken() << endl;

}

return out;


}