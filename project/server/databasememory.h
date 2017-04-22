#ifndef DATABASE_MEMORY_H
#define DATABASE_MEMORY_H

#include "database.h"

class DatabaseMemory : public Database {
public:
    virtual bool createNewsgroup(const std::string &name) override;
    virtual bool deleteNewsgroup(const int id) override;
    
    virtual void createArticle(Newsgroup *newsgroup, const std::string &title, const std::string &author, const std::string &text) override;
    virtual bool deleteArticle(Newsgroup *newsgroup, const int id) override;
};

#endif