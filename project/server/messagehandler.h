#ifndef MESSAGE_HANDLER
#define MESSAGE_HANDLER

#include "connection.h"
#include "packet.h"

#include <memory>

class MessageHandler {
public:
    MessageHandler();
    
    MessageHandler(const MessageHandler &messageHandler) = delete;
    MessageHandler& operator==(const MessageHandler &messageHandler) = delete;
    
    Packet& read(const std::shared_ptr<Connection> &conn);
    void send(const std::shared_ptr<Connection> &conn, const Packet &packet) const;
    
private:
    bool isValidCommand(const unsigned char command) const;
    //std::string readString(const std::shared_ptr<Connection> &conn);
    //int readInt(const std::shared_ptr<Connection> &conn);
    
    Packet m_packet;
};

#endif