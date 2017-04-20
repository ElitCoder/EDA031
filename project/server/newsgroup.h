#ifndef NEWSGROUP_H
#define NEWSGROUP_H

#include "article.h"

#include <string>
#include <vector>

class Newsgroup {
public:
    Newsgroup(const std::string &name, const unsigned int id);
    
    unsigned int getId() const;
    const std::string& getName() const;
    
private:
    std::string m_name;
    unsigned int m_id;
    
    std::vector<Article> m_articles;
};

#endif