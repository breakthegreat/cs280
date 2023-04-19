#ifndef SHORTSTORY_H
#define SHORTSTORY_H
#include "Story.h"

using namespace std;
class ShortStory: public Story{




public:
int lower= 5;
 int upper= 50;
int words;


ShortStory(){

}

ShortStory(string book ,int val){
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
    
  pages = words / val;
  if(pages >= lower && pages <= upper){
    setMsg("Book is accepted.");
  }
   else if(pages < lower){
      int val = lower - pages;
      setMsg("Pages must be added to the book to satisfy the requirements of a Short Story: " + to_string(val));
    }
    else if(pages > upper){
      int val = pages - upper;
      setMsg("Pages must be cut to the book to satisfy the requirements of a Short Story: " + to_string(val));
    }

  }

};
#endif