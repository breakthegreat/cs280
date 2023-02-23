#include <regex>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include "lex.h"
#include "lex.cpp"

using namespace std;

bool v = true, nconst = true, sconst = false, ident = false;
string filename = "";

ifstream inClientFile;

int main(int argc, char *argv[])
{
  // HANDLES THE ARGUMENT

  // if(argv[1] != NULL){
  filename = "validops.txt"; // Should be switched to argv[1] when live
  //}

  /*
    for (int i = 1; i < sizeof(argv); ++i)
    {
      if (argv[i] == "-v")
      {

        v = true;
      }
      else if (argv[i] == "-nconst")
      {
        nconst = true;
      }
      else if (argv[i] == "-sconst")
      {

        sconst = true;
      }
      else if (argv[i] == "-ident")
      {

        ident = true;
      }
      else if (argv[i][0] != '-')
      {
        cout << "ONLY ONE FILE NAME IS ALLOWED" << endl;
        exit(1);
      }

      else
      {

        cout << "UNRECOGNIZED FLAG {" << argv[i] << "}";
        exit(1);
      }

    }

   */

  // CHECKS FOR FILENAME EMPTY OR WRONG
  if (filename == "")
  {

    cout << "NO SPECIFIED INPUT FILE" << endl;
    exit(1);
  }

  inClientFile.open(filename.c_str());

  if (!inClientFile)
  {

    cout << "CANNOT OPEN THE FILE " << filename << endl;
    exit(1);
  }
  int lineCount = 0;
  int tokenCount = 0;
  int identCount = 0;
  int numCount = 0;
  int numString = 0;
  // string line;
 
 // YOU SHOULD STORE TOKENS IN DIFFERENT MAPS
    LexItem tok;
    while ((tok = getNextToken(inClientFile, lineCount)) != DONE && tok != ERR)
    {
      tokenCount++;
      if(tok.GetToken() == IDENT || tok.GetToken() == SIDENT || tok.GetToken() == NIDENT){

        identCount++;
      }
      if(tok.GetToken() == ICONST || tok.GetToken() == SCONST || tok.GetToken() == RCONST){

        numCount++;
      }
      if(tok.GetToken() == SCONST){

        numString++;
      }
      if(v){
      cout << tok << endl;
      }
      
    }
    if(tok.GetToken() == ERR){
      cout << "Error in line " << tok.GetLinenum() << " (" << tok.GetLexeme() << ")";
      exit(1);


    }
    if(tok.GetToken() == DONE){
      cout << endl;
      cout << "Lines: " << tok.GetLinenum() << endl;
      cout << "Total Tokens: " << tokenCount << endl;
      cout << "Identifiers: " << identCount << endl;
      cout << "Numbers: " << numCount << endl;
      cout << "Strings: " << numString << endl;

    }
 
if(nconst){
     //if present, prints out all the unique numeric constants (i.e., integer or
//real) in numeric order
      }

if(sconst){
     //if present, prints out all the unique string constants in alphabetical order
      }
if(ident){
  //if present, prints out all of the unique identifiers in alphabetical order
}


  }




// END OF MAIN