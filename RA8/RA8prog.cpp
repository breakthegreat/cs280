#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include "val.h"

void ExecuteMult(const Value &val1, const Value &val2)
{
	cout << val1 << " * " << val2 << " is " << val1 * val2 << endl;
}

void ExecuteNEQ(const Value &val1, const Value &val2)
{
	cout << val1 << " == " << val2 << " is " << (val1 == val2) << endl;
}

void ExecuteCAT(const Value &val1, const Value &val2)
{
	cout << val1 << " . " << val2 << " is " << (val1.Catenate(val2)) << endl;
}

void ExecuteSLT(const Value &val1, const Value &val2)
{
	cout << val1 << " -lt " << val2 << " is " << (val1.SLthan(val2)) << endl;
}

void ExecuteEXP(const Value &val1, const Value &val2)
{
	cout << val1 << " ^ " << val2 << " is " << (val1 ^ val2) << endl;
}

int main(int argc, char *argv[])
{
	Value ErrorVal;
	double num1 = 7.25;
	Value doubleVal1(num1);
	double num2 = 3;
	Value doubleVal2(num2);
	string str1 = "CS280";
	Value StrVal1(str1);
	string str2 = "Spring 2023";
	Value StrVal2(str2);
	string str3 = "25.7";
	Value StrVal3(str3);
	string str4 = "3.0";
	Value StrVal4(str4);
	vector<Value> vals({ErrorVal, doubleVal1, doubleVal2, StrVal1, StrVal2, StrVal3, StrVal4});
	bool neqflag = false, multflag = false, sltflag = false, catflag = false, powflag = false;

	if (argc == 1)
	{
		cerr << "No Specified arguments." << endl;
		return 0;
	}

	string arg(argv[1]);
	if (arg == "-mult")
		multflag = true;
	else if (arg == "-neq")
		neqflag = true;
	else if (arg == "-cat")
		catflag = true;
	else if (arg == "-slt")
		sltflag = true;
	else if (arg == "-pow")
		powflag = true;
	else
	{
		cerr << "UNRECOGNIZED FLAG " << arg << endl;
		return 0;
	}

	cout << "ErrorVal=" << ErrorVal << endl;
	// cout << "IntVal=" << IntVal << endl;
	cout << "doubleVal1=" << doubleVal1 << endl;
	cout << "doubleVal2=" << doubleVal2 << endl;
	cout << "StrVal1=" << StrVal1 << endl;
	cout << "StrVal2=" << StrVal2 << endl;
	cout << "StrVal3=" << StrVal3 << endl;
	cout << "StrVal4=" << StrVal4 << endl;

	if (multflag)
	{
		for (int i = 0; i < vals.size(); i++)
			for (int j = 0; j < vals.size(); j++)
				if (i != j)
					ExecuteMult(vals[i], vals[j]);
	}

	if (neqflag)
	{
		for (int i = 0; i < vals.size(); i++)
			for (int j = 0; j < vals.size(); j++)
				if (i != j)
					ExecuteNEQ(vals[i], vals[j]);
	}

	if (sltflag)
	{
		for (int i = 0; i < vals.size(); i++)
			for (int j = 0; j < vals.size(); j++)
				if (i != j)
					ExecuteSLT(vals[i], vals[j]);
	}
	if (catflag)
	{
		for (int i = 0; i < vals.size(); i++)
			for (int j = 0; j < vals.size(); j++)
				if (i != j)
					ExecuteCAT(vals[i], vals[j]);
	}

	if (powflag)
	{
		for (int i = 0; i < vals.size(); i++)
			for (int j = 0; j < vals.size(); j++)
				if (i != j)
					ExecuteEXP(vals[i], vals[j]);
	}
	return 0;
}
