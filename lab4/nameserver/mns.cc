#include "mns.h"

#include <map>
#include <algorithm>

using namespace std;

void MNS::insert(const HostName &host, const IPAddress &ip) {
    map[host] = ip;
}

bool MNS::remove(const HostName &host) {
    auto position = map.find(host);

    if(position == map.end()) {
        return false;
    }

    map.erase(position);
    //returns true if not equal to the end == object does not exist
    return true;
}

IPAddress MNS::lookup(const HostName &host) const {
    auto position = map.find(host);

    if(position != map.end()){
        return position->second;
    }else{
        return NON_EXISTING_ADDRESS;
    }
}
