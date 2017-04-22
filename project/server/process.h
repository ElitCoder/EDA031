#ifndef PROCESS_H
#define PROCESS_H

#include "database.h"
#include "connection.h"
#include "stream.h"

#include <memory>

class Process {
public:
    Process(const bool databaseType);
    ~Process();
    
    Process(const Process &process) = delete;
    Process& operator==(const Process &process) = delete;
    
    Process(const Process &&process) = delete;
    Process& operator==(const Process &&process) = delete;
    
    void process(/*Packet &packet*/std::shared_ptr<Connection> &conn);
    
private:
    void commandListNewsgroups();
    void commandCreateNewsgroup();
    void commandDeleteNewsgroup();
    void commandListArticles();
    void commandCreateArticle();
    void commandGetArticle();
    void commandDeleteArticle();
    
    //Packet *m_currentPacket;
    //Packet m_response;
    Database *m_database;
    Stream m_stream;
};

#endif