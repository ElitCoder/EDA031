#ifndef DATABASE_MEMORY_H
#define DATABASE_MEMORY_H

#include "database.h"

class DatabaseMemory : public Database {
public:
    virtual const std::vector<Newsgroup>& getNewsgroups() const override;
    virtual const std::vector<Article>& getArticles(const int id) const override;
    virtual const Article* getArticle(const int groupId, const int articleId) const override;

    
    virtual bool createNewsgroup(const std::string &name) override;
    virtual bool deleteNewsgroup(const int id) override;
    virtual bool newsgroupExists(const int id) override;
    
    virtual bool createArticle(const int id, const std::string &title, const std::string &author, const std::string &text) override;
    virtual bool deleteArticle(const int groupId, const int articleId) override;
};

#endif