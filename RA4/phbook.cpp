#include <iostream>
#include <map>
#include <string>

using namespace std;


//Dictionary of phonebook in a file and their occurrences
int main(int argc, char *argv [])
{
	map<string,int> Phonebook; 
	string name;
	int phnum;
	

	cout << "Please start to build your phonebook by entering a name followed by a phone number. When you are done enter End of File. " <<  endl;
	while( !cin.eof() ) 
	{
		cin >> name >> phnum;
		Phonebook[name]= phnum;
		
	}
	cout << endl;
	map<string,int>::iterator it;
	cout << "The phonebook contents in order are: " <<endl <<endl;
	for( it = Phonebook.begin(); it != Phonebook.end(); it++ )
		cout << it->first << ": " << it->second << endl;

}
