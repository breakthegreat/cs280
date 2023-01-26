#include <iostream>
#include <fstream>       
#include <cstdlib>  // exit prototype
#include <iomanip>

    using namespace std;
    
    int main()
	{
    	ifstream inClientFile;
    	string filename;
    	// if a filename is provided, open file
		cout << "Enter the name of a file to read from: " << endl;
		cin >> filename;
		
		inClientFile.open(filename.c_str());
		if( !inClientFile)
		{
			cerr << endl;
			cerr << "File cannot be opened" << " " << filename << endl;
			exit (1);
		}
       	
		cout << left << setw( 10 ) << "Account" << setw( 13 ) 
            << "Name" << "Balance" << endl << fixed << showpoint;
    
       int account;
       char name[ 30 ];
       double balance;
    	
    	// display each record in file
       while ( inClientFile >> account >> name >> balance )
       {
		   	cout << left << setw( 10 ) << account << setw( 13 ) << name
            << setw( 8 ) << setprecision( 2 ) << right << balance
            << endl;
       } // end while
    
       return 0;  // ifstream destructor closes file
    
    } // end main
