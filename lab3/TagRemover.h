#ifndef TAGREMOVER_H
#define TAGREMOVER_H

#include <iostream>

class TagRemover {
public:
    TagRemover(const std::istream &in);
    
    void print(const std::ostream &out);
};

#endif
