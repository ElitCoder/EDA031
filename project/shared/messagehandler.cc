#include "messagehandler.h"
#include "protocol.h"
#include "connectionclosedexception.h"

#include <iostream>
#include <algorithm>

using namespace std;

bool MessageHandler::isValidCommand(const unsigned char command) const {
    return ((command >= Protocol::COM_LIST_NG && command <= Protocol::COM_GET_ART) || (command >= Protocol::ANS_LIST_NG && command <= Protocol::ANS_GET_ART));
}

Packet& MessageHandler::read(const shared_ptr<Connection> &conn) {
    m_packet.clean();
    
    unsigned char command = conn->read();
        
    if(!isValidCommand(command)) {
        cout << "Unknown command - disconnecting client.\n";
        
        throw ConnectionClosedException();
    }
    
    /*
    while(command != Protocol::COM_END && command != Protocol::ANS_END) {
        m_packet.addByte(command);
        
        command = conn->read();
    }
    */
    
    unsigned char commandByte = command;
    
    while(true) {
        m_packet.addByte(command);
        
        //NOT WORKING
        //TODO
        //TODO
        
        if(command == Protocol::COM_END || command == Protocol::ANS_END) {
            break;
        }
        
        command = conn->read();
    }
    
    return m_packet;
}

void MessageHandler::send(const shared_ptr<Connection> &conn, const Packet &packet) const {
    auto &data = packet.data();
    
    //cout << "Sending response: 0x";
    //printf("%.2X with length (%zu).\n", packet.getHeader(), data.size());
    
    for_each(data.begin(), data.end(), [&conn] (const unsigned char c) { conn->write(c); });
}