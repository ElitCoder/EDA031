#ifndef MESSAGE_HANDLER
#define MESSAGE_HANDLER

#include "connection.h"
#include "packet.h"

#include <memory>

class MessageHandler {
public:
    Packet& read(const std::shared_ptr<Connection> &conn);
    void send(const std::shared_ptr<Connection> &conn, const Packet &packet) const;
    
private:
    bool isValidCommand(const unsigned char command) const;
    
    Packet m_packet;
};

#endif