#include "packet.h"
#include "protocol.h"

#include <iostream>

using namespace std;

Packet::Packet() : m_finalized(false), m_read(1) {
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
        
        return -1;
    }
    
    return m_data.at(0);
}

string Packet::getString() {
    unsigned int size = m_data.at(++m_read);
    string str;
    
    for(unsigned int current = m_read; current != size + m_read; ++current) {
        str += m_data.at(++m_read);
    }
    
    return str;
}

unsigned int Packet::getInt() {
    cout << "ERROR: NOT IMPLEMENTED.\n";
}