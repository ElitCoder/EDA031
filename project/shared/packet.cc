#include "packet.h"
#include "protocol.h"
#include "invalidprotocolexception.h"

#include <iostream>
#include <algorithm>

using namespace std;

Packet::Packet() : m_read(1) {
}

void Packet::print() const {
    cout << "\n\nPacket contains: ";
    for_each(m_data.begin(), m_data.end(), [] (const unsigned char c) { printf("0x%.2X ", c); });
    cout << endl;
    
    cout << "In clear text: ";
    for_each(m_data.begin(), m_data.end(), [] (const unsigned char c) { cout << c << " "; });
    cout << "\n\n";
}

void Packet::addInt(const int value, const bool identifier) {
    if(identifier) {
        m_data.push_back(Protocol::PAR_NUM);
    }
    
    m_data.push_back((value >> 24) & 0xFF);
    m_data.push_back((value >> 16) & 0xFF);
    m_data.push_back((value >> 8) & 0xFF);
    m_data.push_back(value & 0xFF);
}

void Packet::addByte(const unsigned char byte) {
    m_data.push_back(byte);
}

void Packet::addString(const string &str) {
    addByte(Protocol::PAR_STRING);
    addInt(str.length(), false);
    
    copy(str.begin(), str.end(), back_inserter(m_data));
}

void Packet::clean() {
    m_data.clear();
    m_read = 1;
}

const vector<unsigned char>& Packet::data() const {
    return m_data;
}

unsigned char Packet::getHeader() const {
    if(m_data.empty()) {
        throw InvalidProtocolException();
    }
    
    return m_data.at(0);
}

string Packet::getString() {
    ++m_read; //SKIP PAR_STRING
    unsigned int size = getInt(false);
    string str;
    
    if(m_data.size() <= (m_read + size)) {
        throw InvalidProtocolException();
    }
    
    for(unsigned int i = 0; i != size; ++i) {
        str += m_data.at(m_read++);
    }
        
    return str;
}

unsigned int Packet::getInt(const bool identifier) {
    if(identifier) {
        ++m_read; //SKIP PAR_NUM
    }
    
    if(m_data.size() <= (m_read + 4)) {
        throw InvalidProtocolException();
    }
    
    unsigned char byte1 = m_data.at(m_read++);
    unsigned char byte2 = m_data.at(m_read++);
    unsigned char byte3 = m_data.at(m_read++);
    unsigned char byte4 = m_data.at(m_read++);

    return (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
}

unsigned char Packet::getByte() {
    return m_data.at(m_read++);
}