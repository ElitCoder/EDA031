#ifndef COMMANDER_H
#define COMMANDER_H

#include "packet.h"

class Commander {
public:
    void listNewsgroups();
    void createNewsgroup();
    void deleteNewsgroup();
    void listArticles();
    void createArticle();
    void deleteArticle();
    void getArticle();
    
    const Packet& getPacket() const;
    void clean(); 
    
private:
    Packet m_packet;
};

#endif