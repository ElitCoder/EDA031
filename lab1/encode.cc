#include <iostream>
#include <fstream>

#include "coding.h"

void test() {
    unsigned char encode = Coding::encode('e');
    unsigned char decode = Coding::decode(encode);

    if(decode == 'e') {
        std::cout << "Correct encryption\n";
    }

    std::cout << "\n----- DEBUG -----\n";
    std::cout << "e\n" << encode << '\n' << decode << "\n\n";
}

int main(int argc, char **argv) {
    using std::ios;

    //test();

    if(argc < 2) {
        std::cout << "No input file.\n";

        return -1;
    }

    std::string file = argv[1];
    std::ifstream in(file, ios::binary);

    in.seekg(0, ios::end);
    int64_t length = in.tellg();
    in.seekg(0, ios::beg);

    char *data = new char[length];
    in.read(data, length);

    in.close();

    for(auto i = 0; i < length; ++i) {
        data[i] = Coding::encode(data[i]);
    }

    std::ofstream out("file.enc", ios::binary);
    out.write(data, length);
    out.close();

    delete[] data;

    return 0;
}
