#include <regex>
#include <fstream>
#include <iostream>
#include <sstream>
#include "lex.h"

using namespace std;

enum tokState
{

   START,
   IDENTIFIER, //[Letter _] {( Letter | Digit | _ )}
   NUMS,       //[0-9] CAN ALSO BE FLOAT POINT
   STRING,
   OP // WORDS IN BETWEEN QUOTATION MARKS

};

LexItem getNextToken(istream &in, int &linenumber)
{

   tokState lexState = tokState::START;
   char ch;

   // DRAW DFA FIRST !!!

   string lexeme = "";
   while (in.get(ch))
   { // WHile loop reads each character, in.get(ch) different for each iteration

      while (ch == '\n')
      {

         linenumber = linenumber + 1;

         if (in.peek() == EOF)
         {
            LexItem temp(DONE, lexeme, linenumber); // when reaching the end of the while loop program is DONE

            return temp;
         }

         else
         {
            in.get(ch);
         }
      }

      if (ch == '#')
      {
         ch = ' ';
      }

      if (!isspace(ch))
      {

         lexeme = lexeme + ch;
      }
      switch (lexState)
      {
      case START:

         /*  if(in.eof() || ch == '\0'){ MIGHT BE USEFUL...

            LexItem temp(DONE,lexeme,linenumber);
            return temp;
         }*/

         if (ch == '+')
         {

            LexItem temp(PLUS, lexeme, linenumber);

            return temp;
         }
         else if (ch == '-')
         {

            // IMPLEMENT THE FUCKING -eq, -lt and -gt dumbfuck

            char tp = in.peek();
            if (isalpha(tp))
            {

               string code;
               {

                  while (in.get(ch))
                  {

                     if (isspace(ch))
                     {
                        break;
                     }
                     if (ch == '\n')
                     {
                        linenumber += 1;
                        break;
                     }

                     code += ch;
                  }

                  // end while loop

                  if (code == "eq")
                  {
                     LexItem temp(SEQ, "-eq", linenumber); // when reaching the end of the while loop program is DONE

                     return temp;
                  }
                  if (code == "gt")
                  {
                     LexItem temp(SGTHAN, "-gt", linenumber); // when reaching the end of the while loop program is DONE

                     return temp;
                  }
                  if (code == "lt")
                  {
                     LexItem temp(SLTHAN, "-lt", linenumber); // when reaching the end of the while loop program is DONE

                     return temp;
                  }
                  else
                  {

                     for (int i = code.length(); i >= 0; i--)
                     {

                        in.putback(code[i]); // MIGHT NEED TO FIX EOF
                     }

                     LexItem temp(MINUS, "-", linenumber);
                     return temp;
                  }
               }
            }
            else
            {

               LexItem temp(MINUS, "-", linenumber);

               return temp;
            }
         }

         else if (ch == '*')
         {
            // USE PEEK SLIDE NUMBER 12 ON PA 1 DESCRIPTION

            if (in.get(ch).peek() == '*')
            {
            }

            LexItem temp(MULT, lexeme, linenumber);
            return temp;
         }
         else if (ch == '/')
         {

            LexItem temp(DIV, lexeme, linenumber);

            return temp;
         }
         else if (ch == '=')
         {
            // USE PEEK
            if (in.peek() == '=')
            {
               LexItem temp(ASSOP, lexeme, linenumber);

               return temp;
            }

            LexItem temp(ASSOP, lexeme, linenumber);

            return temp;
         }
         else if (ch == '<')
         {
            LexItem temp(NLTHAN, lexeme, linenumber);

            return temp;
         }
         else if (ch == '>')
         {

            LexItem temp(NGTHAN, lexeme, linenumber);

            return temp;
         }
         else if (ch == '^')
         {

            LexItem temp(EXPONENT, lexeme, linenumber);

            return temp;
         }
         else if (ch == '.')
         {
            in.get(ch);
            if (ch == '\n' || isspace(ch))
            {
               LexItem temp(CAT, lexeme, linenumber);

               return temp;
            }
            else
            {

               in.putback(ch);
               LexItem temp(ERR, lexeme, linenumber);

               return temp;
            }
         }
         else if (ch == '(')
         {
            LexItem temp(LPAREN, lexeme, linenumber);

            return temp;
         }

         else if (ch == ')')
         {
            LexItem temp(RPAREN, lexeme, linenumber);

            return temp;
         }

         else if (ch == '{')
         {

            LexItem temp(LBRACES, lexeme, linenumber);

            return temp;
         }

         else if (ch == '}')
         {

            LexItem temp(RBRACES, lexeme, linenumber);

            return temp;
         }

         else if (ch == ',')
         {

            LexItem temp(COMMA, lexeme, linenumber);

            return temp;
         }
         else if (ch == ';')
         {

            LexItem temp(SEMICOL, lexeme, linenumber);

            return temp;
         }

         else if (ch == '#' || isspace(ch)) // CHECK FOR WHITESPACE AND COMMENT
         {
         }

         else if (ch == '_' || isalpha(ch))
         {
            char tp = in.peek();

            if (tp == '\n' || isspace(tp) || tp == EOF)
            {

               LexItem temp(IDENT, lexeme, linenumber);
               return temp;
            }
            else
            {

               lexState = tokState::IDENTIFIER;
            }
         }
         else if (isdigit(ch))
         {

            // lexState = tokState::NUMS;
            char tp = in.peek();

            if (!isdigit(tp) && tp != '.')
            {

               LexItem temp(ICONST, lexeme, linenumber);
               lexState = tokState::START;
               return temp;
            }
            else
            {

               lexState = tokState::NUMS;
            }
            // in.putback(tp);
         }

         else if (ch == '$' || ch == '@')
         {

            lexState = tokState::IDENTIFIER;
         }
         else if (ch == '\'')
         {

            lexState = tokState::STRING;
         }

         else
         {

            LexItem temp(ERR, lexeme, linenumber);
            return temp;
         }

         break;

      case IDENTIFIER:

      {

         bool goodChar = true;

         if (lexeme[0] == '$')
         {

            char tp = in.peek();

            if (!isalnum(tp) && tp != '_')
            {

               LexItem temp(NIDENT, lexeme, linenumber);

               return temp;

               lexState = tokState::START;

               break;
            }

            while (in.get(ch) && goodChar)
            {
               if (ch == '\n')
               {
                  linenumber = linenumber + 1;
                  break;
               }

               lexeme += ch;
               if (isalnum(ch) || ch == '_')
               {

                  goodChar = true;
               }
               else if (isspace(ch))
               {

                  break;
               }
               else
               {
                  goodChar = false;
               }

               char tp = in.peek();

               if (!isalnum(tp) && tp != '_')
               {

                  LexItem temp(NIDENT, lexeme, linenumber);

                  return temp;

                  lexState = tokState::START;

                  break;
               }
            }

            if (goodChar)
            {

               LexItem temp(NIDENT, lexeme, linenumber);

               return temp;
               lexState = tokState::START;
            }
            else
            {

               lexState = tokState::START;
            }
         }

         else if (lexeme[0] == '@')
         {

            char tp = in.peek();
            if (!isalnum(tp) && tp != '_')
            {

               LexItem temp(SIDENT, lexeme, linenumber);

               return temp;
               lexState = tokState::START;

               break;
            }

            while (in.get(ch) && goodChar)
            {
               if (ch == '\n')
               {
                  linenumber = linenumber + 1;
                  break;
               }

               lexeme += ch;

               if (isalnum(ch) || ch == '_')
               {

                  goodChar = true;
               }
               else if (isspace(ch))
               {

                  break;
               }
               else
               {
                  goodChar = false;
               }

               char tp = in.peek();

               if (!isalnum(tp) && tp != '_')
               {

                  LexItem temp(SIDENT, lexeme, linenumber);

                  return temp;

                  lexState = tokState::START;

                  break;
               }
            }

            if (goodChar)
            {

               LexItem temp(SIDENT, lexeme, linenumber);

               return temp;
               lexState = tokState::START;
            }
            else
            {
               LexItem temp(ERR, lexeme, linenumber);
               return temp;
               lexState = tokState::START;
            }
         }

         else if (lexeme[0] == '_' || isalpha(lexeme[0]))
         {

            while (in.get(ch) && goodChar)
            {
               if (ch == '\n')
               {
                  linenumber = linenumber + 1;
                  break;
               }

               if (isspace(ch))
               {

                  break;
               }

               lexeme += ch;
               if (isalnum(ch) || ch == '_')
               {

                  goodChar = true;
               }

               else
               {
                  goodChar = false;
               }
            }

            if (goodChar)
            {



               
               LexItem temp = id_or_kw(lexeme, linenumber);

               return temp;
               lexState = tokState::START;
            }
            else
            {
               LexItem temp(ERR, lexeme, linenumber);
               return temp;
               lexState = tokState::START;
            }
         }
      } // END CASE IDENTIF

      case NUMS: // FIX THIS SHIT, problem with single digit and single digit + '.'
      {

         bool isFloat = false;
         int dotCount = 0;

         char tp = in.peek();

         if (ch == '.' && dotCount < 2)
         {

            isFloat = true;
            dotCount++;
         }
         if (!isdigit(tp) && tp != '.')
         {

            if (isFloat)
            {
               LexItem temp(RCONST, lexeme, linenumber);
               return temp;
            }
            else
            {
               LexItem temp(ICONST, lexeme, linenumber);
               return temp;
            }
         }

         if (!isdigit(ch) && ch != '.')
         {

            lexState = tokState::START;

            break;
         }

         while (in.get(ch))

         {

            if (!isdigit(ch) && ch != '.')
            {

               lexState = tokState::START;
               break;
            }

            if (ch == '.' && dotCount < 2)
            {

               isFloat = true;
               dotCount++;
               if (dotCount >= 2)
               { // if more than one dot
                  lexeme += ch;
                  LexItem temp(ERR, lexeme, linenumber);
                  return temp;
                  lexState = tokState::START;
               }
            }
            if (ch == '\n')
            {
               linenumber = linenumber + 1;
               break;
            }
            if (isspace(ch))
            {

               break;
            }
            lexeme += ch;
         }

         if (isFloat)
         {
            in.putback(ch);
            LexItem temp(RCONST, lexeme, linenumber);
            return temp;
            lexState = tokState::START;
         }
         else
         {
            LexItem temp(ICONST, lexeme, linenumber);
            return temp;
            lexState = tokState::START;
         }
      } // END CASE NUM

      case STRING:
      {
         while (in.get(ch))
         {
            lexeme += ch; // might be issue linux?
            if (ch == '\'')
            {
               break;
            }
         }

         if (ch != '\'')
         {
            LexItem temp(ERR, lexeme, linenumber);
            return temp;
            lexState = tokState::START;
         }
         else
         {
            lexeme.erase(0, 1);
            lexeme.erase(lexeme.length() - 1, 1);
            LexItem temp(SCONST, lexeme, linenumber);
            return temp;
            lexState = tokState::START;
         }
      }

      } // END LexState SWITCH CASE

   }                                       // END WHILE LOOP
   LexItem temp(DONE, lexeme, linenumber); // when reaching the end of the while loop program is DONE

   return temp;
}

