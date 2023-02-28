
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

string DecToBaseN(int num, int base)
{ // NO NEGATIVE INT

    int rem;
    string remainder = "";

    string tp = "";

    if (num == 0)
    {
        return remainder;
    }
   
   
    if (base == 16)
    {

        rem = num % base;
        num = num / base;
        
        if (rem == 10)
        {
            remainder += "A";
        }
        else if (rem == 11)
        {
            remainder += "B";
        }
         else if (rem == 12)
        {
            remainder += "C";
        }
         else if (rem == 13)
        {
            remainder += "D";
        }
         else if (rem == 14)
        {
            remainder += "E";
        }
         else if (rem == 15)
        {
            remainder += "F";
        }
        else{
        remainder += to_string(rem);
        }
        return DecToBaseN(num, base) + remainder;
    }

   
    else if (base > 1 && base <= 10)
    {

        rem = num % base;
        num = num / base;
        remainder += to_string(rem);

        return DecToBaseN(num, base) + remainder;
    }

    else
    {
        cout << "Invalid Base: " << to_string(base);

        return tp;
        // "result of converting the decimal number " + to_string(num)+ "to base " + to_string(base) + ":"
    }
}

int main(int argc, char *argv[])
{

    string tp = DecToBaseN(453, 16);

    cout << tp << endl;

    ifstream inClientFile;
    // if(argv[1] != NULL){
    string filename = "RA6TestCases/case1"; // Should be switched to argv[1] when live
    //}

    if (filename == "")
    {

        cout << "NO SPECIFIED INPUT FILE NAME." << endl;
        exit(1);
    }

    inClientFile.open(filename.c_str());
    if (!inClientFile)
    {

        cout << "CANNOT OPEN THE FILE " << filename << endl;
        exit(1);
    }
    string line = "";
    int num;
    int base;
    int lnIndex = 0;
    while (getline(inClientFile, line))
    {

        if (lnIndex >= 1)
        {
            base = stoi(line);
        }
        else
        {
            num = stoi(line);
        }
        lnIndex++;
    }
}
