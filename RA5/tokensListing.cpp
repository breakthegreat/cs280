#include <iostream>
#include <map>
#include <fstream>
#include <cctype>
#include <map>
#include "lex.h"
//#include "ra5.cpp"

/*
 * CS280 - Spring 2023
*/


using std::map;

using namespace std;


istream& operator>>(istream& in, LexItem& tok) {
    
    map <string, Token> StrToTok = {
		{"WRITELN", WRITELN},
		{ "IF", IF },
		{ "ELSE", ELSE },	
		{ "IDENT", IDENT },
		{ "NIDENT", NIDENT },
		{ "SIDENT", SIDENT },
		{ "ICONST", ICONST },
		{ "RCONST", RCONST },
		{ "SCONST", SCONST  },
			
		{ "PLUS", PLUS },
		{ "MINUS" , MINUS },
		{ "MULT" , MULT  },
		{ "DIV" , DIV },
		{ "EXPONENT" , EXPONENT },
		{ "ASSOP", ASSOP },
		{ "NEQ", NEQ  },
		{ "NGTHAN" , NGTHAN  },
		{ "NLTHAN", NLTHAN },
		
		{ "CAT", CAT },
		{ "SREPEAT" , SREPEAT  },
		{ "SEQ", SEQ },
		{ "SGTHAN", SGTHAN },
		{ "SLTHAN", SLTHAN },
		            
		{ "COMMA", COMMA  },
		{ "LPAREN", LPAREN },
		{ "RPAREN", RPAREN },
		{ "LBRACES", LBRACES },
		{ "RBRACES", RBRACES  },
		
		{ "SEMICOL", SEMICOL  },
		
		{ "ERR",ERR  },

		{ "DONE", DONE },
};
	
	Token tt;
	string tokstr, lexeme, str2;
	char ch;
    int i, line, strlen;
		
	in >> tokstr ;
	if(!in)
	{
		return in;
	}
	auto ttitr = StrToTok.find(tokstr);
	//cout << tokstr << endl;
	if(ttitr != StrToTok.end())
	{
		tt = ttitr->second;
		if(tt == IDENT)
		{
			in >> lexeme >> line;
			tok = id_or_kw(lexeme, line);
		
		}
		else if (tt == ICONST || tt == RCONST )
		{
			in >> lexeme >> line;
			LexItem item(tt, lexeme, line);
			tok = item;
		
		}
		else if (tt == SCONST)
		{
			in >> strlen;
			str2 = ""; i = 0;
			ch = in.get();
			while (ch != '\"')
			{
				ch = in.get();
			}
			ch = in.get();
			while ( (ch != '\"') && (i < strlen))
			{
				str2 += ch;
				ch = in.get();
				i++;
			}
			in >> line;
			LexItem item(tt, str2, line);
			tok = item;
		}
		else 
		{
			in >> lexeme >> line;
			LexItem item(tt, lexeme, line);
			tok = item;
			
		}
		
	}
	
	return in;
}

int main(int argc, char *argv[])
{
	LexItem item(ERR, "", 0);
	LexItem& tokItem = item;
	LexItem kwtok;
	ifstream  file ;

	string str1;
	
{
		file.open("case1");
		if( file.is_open() == false ) {
			cerr << "CANNOT OPEN THE FILE " << argv[1] << endl;
			return 0;
		}

	}
	while (file >> tokItem)
	{
		cout << tokItem; //<< endl;
	}
    	
    return 0;
}
