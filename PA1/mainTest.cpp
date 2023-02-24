#include <regex>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include "lex.h"
#include "lex.cpp" // disable this for voc

using namespace std;

bool v = true, nconst = true, sconst = true, ident = true;
string filename = "";

ifstream inClientFile;

int main(int argc, char *argv[])
{
  // HANDLES THE ARGUMENT

  // if(argv[1] != NULL){
  filename = "PA1Testcases/allflags"; // Should be switched to argv[1] when live
  //}

  /*

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
  int numIdent = 0;
  int numCount = 0;
  int numString = 0;
  float numbers[100];
  string stringConstant[100];
  string ident[100];

  // string line;
  bool isNumUnique = true;
  bool isStringUnique = true;
  bool isIdentUnique = true;
  // YOU SHOULD STORE TOKENS IN DIFFERENT MAPS
  LexItem tok;
  while ((tok = getNextToken(inClientFile, lineCount)) != DONE && tok != ERR)
  {
    tokenCount++;
    
    
    if (tok.GetToken() == IDENT || tok.GetToken() == SIDENT || tok.GetToken() == NIDENT)
    {
      numIdent++;
      string tempSt = tok.GetLexeme() + ",";
    
   
      for(int i = 0; i < identCount; ++i){
        
        if(ident[i] == tempSt){
           
          isIdentUnique = false;
        }
      }
   
     // cout << tempSt << endl;
       
      
      if(isIdentUnique){
       
      //cout << tok.GetLexeme();
      ident[identCount] = tempSt;
      identCount++;
     }
    }

  


    if (tok.GetToken() == ICONST || tok.GetToken() == RCONST)
    {
      isNumUnique = true;
      float tp = stof(tok.GetLexeme());

      for (int i = 0; i < numCount; ++i)
      {
        if (numbers[i] == tp)
        {
          isNumUnique = false;
          numCount--;
        }
      }

      if (isNumUnique)
      {
        numbers[numCount] = tp;
      }
      numCount++;
    }

    if (tok.GetToken() == SCONST)
    {

      for (int i = 0; i < numString; ++i)
      {
        isStringUnique = true;
        string tempSt = "'" + tok.GetLexeme() + "'";
        if (stringConstant[i] == tempSt)
        {
          isStringUnique = false;
          numString--;
        }
      }
      if (isStringUnique)
      {
        stringConstant[numString] = "'" + tok.GetLexeme() + "'";
      }
      numString++;
    }
    if (v)
    {
      cout << tok << endl;
    }
  }

  if (tok.GetToken() == ERR)
  {
    cout << "Error in line " << tok.GetLinenum() << " (" << tok.GetLexeme() << ")";
    exit(1);
  }
  if (tok.GetToken() == DONE)
  {
    tokenCount++;
    cout << endl;
    cout << "Lines: " << tok.GetLinenum() << endl;
    cout << "Total Tokens: " << tokenCount << endl;
    cout << "Identifiers: " << numIdent << endl;
    cout << "Numbers: " << numCount << endl;
    cout << "Strings: " << numString << endl;



  }

  
  
  
  
  
  
  
  

  
  
  if (ident)
  {
    
    
   
    
    cout<<"IDENTIFIERS:"<<endl;
   
   
   
   
    sort(ident, ident + identCount);

     
    for (int i = 0; i < identCount; i++)
    {
      if(i == identCount - 1){
        ident[i].erase(i,1);
      }

      
      cout << ident[i] << " ";
      
    }
    cout << endl;

    // if present, prints out all of the unique identifiers in alphabetical order
  }

  if (nconst)
  {

    sort(numbers, numbers + numCount);

    cout << "NUMBERS:" << endl;

    for (int i = 0; i < numCount; i++)
    {
      cout << numbers[i] << endl;
    }

    // if present, prints out all the unique numeric constants (i.e., integer or
    // real) in numeric order
  }
  if (sconst)
  {
    cout << "STRINGS:" << endl;
    sort(stringConstant, stringConstant + numString);
    for (int i = 0; i < numString; i++)
    {
      cout << stringConstant[i] << endl;
    }
  }

  // if present, prints out all the unique string constants in alphabetical order
}

// END OF MAIN