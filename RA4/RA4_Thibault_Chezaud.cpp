// thibault chezaud RA4

#include <iostream>
#include <fstream>
#include <cctype>
#include <map>
#include <cstring>
#include <sstream>

#include <regex>
using namespace std;

int words(string text)
{
    int count = 0; // might needto revert this
    istringstream ss(text);
    string tp;

    while (ss >> tp)
    {

        count += 1;

        /* return number of words A word is defined as a sequence of one or more non-whitespace characters separated by
         whitespace. */
    }
    return count;
}



int space(string text){
    int count = 0;
    
        for (int i = 0; i < text.length(); ++i){
            if (isspace(text[i])){

                count += 1;
            }

        }


    
    return count;






}
////////////////////////
//HANDLE SPECIAL NAMES//
////////////////////////

map<string, int> numNames;
  int countNames = 0;


  void handleName(string text){
istringstream ss(text);
  string tp;
  while (getline(ss, tp, ' '))
  {

    bool isNorm = true;
    if (tp[0] == '$' && isalpha(tp[1]))
    {

      for (int i = 2; i < tp.length(); ++i)
      {
        if (!(tp[i] == '_' || isalpha(tp[i]) || isdigit(tp[i])))
        {
          isNorm = false;
        }
      }

      if (isNorm)
      {


        numNames[tp] += 1;
        countNames += 1;
      }
    }
  }


  }


////////////////////////
// HANDLE INTEGER NUM///
////////////////////////


map<int, int> numInteger;
bool isInteger;
int integerCount = 0;

void handleInteger(string text){
istringstream ss1(text);
string tp1;
while (getline(ss1, tp1, ' ')){
string regexPattern = "[+-]*-?[0-9]+";
regex e(regexPattern);



if(regex_match(tp1,e)){

  integerCount += 1;
numInteger[stoi(tp1)] += 1;
   
}
}



/*
while (getline(ss1, tp1, ' ')){

 isInteger = true;
if(tp1[0] == '+' || tp1[0] == '-' || isdigit(tp1[0])){
    


    

 

    for(int i = 0; i < tp1.length();++i){
        
        if(!isdigit(tp1[0]) && tp1.length() <= 1){
          
isInteger = false;
        }

        if(!isdigit(tp1[i]) && i != 0){
           
            isInteger = false;
            
        }
       


    }


    if(isInteger){ 

    integerCount += 1;
    numInteger[stoi(tp1)] += 1;
   

    
} 
    

    

}



 } // END WHILE LOOP
*/

}


////////////////////////
// HANDLE REAL NUMBERS//
////////////////////////
map<float, int> numReal;
bool isReal;
int realCount = 0;

void handleReal(string text){
istringstream ss2(text);
string tp2;

while (getline(ss2, tp2, ' ')){

if(tp2[0] == '+' || tp2[0] == '-' || isdigit(tp2[0])){
int dotCount = 0;
for (int i =0; i < tp2.length(); ++i){



    if(tp2[i] == '.' && isdigit(tp2[i+1])){
        if(tp2[i-1] == '-' || tp2[i-1] == '+'){


        isReal = false;
        }
    else{
        dotCount += 1;
        isReal = true;
    }
    }




    if(!isdigit(tp2[i]) && tp2[i] != '.' ){

        isReal = false;
    }

  
    


}

if(dotCount == 0 || dotCount > 1){

    isReal = false;
}


if (isReal){
realCount += 1;
numReal[stof(tp2)] += 1;

}


}






}





}


int main(int argc, char *argv[])
{

    

    string filename = "";
    string flag;
    ifstream inClientFile;
    string lineEmpty;
    string line;
    //if(argv[1] != NULL){
    filename = "infile4"; // Should be switched to argv[1] when live
    //}

    if (filename == "")
    {

        cout << "NO SPECIFIED INPUT FILE NAME." << endl;
        exit(1);
    }

       inClientFile.open(filename.c_str());
   if (!inClientFile)
    {
        
        cout << "CANNOT OPEN THE FILE "<< filename <<  endl;
        exit(1);
    }

    string fileText;
    string fileEmpty;





    while (getline(inClientFile, line))
    {

        
        
        fileEmpty += line;
        fileText +=  line + " ";
        handleName(line);
        handleInteger(line);
        handleReal(line);
    }
    

    if (words(fileText) == 0 && space(fileEmpty) == 0)
    {
        cout << "File is empty." << endl;
        
        exit(1);
    }

   



cout << "Number of integers in the file: " << integerCount << endl;
cout << "Number of reals in the file: " << realCount << endl;
cout << "Number of special names in the file: " << countNames << endl;
  

if(integerCount != 0){
cout << endl;
cout << "List of integer values and their number of occurrences:" << endl;
map<int,int>::iterator it1;
for( it1 = numInteger.begin(); it1 != numInteger.end(); it1++ ){


cout << it1->first << ": " << it1->second << endl;




}

}



if(realCount != 0){
    
cout << endl;
cout << "List of real values and their number of occurrences:" << endl;
map<float,int>::iterator it2;
for( it2 = numReal.begin(); it2 != numReal.end(); it2++ ){


   cout << it2->first << ": " << it2->second << endl;
}



}




if(countNames != 0){
    
cout << endl;
cout << "List of special names and their number of occurrences:" << endl;
map<string,int>::iterator it;
for( it = numNames.begin(); it != numNames.end(); it++ ){


   cout << it->first << ": " << it->second << endl;
}



}






















} // END OF MAIN 
