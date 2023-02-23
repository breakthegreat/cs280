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
   OP      // WORDS IN BETWEEN QUOTATION MARKS

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
            if(isalpha(tp)){
               
               lexState = tokState::OP;
               
               
               LexItem temp(MINUS, "-", linenumber);

            return temp;
            

            }
            else{
            
            LexItem temp(MINUS, lexeme, linenumber);

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
            if (in.get(ch).peek() == '=')
            {
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

            lexState = tokState::IDENTIFIER;
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

               LexItem temp(IDENT, lexeme, linenumber);

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
            LexItem temp(SCONST, lexeme, linenumber);
            return temp;
            lexState = tokState::START;
         }
        
      
      
      
      
      }


      case OP:
      string code; 
      {
         
         while(in.get(ch)){


            if(isspace(ch)){
               break;
            }
            if(ch == '\n'){
               linenumber += 1;
               break;
            }
            
         code += ch;
            
            


         }// end while loop

      if(code == "eq"){
         LexItem temp(SEQ, code, linenumber); // when reaching the end of the while loop program is DONE

   return temp;
      }
      if(code == "gt"){
         LexItem temp(SGTHAN, code, linenumber); // when reaching the end of the while loop program is DONE

   return temp;
      }
       if(code == "lt"){
         LexItem temp(SLTHAN, code, linenumber); // when reaching the end of the while loop program is DONE

   return temp;
      }
      else{
        
         LexItem temp(IDENT,code,linenumber);
         return temp;

      }





      } // END CASE OP
      } // END LexState SWITCH CASE

   }                                       // END WHILE LOOP
   LexItem temp(DONE, lexeme, linenumber); // when reaching the end of the while loop program is DONE

   return temp;
}

LexItem id_or_kw(const string &lexeme, int linenum)
{


}

ostream &operator<<(ostream &out, const LexItem &tok)
{

   if (tok.GetToken() == IDENT || tok.GetToken() == NIDENT || tok.GetToken() == SIDENT ||
       tok.GetToken() == ICONST || tok.GetToken() == RCONST || tok.GetToken() == SCONST)
   {
      out << tok.GetToken() << "(" << tok.GetLexeme() << ")";
   }
   else
   {
      out << tok.GetToken();
   }

   return out;
}
