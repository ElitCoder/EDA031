#include "messagehandler.h"
#include "protocol.h"
#include "connectionclosedexception.h"

#include <iostream>
#include <algorithm>

using namespace std;

MessageHandler::MessageHandler() {
}

/*
string MessageHandler::readString(const std::shared_ptr<Connection> &conn) {
    string str;
    unsigned char temp;
    
    while((temp = conn->read()) != '$') {
        str += temp;
    }
    
    return str;
}

int MessageHandler::readInt(const std::shared_ptr<Connection> &conn) {
    unsigned char byte1 = conn->read();
    unsigned char byte2 = conn->read();
    unsigned char byte3 = conn->read();
    unsigned char byte4 = conn->read();

    return (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
}
*/

bool MessageHandler::isValidCommand(const unsigned char command) const {
    return true;
    
    //TODO
}

Packet& MessageHandler::read(const shared_ptr<Connection> &conn) {
    m_packet.clean();
    
    unsigned char command = conn->read();
    
    if(!isValidCommand(command)) {
        cout << "Unknown command, disconnection client.\n";
        
        throw ConnectionClosedException();
    }
    
    m_packet.addHeader(command);
    
    while((command = conn->read()) != Protocol::COM_END) {
        m_packet.addByte(command);
    }
    
    m_packet.finish();
    
    return m_packet;
    /*
    m_packet.clean();
    
    unsigned char command = conn->read();
    
    cout << "Received command: 0x";
    printf("%.2X.\n", command);
    
    m_packet.addHeader(command);
    
    switch(command) {
        case Protocol::COM_LIST_NG:
            {
                cout << "Recevied COM_LIST_NG.\n";
            }
            break;
            
        case Protocol::COM_CREATE_NG:
            {
                m_packet.addString(readString(conn));
            }
            break;
            
        default:
            {
                cout << "Unknown command, disconnection client.\n";
                
                throw ConnectionClosedException();
            }
    }
    
    command = conn->read();
    
    if(command != Protocol::COM_END) {
        cout << "Packet was not processed properly.\n";
    }
    
    else {
        cout << "Received COM_END.\n";
    }
    
    m_packet.addTail(command);
    
    return m_packet;
    */
}

void MessageHandler::send(const shared_ptr<Connection> &conn, const Packet &packet) const {
    auto &data = packet.data();
    
    cout << "Sending response: 0x";
    printf("%.2X with length (%zu).\n", packet.getHeader(), data.size());
    
    for_each(data.begin(), data.end(), [&conn] (const unsigned char c) { conn->write(c); });
}