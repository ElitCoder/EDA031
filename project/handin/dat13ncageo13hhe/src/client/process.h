#ifndef PROCESS_H
#define PROCESS_H

#include "stream.h"

#include <memory>

class Process {
public:
    Process(std::shared_ptr<Connection> &conn);
    
    void process();
    
private:
    void listNewsgroups();
    void createNewsgroup();
    void deleteNewsgroup();
    void listArticles();
    void createArticle();
    void deleteArticle();
    void getArticle();
    
    Stream m_stream;    
};

#endif