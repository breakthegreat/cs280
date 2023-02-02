#include <iostream>
#include <fstream>       
#include <cctype>

#include <cstring> 
#include <sstream>
using namespace std;




int type1(string text) {
int count = 0;
istringstream ss(text);
string tp;
while(getline(ss, tp, ' ')){
   
  bool isNorm = true; 
  if(tp[0] == '$' && isalpha(tp[1]) ){
    
    for (int i = 2; i < tp.length(); ++i){
      if (tp[i] == '_' || isalpha(tp[i]) || isdigit(tp[i])){
          isNorm = true;

      }
      else{

        isNorm = false;
      }

    }

    if(isNorm){
    count += 1;
   
    }
  }



}

return count;




// return number of type1 words  Type 1 names must start by a ‘$’ character
}

int type2(string text) {
int count = 0;
istringstream ss(text);
string tp;
while(getline(ss, tp, ' ')){
  
  bool isNorm = true; 
  if(tp[0] == '@' && isalpha(tp[1]) ){
    
    for (int i = 2; i < tp.length(); ++i){
      if (tp[i] == '_' || isalpha(tp[i]) || isdigit(tp[i])){
          isNorm = true;

      }
      else{

        isNorm = false;
      }

    }

    if(isNorm){
    count += 1;
    }
  }




// return number of type2 words Type 2 names must start by @ character.
  
}
return count;
}

int words(string text) {
int count = 0; // might needto revert this
istringstream ss(text);
string tp, tp2;

getline(ss, tp, ' ');
  istringstream iss(tp);
  while(ss >> tp2){
  
  count +=1;


  












/* return number of words A word is defined as a sequence of one or more non-whitespace characters separated by
 whitespace. */



}
    return count;
}





int allFlag(string text){
int countWords = words(text);
int countType1 = type1(text);
int countType2 = type2(text);

cout << "Total number of words: " << countWords << endl;
      cout << "Number of Type 1 names: " << countType1  << endl;
        cout << "Number of Type 2 names: " << countType2  << endl;





return 0;
}




/*All Type 1 and Type 2 names should consist of a letter following the special start
character, followed by zero or more letters, digits or underscores*/











int main(int argc, char *argv []){

  ifstream inClientFile;
  string filename = "text1.txt"; // SHOULD BE argv[1] when uploading
  string flag = "-all"; // should be argv[2] when uploading
  string lineEmpty;
  string line;



 if(filename == ""){

      cout << "NO SPECIFIED INPUT FILE NAME." << endl;
      exit (1);
    }

    	inClientFile.open(filename.c_str());
		if(!inClientFile)
		{
			cerr << endl;
			cerr << "CANNOT OPEN THE FILE" << " " << filename << endl;
			exit (1);
		}


  

    

    string fileText = "";
    string fileEmpty = "";

    while(getline(inClientFile, line)){
      fileEmpty += line;
      fileText += line + " ";

    }

  

    if( words(fileText) == 1){
      cout << "File is empty." << endl;
      exit (1);
    }

    int wordCount = words(fileText);
    int type1Count = 0;
    int type2Count = 0;
    type1Count = type1(fileText);
    type2Count = type2(fileText);
    
    
    
    if(flag == "-all"){

      allFlag(fileText);
      


    }


    else if(flag == "-type1"){

      type1Count = type1(fileText);

      cout << "Number of Type 1 names: " << type1Count << endl;


    }

    else if(flag == "-type2"){

     type2Count = type2(fileText);
    cout << "Number of Type 2 names: " << type2Count << endl;
    }
    
    
    
    else if(flag != "" &&  flag != "-type2" && flag != "-type1" && flag != "-all"){
      
      cout << "UNRECOGNIZED FLAG " << flag << endl;
      

    }
    else{
      int typeCount =  type1(fileText) + type2(fileText);

      cout << "Total number of words: " << wordCount << endl;
      cout << "Total number of Type 1 and Type 2 names: " << typeCount  << endl;


    }
    




    




    inClientFile.close();

}







// TODO : HANDLE COMMAND LINE ARGUMENT, FILENAME, FLAGS, using arg[]
// TODO : HANDLE PROPER ERROR CODING
// TODO: CREATE METHOD FOR EACH FLAGS









