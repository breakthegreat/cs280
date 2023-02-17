
#include <regex>
#include <fstream>
#include <iostream>


using namespace std;

int main (int argc, char *argv[]) { 

string myPhrase = "";
regex IDENT("([a-z]|[A-Z]|_)([a-z A-Z]*[0-9]*[_]*)");
regex NIDENT("\\$([a-z A-Z]|_)([a-z A-Z]|[0-9]|[_])*");
regex SIDENT("@([a-z A-Z]|_)([a-z A-Z]|[0-9]|[_])*");
regex SCONST("\\'.+\\'");

if(regex_match(myPhrase,SCONST)){
cout << "MaTCH " << endl;

}
else{

  cout << " no match " << endl;
}
 }