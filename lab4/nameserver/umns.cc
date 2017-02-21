#include "umns.h"

#include <algorithm>

using namespace std;

void UMNS::insert(const HostName &host, const IPAddress &ip){
    uomap[host] = ip;
}

bool UMNS::remove(const HostName &host) {
    auto position = uomap.find(host);

    if(position == uomap.end()) {
        return false;
    }

    uomap.erase(position);
    //returns true if not equal to the end == object does not exist
    return true;
}

IPAddress UMNS::lookup(const HostName &host) const {
    auto position = uomap.find(host);

    if(position != uomap.end()){
        return position->second;
    }else{
        return NON_EXISTING_ADDRESS;
    }
}
