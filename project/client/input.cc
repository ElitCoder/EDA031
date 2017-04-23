#include "input.h"
#include "invalidinputexception.h"

#include <iostream>

using namespace std;

namespace Input {
    string getString() {
        string inputString;
        getline(cin, inputString);
        
        return inputString;
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