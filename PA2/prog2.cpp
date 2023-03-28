/*
 * main.cpp
 *
 * CS280 - Spring 2023
 * parser testing program
 */
#include <iostream>
#include <fstream>

#include "lex.h"
#include "parser.h"
#include "lex.cpp"
#include "parser.cpp"


using namespace std;

int main(int argc, char *argv[])
{
	int lineNumber = 1;

	istream *in = NULL;
	ifstream file;


		file.open("testprog7"); // 1,2,3,4,5,6,8,10,11 good
		// fix the line for syntatic error!
	// 7,9,13,14,15 dont work

		in = &file;
	
	
	// cout << "before entering parser" << endl;
	bool status = Prog(*in, lineNumber);
	// cout << "returned from parser" << endl;
	if (!status)
	{
		cout << "Unsuccessful Parsing" << endl
				 << "Number of Syntax Errors " << ErrCount() << endl;
	}
	else
	{
		cout << "Successful Parsing" << endl;
	}
	return 0;
}

