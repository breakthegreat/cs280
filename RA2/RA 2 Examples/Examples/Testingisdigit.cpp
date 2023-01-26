#include <iostream>
#include <string>
#include <cctype>
//isdigit example
using namespace std;
int main()
{
	string str = "hds24w7ds", num = "";
	int value, i = 0;
	
	while (i < str.length())
	{
		if (isdigit(str[i]))
			num += str[i];
		i++;
	}
	cout << "The digit characters form the number: "<< num;
	
	return 0;
}
