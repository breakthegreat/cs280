
#include <regex>
#include <fstream>
#include <iostream>


using namespace std;

int main (int argc, char *argv[]) { 

string myPhrase = "   'dwdw '   ";

regex SCONST("\\s*\\'(.)+\\'\\s*");
smatch match;
if(regex_match(myPhrase,match,SCONST)){
cout << "MaTCH " << endl;
string myMatch = match[0].str();
cout << myMatch << endl;
}
else{

  cout << " no match " << endl;
}
 }