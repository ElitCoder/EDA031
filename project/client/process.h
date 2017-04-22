#ifndef PROCESS_H
#define PROCESS_H

#include "packet.h"

class Process {
public:
    void process(Packet &packet);
    
private:
    void listNewsgroups();
    void createNewsgroup();
    
    Packet *m_packet;
};

#endif