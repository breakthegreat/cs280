#include "val.h"
#include <string>
using namespace std;
Value Value::operator*(const Value &op) const
{
  Value result;
  // double oper;
  result.SetType(VREAL);

  if (IsReal() && op.IsReal())
  {

    double num1 = GetReal();
    double num2 = op.GetReal();
    double rslt = num1 * num2;

    result.SetReal(rslt);
    return result;
  }

  else if (!IsReal() || !op.IsReal())
  {

    double num1;
    double num2;

    if (IsErr() || op.IsErr())
    {
      result.SetType(VERR);
      return result;
    }

    if (!IsReal())
    {
      try
      {
        string str = GetString();

        num1 = stod(str);
      }
      catch (...)
      {

        cout << "Invalid conversion from string to double." << endl;
        result.SetType(VERR);
        return result;
      }
    }
    else
    {
      num1 = GetReal();
    }
    if (!op.IsReal())
    {
      try
      {
        string str = op.GetString();

        num2 = stod(str);
      }
      catch (...)
      {

        cout << "Invalid conversion from string to double." << endl;
        result.SetType(VERR);
        return result;
      }
    }
    else
    {
      num2 = op.GetReal();
    }

    double reslt = num1 * num2;
    result.SetReal(reslt);
    return result;
  }
  return result;
}

Value Value::operator==(const Value &op) const
{
  Value result;
  result.SetType(VBOOL);

  if (IsReal() && op.IsReal())
  {
    double num1 = GetReal();
    double num2 = op.GetReal();
    bool rslt = (num1 == num2);
    result.SetBool(rslt);
  }

  if (!IsReal() || !op.IsReal())
  {

    double num1;
    double num2;

    if (IsErr() || op.IsErr())
    {
      result.SetType(VERR);
      return result;
    }
    if (!IsReal())
    {

      try
      {
        string str = GetString();

        num1 = stod(str);
      }
      catch (...)
      {

        cout << "Invalid conversion from string to double." << endl;
        result.SetType(VERR);
        return result;
      }
    }
    else
    {

      num1 = GetReal();
    }
    if (!op.IsReal())
    {

      try
      {
        string str = op.GetString();

        num2 = stod(str);
      }
      catch (...)
      {

        cout << "Invalid conversion from string to double." << endl;
        result.SetType(VERR);
        return result;
      }
    }
    else
    {
      num2 = op.GetReal();
    }
    bool rslt = (num1 == num2);
    result.SetBool(rslt);
    return result;
  }

  return result;
}

Value Value::operator^(const Value &oper) const
{
  Value result;
  // double oper;
  result.SetType(VREAL);
  if (IsReal() && oper.IsReal())
  {
    double num1 = GetReal();
    double num2 = oper.GetReal();
    double rslt = pow(num1, num2);
    result.SetReal(rslt);
    return result;
  }
  else
  {
    result.SetType(VERR);
    return result;
  }

  return result;
}
Value Value::Catenate(const Value &oper) const
{
  Value result;
  string st1,st2;
  result.SetType(VSTRING);
  if (IsString() && oper.IsString())
  {
    
    result.SetType(VSTRING);
     st1 = GetString();
     st2 = oper.GetString();
    string final = st1 + st2;
    result.SetString(final);
    return result;
  }
  
  if(IsReal() || oper.IsReal()){
    
   
   
   
   if(IsReal()){
    
    double num = GetReal();

    try{
    st1 = to_string(num);
    st1.erase(st1.find_last_not_of('0') + 1, std::string::npos);
    if (st1.back() == '.') {
        st1.pop_back();
    }
    }
    catch(...){
      result.SetType(VERR);
      return result;

    }



  }
  else if (!IsString()){
    result.SetType(VERR);
      return result;
  }
  else{
    
    st1 = GetString();
  }

  if(oper.IsReal()){
      
    double num = oper.GetReal();

    try{
      st2 = to_string(num);
      st2.erase(st2.find_last_not_of('0') + 1, std::string::npos);
    if (st2.back() == '.') {
        st2.pop_back();
    }
    }
    catch(...){
      result.SetType(VERR);
      return result;

    }

  }
  else if (!oper.IsString()){
    result.SetType(VERR);
      return result;
  }
  else{
   
  st2 = oper.GetString();
  } 

 
  string rslt = st1 + st2;
  result.SetString(rslt);
  return result;

  }

  result.SetType(VERR);
  return result;
}

Value Value::SLthan(const Value &oper) const
{
Value result;
  string st1,st2;
  result.SetType(VBOOL);
  if (IsString() && oper.IsString())
  {
    
    result.SetType(VSTRING);
     st1 = GetString();
     st2 = oper.GetString();
    bool final = st1 < st2;
      result.SetType(VBOOL);
    result.SetBool(final);
    return result;
  }
  
  if(IsReal() || oper.IsReal()){
    
   
   
   
   if(IsReal()){
    
    double num = GetReal();

    try{
    st1 = to_string(num);
    st1.erase(st1.find_last_not_of('0') + 1, std::string::npos);
    if (st1.back() == '.') {
        st1.pop_back();
    }
    }
    catch(...){
      result.SetType(VERR);
      return result;

    }



  }
  else if (!IsString()){
    result.SetType(VERR);
      return result;
  }
  else{
    
    st1 = GetString();
  }

  if(oper.IsReal()){
      
    double num = oper.GetReal();

    try{
      st2 = to_string(num);
      st2.erase(st2.find_last_not_of('0') + 1, std::string::npos);
    if (st2.back() == '.') {
        st2.pop_back();
    }
    }
    catch(...){
      result.SetType(VERR);
      return result;

    }

  }
  else if (!oper.IsString()){
    result.SetType(VERR);
      return result;
  }
  else{
   
  st2 = oper.GetString();
  } 

 
  bool rslt = st1 < st2;
  result.SetBool(rslt);
  return result;

  }

  result.SetType(VERR);
  return result;
}