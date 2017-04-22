#ifndef DATABASE_H
#define DATABASE_H

#include "newsgroup.h"

#include <vector>
#include <string>

class Database {
public:
    virtual ~Database() = default;
    
    virtual const std::vector<Newsgroup>& getNewsgroups() const final;
    virtual const Newsgroup* getNewsgroup(const int id) const final;
    
    virtual bool createNewsgroup(const std::string &name) = 0;
    virtual bool deleteNewsgroup(const int id) = 0;
    
    virtual void createArticle(const Newsgroup *newsgroup, const std::string &title, const std::string &author, const std::string &text) = 0;
    virtual bool deleteArticle(const Newsgroup *newsgroup, const int id) = 0;
    
protected:
    std::vector<Newsgroup> m_newsgroups;
    static unsigned int m_newsgroupId;
};

#endif