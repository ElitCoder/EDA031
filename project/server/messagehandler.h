#ifndef MESSAGE_HANDLER
#define MESSAGE_HANDLER

#include "connection.h"

#include <vector>
#include <memory>

class MessageHandler {
public:
    void read(const std::shared_ptr<Connection> &conn);
    void process(const std::shared_ptr<Connection> &conn);
    
private:    
    std::vector<unsigned char> m_buffer;
};

#endif