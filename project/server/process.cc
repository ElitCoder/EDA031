#include "process.h"
#include "protocol.h"
#include "databasememory.h"

#include <iostream>

using namespace std;

Process::Process() : m_database(new DatabaseMemory()) {
}

Process::~Process() {
    delete m_database;
}

Packet& Process::process(Packet &packet) {
    m_currentPacket = &packet;
    m_response.clean();
    
    cout << "Received command: ";
    
    switch(packet.getHeader()) {
        case Protocol::COM_LIST_NG: 
                cout << "COM_LIST_NG.\n";
                commandListNewsgroups();
            break;
            
        case Protocol::COM_CREATE_NG:
                cout << "COM_CREATE_NG.\n";
                commandCreateNewsgroup();
    }
    
    return m_response;
}

void Process::commandListNewsgroups() {
    auto &newsgroups = m_database->getNewsgroups();
    
    m_response.addHeader(Protocol::ANS_LIST_NG);
    m_response.addInt(newsgroups.size());
    
    for(const Newsgroup &newsgroup : newsgroups) {
        m_response.addInt(newsgroup.getId());
        m_response.addString(newsgroup.getName());
    }
    
    m_response.addTail(Protocol::ANS_END);
}

void Process::commandCreateNewsgroup() {
    string name = m_currentPacket->getString();
    bool result = m_database->createNewsgroup(name);
    
    m_response.addHeader(Protocol::ANS_CREATE_NG);
    
    if(result) {
        m_response.addByte(Protocol::ANS_ACK);
    }
    
    else {
        m_response.addByte(Protocol::ANS_NAK);
        m_response.addByte(Protocol::ERR_NG_ALREADY_EXISTS);
    }
    
    m_response.addTail(Protocol::ANS_END);
}