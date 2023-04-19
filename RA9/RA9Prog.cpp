#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream> 

#include "Story.h"
#include  "Novel.h"
#include  "Novella.h"
#include "ShortStory.h"

using namespace std;

int main(int argc, char *argv []) 
{
	
	ifstream file;
    vector< Story * > StoryList;
    vector< Story * >::iterator listitr;
	
	Novel *novelbook;
	Novella *novellabook;
	ShortStory *shortbook;
	string strline, title, author, msg, storytype;
	int words, type, wordsperpage;
				
	if( argc >= 2 ) {
		
		file.open(argv[1]);
		if( !file) 
		{
			/* error */ 
			cerr << "File cannot be opened: " << argv[1] << endl;
			exit (1);
        }
        
	}
	else
	{
		cerr << "No file is found." << endl;
		exit (1);
	}
 	
 	
   	while (file >> type >> words >> wordsperpage )
    {
    	file.ignore();
    	getline(file, title, ',');
    	getline(file, author, '\n');
    	
    	if(type == 1)
    	{
    		//Novel
    		novelbook = new Novel("Novel", words);
    		novelbook->setTitle(title);
    		novelbook->setAuthor(author);
    		//novelbook->setWords(words);
    		novelbook->setPages(wordsperpage);
    		StoryList.push_back(novelbook);
    		
		}
		else if(type == 2)
		{
			//Novella
			novellabook = new Novella("Novella");
    		novellabook->setTitle(title);
    		novellabook->setAuthor(author);
    		novellabook->setWords(words);
    		novellabook->setPages(wordsperpage);
    		StoryList.push_back(novellabook);
		}
		else
		{
			//ShortStory
			shortbook = new ShortStory("Short Story", words);
    		shortbook->setTitle(title);
    		shortbook->setAuthor(author);
    		//shortbook->setWords(words);
    		shortbook->setPages(wordsperpage);
    		StoryList.push_back(shortbook);
		}
    	
	}
	
	cout << "List of candidate story books to be published:" << endl ;
    for ( int i = 0; i < StoryList.size(); i++ ) 
    {
    	title = (*StoryList[i]).getTitle();
    	cout<< i+1 << ". " << "Title: " <<  title <<endl;
		
		cout << "Author: " << (*StoryList[i]).getAuthor() << endl;
		cout << "Pages: " << (*StoryList[i]).getPages()  << endl;
		
		cout << "Story Category: " << (*StoryList[i]).getType() << endl;
		
		cout << (*StoryList[i]).getMsg() << endl;                                        
		//
		cout << endl;                                
	}
	
	return 0;
}


