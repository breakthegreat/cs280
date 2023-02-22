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
   STRING      // WORDS IN BETWEEN QUOTATION MARKS

};

LexItem getNextToken(istream &in, int &linenumber)
{

   tokState lexState = tokState::START;
   char ch;

   // DRAW DFA FIRST !!!

   string lexeme = "";
   while (in.get(ch))
   { // WHile loop reads each character, in.get(ch) different for each iteration

      if (ch == '\n')
      {

         linenumber = linenumber + 1;
         in.get(ch);
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

            LexItem temp(MINUS, lexeme, linenumber);

            return temp;
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

            LexItem temp(CAT, lexeme, linenumber);

            return temp;
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

            lexState = tokState::NUMS;
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

         bool goodChar = true;

         if (lexeme[0] == '$')
         {

            while (in.get(ch) && goodChar)
            {
               if (ch == '\n')
               {
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
            }

            if (goodChar)
            {

               LexItem temp(NIDENT, lexeme, linenumber);

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

         else if (lexeme[0] == '@')
         {

            while (in.get(ch) && goodChar)
            {
               if (ch == '\n')
               {
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

         case NUMS:
   


         break;
      
      
      
      
      
      } // END SWITCH CASE

  
  
  
  
  
  
  
  
  
  
   } // END WHILE LOOP

   LexItem temp(DONE, lexeme, linenumber);
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
      out << tok.GetToken() << "(" << tok.GetLexeme() << ")" << endl;
   }
   else
   {
      out << tok.GetToken() << endl;
   }

   return out;
}