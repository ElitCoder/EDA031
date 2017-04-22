#ifndef DATABASE_DISK_H
#define DATABASE_DISK_H

#include "database.h"

class DatabaseDisk : public Database {
public:
    virtual bool createNewsgroup(const std::string &name) override;
    virtual bool deleteNewsgroup(const int id) override;
    //virtual bool newsgroupExists(const int id) override;
    
    virtual void createArticle(const Newsgroup *newsgroup, const std::string &title, const std::string &author, const std::string &text) override;
    virtual bool deleteArticle(const Newsgroup *newsgroup, const int id) override;
};

#endif