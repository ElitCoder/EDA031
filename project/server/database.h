#ifndef DATABASE_H
#define DATABASE_H

#include "newsgroup.h"

#include <vector>
#include <string>

class Database {
public:
    virtual ~Database() = default;
    
    virtual void addNewsgroup(const std::string &name) = 0;
    virtual const std::vector<Newsgroup>& getNewsgroups() const = 0;
    virtual bool createNewsgroup(const std::string &name) = 0;
    
protected:
    std::vector<Newsgroup> m_newsgroups;
};

#endif