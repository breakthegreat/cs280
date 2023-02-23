#include <regex>
#include <fstream>
#include <iostream>
#include <sstream>
#include "lex.h"
#include "lex.cpp"

using namespace std;

bool v = false, nconst = false, sconst = false, ident = false;
string filename = "";

ifstream inClientFile;

int main(int argc, char *argv[])
{
  // HANDLES THE ARGUMENT

  // if(argv[1] != NULL){
  filename = "allflags.txt"; // Should be switched to argv[1] when live
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
  int lineCount = 1;
  //string line;






    LexItem tok;
  while((tok = getNextToken(inClientFile, lineCount)) != DONE && tok != ERR ) {
    //cout << "Lexeme: "<< tok.GetLexeme() << " FOR TOKEN: " << tok.GetToken() << " LINE: " << tok.GetLinenum() <<endl;
  cout << tok << endl;
  }
  
  

}
 // END OF MAIN