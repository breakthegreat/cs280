#include <iostream>   
using namespace std;

int main()
{
    int character; // 
    
    // prompt user to enter line of text
    cout << "Before input, cin.eof() is " << cin.eof() << endl
            << "Enter a sentence followed by end-of-file:" << endl;
   
    // use get to read each character; use put to display it
    while ( ( character = cin.get() ) != EOF )
        cout.put( character );
    
    // display end-of-file character
    //use int, because char cannot represent EOF
    cout << "\nEOF in this system is: " << (int) character << endl;
    cout << "After input, cin.eof() is " << cin.eof() << endl;
    
    return 0;
}
