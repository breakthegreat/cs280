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
		cout << "Enter the name of a file to read from:" << endl;
		cin >> filename;
		
		inClientFile.open(filename.c_str());
		if( !inClientFile)
		{
			cerr << endl;
			cerr << "File cannot be opened" << " " << filename << endl;
			exit (1);
		}
      string tp;
     int numLines = 0;
     int numComment = 0;
     int numNonComment = 0;
     int maxCom = 0;
     int maxNoCom = 0;
     string maxComment = "";
     string maxNonComment = "";
     while(getline(inClientFile, tp)){

      numLines += 1;
      if(tp[0] == '/' && tp[1] == '/' ){

        numComment += 1;
        if(tp.length() > maxCom){
          maxComment = tp;
          maxCom = tp.length();
        }
      }
      else if(tp[0] == '#' && tp[1] == '#' ){
        numComment += 1;

         if(tp.length() > maxCom){
          maxComment = tp;
          maxCom = tp.length();
        }
        
      }
      else{

        numNonComment += 1;

         if(tp.length() > maxNoCom){
          maxNonComment = tp;
          
          maxNoCom = tp.length();
        }


      }



     }
     cout <<"\nTotal Number of Lines: "<< numLines
     
     << "\nNumber of commented lines: " << numComment
     << "\nMaximum Length of commented lines: " << maxCom
     << "\nMaximum Length of non-commented lines: " << maxNoCom
     << "\nCommented line of maximum length: \"" << maxComment << "\""
     << "\nNon-commented line of maximum length: \"" << maxNonComment << "\"" << "\n";

		
    return 0;
    } // end main
