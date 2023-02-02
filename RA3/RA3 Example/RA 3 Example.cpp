#include <iostream>
#include <fstream>       
#include <cstdlib>  // exit prototype

using namespace std; 

int main(int argc, char *argv [])
{
	istream *in = &cin;
	ifstream file;
	ofstream outClientFile( "clients.dat", ios::out );
	
	// if a filename is provided, open file
	// make in pointer to point to the opened file object		
	if( argc >= 2 ) 
	{
		file.open(argv[1]);
		if( file.is_open() )
			in = &file;
		else 
		{ /* error */ 
			cerr << "File could not be opened" << endl; 
			exit(1);
		}
	}
	else
	{
	//Get input from the standard input (i.e., keyboard)
		cout << "Enter the account, name, and balance." << endl << 	"Enter end-of-file to end input.\n? ";
	}
	// exit program if unable to create file
   if ( !outClientFile ) 
   {  // overloaded ! operator
      cerr << "File could not be opened" << endl;
      exit( 1 );
	} 
	
  int account;
  char name[ 30 ];
  double balance;

	// read account, name and balance from file or cin, then place 
	// them in output file
	
	while ( *in >> account >> name >> balance ) 
	{
      outClientFile << account << ' ' << name << ' ' << balance
                        << endl;                                   
	} // end while
	
 	return 0;  // ofstream destructor closes the file
} // end main

