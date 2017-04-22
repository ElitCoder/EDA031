#include "process.h"
#include "protocol.h"

#include <iostream>

using namespace std;

void Process::process(Packet &packet) {
    m_packet = &packet;
    
    switch(packet.getHeader()) {
        case Protocol::ANS_LIST_NG: listNewsgroups();
            break;
            
        case Protocol::ANS_CREATE_NG: createNewsgroup();
            break;
    }
}

void Process::listNewsgroups() {
    cout << "Newsgroups:\n";
    
    int nbrGroups = m_packet->getInt();
    
    for(int i = 0; i != nbrGroups; ++i) {
        int id = m_packet->getInt();
        string title = m_packet->getString();
        
        cout << id << ". " << title << endl;
    }
}

void Process::createNewsgroup() {
    int answer = m_packet->getByte();
    
    if(answer == Protocol::ANS_ACK) {
        cout << "Newsgroup was created!";
    }
    
    else {
        answer = m_packet->getByte();
        
        switch(answer) {
            case Protocol::ERR_NG_ALREADY_EXISTS: cout << "Error: newsgroup does already exist.";
                break;
                
            default: cout << "Unknown error code (" << answer << ").";
        }
    }
    
    cout << endl;
}