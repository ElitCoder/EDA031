#ifndef TAGREMOVER_H
#define TAGREMOVER_H

#include <iostream>

class TagRemover {
public:
    TagRemover(std::istream &in);
    
    void print(std::ostream &out);
private:
    void remove(std::ifstream &file, std::string &input);
    void transform();

    std::string output;
};

#endif
