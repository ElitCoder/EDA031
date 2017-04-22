#include "stream.h"
#include "protocol.h"

#include <algorithm>

using namespace std;

void Stream::addByte(const unsigned char byte) {
    m_conn->write(byte);
}

void Stream::addInt(const int value) {
    m_conn->write(Protocol::PAR_NUM);
    
    m_conn->write((value >> 24) & 0xFF);
    m_conn->write((value >> 16) & 0xFF);
    m_conn->write((value >> 8) & 0xFF);
    m_conn->write(value & 0xFF);
}

void Stream::addString(const string &str) {
    m_conn->write(Protocol::PAR_STRING);
    
    int value = str.length();
    
    m_conn->write((value >> 24) & 0xFF);
    m_conn->write((value >> 16) & 0xFF);
    m_conn->write((value >> 8) & 0xFF);
    m_conn->write(value & 0xFF);
    
    for_each(str.begin(), str.end(), [this] (const unsigned char c) { m_conn->write(c); });
}

unsigned char Stream::getByte() {
    return m_conn->read();
}

int Stream::getInt() {
    m_conn->read(); //SKIP PAR_NUM
    
    unsigned char byte1 = m_conn->read();
    unsigned char byte2 = m_conn->read();
    unsigned char byte3 = m_conn->read();
    unsigned char byte4 = m_conn->read();

    return (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
}

string Stream::getString() {
    unsigned int length = getInt();
    
    /*
    m_conn->read(); //SKIP PAR_STRING
    
    unsigned char byte1 = m_conn->read();
    unsigned char byte2 = m_conn->read();
    unsigned char byte3 = m_conn->read();
    unsigned char byte4 = m_conn->read();
    
    int length = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
    */
    
    string str;
    
    /*
    if(m_data.size() <= (m_read + size)) {
        throw InvalidProtocolException();
    }
    */
    
    for(unsigned int i = 0; i != length; ++i) {
        str += m_conn->read();
    }
        
    return str;
}

void Stream::setConnection(shared_ptr<Connection> &conn) {
    m_conn = conn;
}