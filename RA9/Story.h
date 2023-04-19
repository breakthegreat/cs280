#ifndef STORY_H
#define STORY_H

#include <string>
using namespace std;
class Story
{

  
public:
  
 
  string title;
  string author;
  int pages;
  string msg;
 string  type;
  Story()
  {
    string type;
  }

  Story(string book)
  {
   type = book;

  }

  void setTitle(string val)
  {
    title = val;
  }
  void setMsg(string val)
  {
    msg = val;
  }
  void setAuthor(string val)
  {
    author = val;
  }
  void setPages(int val)
  {
    pages = val;
  }
  void setType(string val)
  {
   type = val;
  }
 
  string getTitle()
  {
    return title;
  }
  string getAuthor()
  {
    return author;
  }
  int getPages()
  {
    return pages;
  }
  string getMsg()
  {
    return msg;
  }
  string getType()
  {
    
    return type;
  }

  


};
#endif