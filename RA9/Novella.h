#ifndef NOVELLA_H
#define NOVELLA_H
#include "Story.h"

using namespace std;

class Novella: public Story{




public:

 int lower = 51;
 int upper= 100;
 int words;


Novella(){

}

Novella(string book){
type = book;
}

Novella(string book,int val){
words = val;
type = book;

}


int getLower(){
  return lower;
}
int getUpper(){
  return upper;
}

int getWords(){
  return words;
}
void setWords(int val){
  words = val;
}
void setLower(int val){
  lower = val;
}
void setUpper(int val){
  upper = val;
}
void setPages(int val)
  {
    //int temp = pages;
    pages = words / val;
    if(pages >= lower && pages <= upper){
    setMsg("Book is accepted.");
    }
    else if(pages < lower){
      int val = lower - pages;
      setMsg("Pages must be added to the book to satisfy the requirements of a Novella: " + to_string(val));
    }
    else if(pages > upper){
      int val = pages - upper;
      setMsg("Pages must be cut from the book to satisfy the requirements of a Novella: " + to_string(val));
    }


  }
};
#endif