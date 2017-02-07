#ifndef TAGREMOVER_H
#define TAGREMOVER_H

#include <iostream>

class TagRemover {
public:
    TagRemover(std::istream &in);

    void print(std::ostream &out) const;
private:
    std::string m_html;
};

#endif
