#ifndef COMMANDER_H
#define COMMANDER_H

#include "stream.h"

class Commander {
public:
    Commander(std::shared_ptr<Connection> &conn);
    
    void listNewsgroups();
    void createNewsgroup();
    void deleteNewsgroup();
    void listArticles();
    void createArticle();
    void deleteArticle();
    void getArticle();   
    
private:
    Stream m_stream;
};

#endif