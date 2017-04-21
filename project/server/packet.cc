#include "packet.h"
#include "protocol.h"
#include "connectionclosedexception.h"

#include <iostream>
#include <algorithm>

using namespace std;

Packet::Packet() : m_finalized(false), m_read(1) {
}

ostream& operator<<(ostream& out, const Packet &packet) {
    for_each(packet.m_data.begin(), packet.m_data.end(), [&out] (const unsigned char c) { out << hex << c << dec << " "; });
    
    return out;
}

bool Packet::isEditable() {
    return !m_finalized;
}

void Packet::addInt(const int value, const bool identifier) {
    if(!isEditable()) {
        return;
    }
    
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
    if(!isEditable()) {
        return;
    }
    
    m_data.push_back(Protocol::PAR_STRING);
    addInt(str.length(), false);
    
    copy(str.begin(), str.end(), back_inserter(m_data));
}

void Packet::addHeader(const unsigned char header) {
    if(!isEditable()) {
        return;
    }
    
    m_data.push_back(header);
}

void Packet::addTail(const unsigned char tail) {
    if(!isEditable()) {
        return;
    }
    
    m_data.push_back(tail);
    
    finish();
}

void Packet::clean() {
    m_data.clear();
    m_finalized = false;
    m_read = 1;
}

void Packet::finish() {
    m_finalized = true;
}

const vector<unsigned char>& Packet::data() const {
    return m_data;
}

unsigned char Packet::getHeader() const {
    if(m_data.size() == 0) {
        cout << "ERROR: Caught getHeader() with packet-size 0.\n";
        
        throw ConnectionClosedException();
    }
    
    return m_data.at(0);
}

string Packet::getString() {
    ++m_read; //SKIP PAR_STRING
    unsigned int size = getInt(false);
    string str;
    
    cout << "String with size: " << size << endl;
    
    for(unsigned int i = 0; i != size; ++i) {
        str += m_data.at(m_read++);
    }
    
    cout << "Successfully read string.\n";
    
    return str;
}

unsigned int Packet::getInt(const bool identifier) {
    if(identifier) {
        ++m_read; //SKIP PAR_NUM
    }
    
    unsigned char byte1 = m_data.at(m_read++);
    unsigned char byte2 = m_data.at(m_read++);
    unsigned char byte3 = m_data.at(m_read++);
    unsigned char byte4 = m_data.at(m_read++);

    return (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
}