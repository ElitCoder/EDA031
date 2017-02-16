#ifndef VNS_H
#define VNS_H

#include <iostream>

const HostName&
const IPAddress&

/* Implement a class VNS (vector name server) that uses an unsorted vector to store the
name/address pairs. Use the find if algorithm to search for a host name. The third
parameter to the algorithm should be a lambda.
*/
Class vns : public NameServerInterface {

public:
    vns(){}
    void insert(const HostName&, const IPAddress&);
    bool remove(const HostName&);
    IPAddress lookup(const HostName&);

}

#endif
