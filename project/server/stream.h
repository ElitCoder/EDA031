#ifndef STREAM_H
#define STREAM_H

#include "connection.h"

#include <memory>

class Stream {
public:
    void setConnection(std::shared_ptr<Connection> &conn);
    
    void addByte(const unsigned char byte);
    void addInt(const int value);
    void addString(const std::string &str);
    
    unsigned char getByte();
    int getInt();
    std::string getString();
    
private:
    std::shared_ptr<Connection> m_conn;
};

#endif