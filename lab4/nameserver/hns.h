#ifndef HNS_H
#define HNS_H

#include "nameserverinterface.h"

#include <vector>

class HNS : public NameServerInterface {
public:
    HNS(const unsigned int size);

    void insert(const HostName&, const IPAddress&);
    bool remove(const HostName&);
    IPAddress lookup(const HostName&) const;

private:
    unsigned int hashKey(const HostName &host) const;

    std::vector<std::vector<std::pair<HostName, IPAddress>>> hashTable;
};

#endif
