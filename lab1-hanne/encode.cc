#include "coding.h"
#include <fstream>
#include <iostream>

using namespace std;


int main(int argc, char* argv[]) {
    ifstream input(argv[1]);
    ofstream output("file.enc");
    if (!input) { // "if the file couldn’t be opened"
        cerr << "Could not open: " << argv[1] << endl;
        exit(1);
    }
// ... read with input >> ...
    char ch;
    while(!input.eof()) {
        input.get(ch);
        unsigned char c1 = Coding::encode(ch);
        output.put(c1);


    }

    output.close();
    input.close();
    }
