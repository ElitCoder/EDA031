#ifndef DATABASE_MEMORY_H
#define DATABASE_MEMORY_H

#include "database.h"
//#include "newsgroup.h"

class DatabaseMemory : public Database {
public:
    DatabaseMemory();
    
    virtual void addNewsgroup(const std::string &name) override;
    virtual const std::vector<Newsgroup>& getNewsgroups() const override;
    virtual bool createNewsgroup(const std::string &name) override;
    
private:
    unsigned int m_currentId;
};

#endif