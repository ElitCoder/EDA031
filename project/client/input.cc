#include "input.h"
#include "invalidinputexception.h"

#include <iostream>

using namespace std;

namespace Input {
    string getString() {
        string inputString;
        getline(cin, inputString);
        
        return inputString;
        
        /*
        string inputString;
        getline(cin, inputString);
        
        int input = 0;
        
        try {
            input = stoi(inputString);
            
            if(input < 0 || input > 7) {
                throw exception();
            }
        } catch(exception &e) {
            cout << "Invalid input, write something understandable. (press enter to continue)";
            cin.get();
            
            cout << "\n\n";
            
            continue;
        }
        return "";*/
    }
    
    int getInt() {
        string inputString = getString();
        int input = 0;
        
        try {
            input = stoi(inputString);
        } catch(exception &e) {
            throw InvalidInputException();
        }
        
        return input;
    }
}