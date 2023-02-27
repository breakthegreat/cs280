#include <regex>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <cstring>
#include "lex.h"
#include "lex.cpp" // disable this for voc

using namespace std;

bool fv = true, fnconst = true, fsconst = true, fident = true;
string filename = "";

ifstream inClientFile;

int main(int argc, char *argv[])
{
  // HANDLES THE ARGUMENT

   //if(argv[1] != NULL){
  filename = "PA1Testcases/allflags"; // Should be switched to argv[1] when live
 // }

/*


bool goodFlag;
    
  for(int i = 2; i < argc; i++){
        
      
      
      
      
      goodFlag = false;
      
      
      
      
      
      
      
      if (strcmp(argv[i], "-v") == 0)
      {

        fv = true;
          goodFlag = true;
      }
       if (strcmp(argv[i], "-nconst") == 0)
      {
        fnconst = true;
            goodFlag = true;
      }
       if (strcmp(argv[i], "-sconst") == 0)
      {

        fsconst = true;
            goodFlag = true;
      }
      if (strcmp(argv[i], "-ident") == 0)
      {

        fident = true;
           goodFlag = true;
      }
      if (argv[i][0] != '-')
      {
        cout << "ONLY ONE FILE NAME IS ALLOWED." << endl;
        exit(1);
      }
      if(goodFlag == false){
      cout << "UNRECOGNIZED FLAG {" << argv[i] << "}" << endl;
          exit(1);
      
      }
      
      


    }
    
*/
   

  // CHECKS FOR FILENAME EMPTY OR WRONG
  if (filename == "")
  {

    cout << "NO SPECIFIED INPUT FILE." << endl;
    exit(1);
  }

  inClientFile.open(filename.c_str());

  if (!inClientFile)
  {

    cout << "CANNOT OPEN THE FILE " << filename << endl;
    exit(1);
  }
   if(inClientFile.peek()== EOF){
   cout<< "Lines: 0" << endl;
       cout << "Empty File." << endl;
       exit(1);
   
   }
    
    
  int lineCount = 1;
  int tokenCount = 0;
  int identCount = 0;

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
  
  isNumUnique = true;
  isStringUnique = true;
  isIdentUnique = true;
      if (fv)
    {
      
      cout << tok << endl;
    }
    
    if (tok.GetToken() == IDENT || tok.GetToken() == SIDENT || tok.GetToken() == NIDENT)
    {
      
      
      string tempSt = tok.GetLexeme();
    
   
      for(int i = 0; i < identCount; ++i){
        


     

        if(ident[i] == tempSt){
           
          isIdentUnique = false;
        }
       
      }

       if(isIdentUnique){
      
        ident[identCount] = tempSt;
        identCount++;
      //cout << tok.GetLexeme();
     
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
  tokenCount++;

  
  
  }
     
  if (tok.GetToken() == ERR)
  {
    
    cout << "Error in line " << tok.GetLinenum() << " (" << tok.GetLexeme() << ")";
    exit(1);
  }

 
  if (tok.GetToken() == DONE)
  {
    
    cout << endl;
    cout << "Lines: " << lineCount << endl;
    cout << "Total Tokens: " << tokenCount << endl;
    cout << "Identifiers: " << identCount << endl;
    cout << "Numbers: " << numCount << endl;
    cout << "Strings: " << numString << endl;



  }

  
  
  
  
  
  
  
  

  
  
  if (fident)
  {
    
    
   
    
    cout<<"IDENTIFIERS:"<<endl;
   
   
   
   
    sort(ident, ident + identCount);

     
    for (int index = 0; index < identCount; index++)
    {
    if(identCount == 1){

      cout << ident[index];
      
    }
     else if(index == identCount -1 ){

          cout << " "<<ident[index];
      }
    else if(index == 0){

    cout << ident[index] << ",";

    }

      else{
      cout << " " << ident[index] << ",";
      }
    }
    
      
        
      
    cout << endl;

    // if present, prints out all of the unique identifiers in alphabetical order
  }

  if (fnconst)
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
  if (fsconst)
  {
    cout << "STRINGS:" << endl;
    sort(stringConstant, stringConstant + numString);
    for (int i = 0; i < numString; i++)
    {
      cout << stringConstant[i] << endl;
    }
  }
  //cout << endl;

  // if present, prints out all the unique string constants in alphabetical order
}

// END OF MAIN