#ifndef PACKET_H
#define PACKET_H

#include <string>
#include <vector>

class Packet {
public:
    Packet();
        
    void addInt(const int value, const bool identifier = true);
    void addString(const std::string &str);
    void addByte(const unsigned char byte);
    
    const std::vector<unsigned char>& data() const;
    void clean();
    
    unsigned char getHeader() const;
    std::string getString();
    unsigned int getInt(const bool identifier = true);
    
private:    
    std::vector<unsigned char> m_data;    
    unsigned int m_read;
};

#endif