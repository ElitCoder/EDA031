#ifndef PACKET_H
#define PACKET_H

#include <string>
#include <vector>

class Packet {
public:
    Packet();
    
    friend std::ostream& operator<<(std::ostream& out, const Packet &packet);
    
    void addInt(const int value, const bool identifier = true);
    void addString(const std::string &str);
    void addByte(const unsigned char byte);
    
    void addHeader(const unsigned char header);
    void addTail(const unsigned char tail);
    
    const std::vector<unsigned char>& data() const;
    void clean();
    void finish();
    
    unsigned char getHeader() const;
    std::string getString();
    unsigned int getInt(const bool identifier = true);
    
private:
    bool isEditable();
    
    std::vector<unsigned char> m_data;
    bool m_finalized;
    
    unsigned int m_read;
};

#endif