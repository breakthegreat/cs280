
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

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
        else
        {
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