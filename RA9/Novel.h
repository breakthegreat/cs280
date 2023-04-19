#ifndef NOVEL_H
#define NOVEL_H
#include "Story.h"
using namespace std;
class Novel : public Story
{

public:
  int lower = 101;
  // const int upper;
  int words;

  Novel()
  {
  }

  Novel(string book, int val)
  {
    words = val;
    type = book;
  }

  int getLower()
  {
    return lower;
  }

  int getWords()
  {
    return words;
  }
  void setWords(int val)
  {
    words = val;
  }
  void setLower(int val)
  {
    lower = val;
  }

  string getType()
  {

    return type;
  }
  void setPages(int val)
  {
    pages = words / val;
    if (pages >= lower)
    {
      setMsg("Book is accepted.");
    }
    else
    {
      if (pages <= lower)
      {
        int val = lower - pages;
        setMsg("Pages must be added to the book to satisfy the requirements of a Novel: " + to_string(val));
      }
    }
  }
};
#endif