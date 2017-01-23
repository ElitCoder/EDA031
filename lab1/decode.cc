#include <iostream>
#include <fstream>

#include "coding.h"

int main(int argc, char **argv) {
    if(argc < 2) {
        std::cout << "Please specify input file.\n";

        return -1;
    }

    std::string file = argv[1];
    std::ifstream in(file, std::ios::binary);

    if(!in) {
        std::cout << "Error opening input file.\n";

        return -1;
    }

    in.seekg(0, std::ios::end);
    auto length = in.tellg();
    in.seekg(0, std::ios::beg);

    char *data = new char[length];
    in.read(data, length);

    in.close();

    for(auto i = 0; i < length; ++i) {
        data[i] = Coding::decode(data[i]);
    }

    std::ofstream out("file.dec", std::ios::binary);

    if(!out) {
        std::cout << "Error opening output file.\n";

        return -1;
    }
    
    out.write(data, length);
    out.close();

    delete[] data;

    return 0;
}
