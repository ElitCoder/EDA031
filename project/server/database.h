#ifndef DATABASE_H
#define DATABASE_H

#include "newsgroup.h"

#include <vector>
#include <string>

class Database {
public:
    virtual ~Database() = default;
    
    virtual const std::vector<Newsgroup>& getNewsgroups() const = 0;
    virtual const std::vector<Article>& getArticles(const int id) const = 0;
    virtual const Article* getArticle(const int groupId, const int articleId) const = 0;
    
    virtual bool createNewsgroup(const std::string &name) = 0;
    virtual bool deleteNewsgroup(const int id) = 0;
    virtual bool newsgroupExists(const int id) = 0;
    
    virtual bool createArticle(const int id, const std::string &title, const std::string &author, const std::string &text) = 0;
    virtual bool deleteArticle(const int groupId, const int articleId) = 0;
    
    
protected:
    std::vector<Newsgroup> m_newsgroups;
    static unsigned int m_newsgroupId;
};

#endif