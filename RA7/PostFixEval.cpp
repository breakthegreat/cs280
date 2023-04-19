#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <iterator>
#include <map>
#include <regex>
#include <string.h>

using namespace std;
void PostfixEval(string instr);

int main()
{
  // ifstream file;
  string instr;
  //	cout<<"Please enter a postfix expression for evalution, using only single lowercase characters as variables:" << endl;
  // getline(cin, instr);

  instr = "152 45 x 4 + $y 12 * +";
  // cout << instr << endl;
  PostfixEval(instr);
  // cout << endl;
  // cout<<"Thank you." << endl;

  return 0;
}

void PostfixEval(string instr)
{

  stack<int> intStack;
  map<string, int> varMap;

  // + - * /
  // Store variable into a map
  // when given $Var retrieve variable and its value

  stringstream s(instr);
  string word;
  regex NUM("[0-9]+");
  
  regex VAR("[a-zA-Z]+");
  regex defVAR("[$][a-zA-Z]+");
  string expression;
  while (s >> word)
  {
    expression = expression + word + " ";
    if (regex_match(word, NUM))
    {

      int num = stoi(word);
      intStack.push(num);
     
    }
    else if (word == "+" || word == "-" || word == "/" || word == "*")
    {

      int num1;
      int num2;
      if (!intStack.empty())
      {

        if (word == "+")
        {
          num1 = intStack.top();
          intStack.pop();
          num2 = intStack.top();
          intStack.pop();
          
          int result = num2 + num1;
          intStack.push(result);
         
        }
        else if (word == "-")
        {
          num1 = intStack.top();
          intStack.pop();
          num2 = intStack.top();
          intStack.pop();
         
          int result = num2 - num1;
          intStack.push(result);
          
        }
        else  if (word == "*")
        {
          num1 = intStack.top();
          intStack.pop();
          num2 = intStack.top();
          intStack.pop();
          
          int result = num2 * num1;
          intStack.push(result);
          
        }
        else if (word == "/")
        {
          num1 = intStack.top();
          intStack.pop();
          num2 = intStack.top();
          intStack.pop();
          
          int result = num2 / num1;
          intStack.push(result);
          
        }
        
      }
      
    }

    else if (regex_match(word, VAR))
    {
      //varMap
      word = "$" + word;
      if(!intStack.empty()){
      int numVar = intStack.top();
      intStack.pop();
      varMap[word] = numVar;
      }
      else{
        cout << "Error: Incomplete input postfix expression." << endl;
        return;
      }

    
    }
    else if (regex_match(word, defVAR))
    {
      int numDefVAR = varMap[word];
        intStack.push(numDefVAR);
      


      // cout << word << endl;
    }

    else{
        expression.pop_back();
        cout << "Error: Invalid string: \"" << instr << "\"" << endl;
        return;
      
        }
  }



  if(!intStack.empty()){
    
    int result = intStack.top();
    intStack.pop();
    if(intStack.empty()){
    expression.pop_back();
    cout << "The result of evaluating the postfix expression \"" << 
    expression << "\" is the value: ";
    cout << result<<endl;
    
    
    return;
    }
    else
    cout << "The evaluation is incomplete, missing input operators." << endl;
  }
  else{
    cout << "Error: Incomplete input postfix expression." << endl;
  }


}
