#include "lex.h"










ostream& operator<<(ostream& out, const LexItem& tok){

 map<int, string> tokenName;

   string tokeNames[31] = {
    "WRITELN", "IF", "ELSE", "IDENT", "NIDENT", "SIDENT",
                           "ICONST", "RCONST", "SCONST", "PLUS", "MINUS", "MULT", "DIV", "EXPONENT", "ASSOP",
                           "NEQ", "NGTHAN", "NLTHAN", "CAT", "SREPEAT", "SEQ", "SLTHAN", "SGTHAN", 
                           "COMMA", "SEMICOL", "LPAREN", "RPAREN", "LBRACES", "RBRACES", "ERR", "DONE"


   };
   for (int i = 0; i < 31; ++i)
   {
      tokenName[i] = tokeNames[i];
   }

  Token temp = tok.GetToken();



  if(temp == IDENT){
   return out << "IDENTIFIER: " << tok.GetLexeme() << " at Line " << tok.GetLinenum() << endl;
  }
  else  if(temp == NIDENT || temp == SIDENT){
   return out << tokeNames[temp] << ": \"" << tok.GetLexeme() << "\" at Line " << tok.GetLinenum() << endl;
  }
  else if(temp == ICONST || temp == RCONST)
  {
    return out << tokeNames[temp] << ": (" << tok.GetLexeme() << ") at Line " << tok.GetLinenum() << endl;

  }
  else if(temp == SCONST){
    return  out << "SCONST: '" << tok.GetLexeme() << "' at Line " << tok.GetLinenum() << endl;
  }
  else if (temp == ERR){
    return out << "Error: : \"" << tok.GetLexeme() << "\" at Line " << tok.GetLinenum() << endl;
  }
  else {
   return out << tokeNames[temp] << ": \"" << tok.GetLexeme() << "\" at Line " << tok.GetLinenum() << endl;
  }


  return out << "";
}
LexItem id_or_kw(const string& lexeme, int linenum){
    map <string, Token> StrToTok = {
		{"WRITELN", WRITELN},
		{ "IF", IF },
		{ "ELSE", ELSE },	
		{ "IDENT", IDENT },
		{ "NIDENT", NIDENT },
		{ "SIDENT", SIDENT },
		{ "ICONST", ICONST },
		{ "RCONST", RCONST },
		{ "SCONST", SCONST  },
			
		{ "PLUS", PLUS },
		{ "MINUS" , MINUS },
		{ "MULT" , MULT  },
		{ "DIV" , DIV },
		{ "EXPONENT" , EXPONENT },
		{ "ASSOP", ASSOP },
		{ "NEQ", NEQ  },
		{ "NGTHAN" , NGTHAN  },
		{ "NLTHAN", NLTHAN },
		
		{ "CAT", CAT },
		{ "SREPEAT" , SREPEAT  },
		{ "SEQ", SEQ },
		{ "SGTHAN", SGTHAN },
		{ "SLTHAN", SLTHAN },
		            
		{ "COMMA", COMMA  },
		{ "LPAREN", LPAREN },
		{ "RPAREN", RPAREN },
		{ "LBRACES", LBRACES },
		{ "RBRACES", RBRACES  },
		
		{ "SEMICOL", SEMICOL  },
		
		{ "ERR",ERR  },

		{ "DONE", DONE },
};

map<string,Token>::iterator it;

Token myToken;
bool found = false;
for( it = StrToTok.begin(); it != StrToTok.end(); it++ ){

  if(it -> first == lexeme){
    myToken = it -> second;
    found = true;
  }





}
if(!found){
  if(isalpha(lexeme[0]) || lexeme[0] == '_'){
   LexItem temp(IDENT, lexeme, linenum);
   return temp;

  }
  else if(lexeme[0] == '$'){
    LexItem temp(NIDENT, lexeme, linenum);
   return temp;
  }
  else if(lexeme[0] == '@'){
    LexItem temp(SIDENT, lexeme, linenum);
   return temp;
  }
}
else{

  LexItem temp(myToken, lexeme, linenum);
   return temp;
}
LexItem temp(ERR,lexeme,linenum);
return temp;
}