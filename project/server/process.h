#ifndef PROCESS_H
#define PROCESS_H

#include "packet.h"
#include "database.h"
#include "connection.h"

#include <memory>

class Process {
public:
    Process();
    ~Process();
    
    Process(const Process &process) = delete;
    Process& operator==(const Process &process) = delete;
    
    Process(const Process &&process) = delete;
    Process& operator==(const Process &&process) = delete;
    
    Packet& process(Packet &packet);
    
private:
    void commandListNewsgroups();
    void commandCreateNewsgroup();
    
    Packet *m_currentPacket;
    Packet m_response;
    Database *m_database;
};

#endif