LexItem id_or_kw(const string &lexeme, int linenum)
{
   
  map <string, Token> StrToTok = {
		{"writeln", WRITELN},
		{ "if", IF },
		{ "else", ELSE },	
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
   




ostream &operator<<(ostream &out, const LexItem &tok)

{

   map<int, string> tokenName;

   string tokeNames[31] = {"WRITELN", "IF", "ELSE", "IDENT", "NIDENT", "SIDENT",
                           "ICONST", "RCONST", "SCONST", "PLUS", "MINUS", "MULT", "DIV", "EXPONENT", "ASSOP",
                           "LPAREN", "RPAREN", "LBRACES", "RBRACES", "NEQ", "NGTHAN", "NLTHAN", "CAT", "SREPEAT", "SEQ", "SLTHAN", "SGTHAN", "COMMA", "SEMICOL", "ERR", "DONE"

   };

   for (int i = 0; i < 31; ++i)
   {
      tokenName[i] = tokeNames[i];
   }

   if (tok.GetToken() == IDENT || tok.GetToken() == NIDENT || tok.GetToken() == SIDENT ||
       tok.GetToken() == ICONST || tok.GetToken() == RCONST || tok.GetToken() == SCONST)
   {
      out << tokeNames[tok.GetToken()] << "(" << tok.GetLexeme() << ")";
   }
   else
   {

      out << tokeNames[tok.GetToken()];
   }

   return out;
}
