#include "vns.h"

#include <vector>
#include <algorithm>

using namespace std;

void VNS::insert(const HostName &host, const IPAddress &ip) {
    kalasKul.push_back(make_pair(host, ip));
}

bool VNS::remove(const HostName &host) {
    auto position = find_if(kalasKul.begin(), kalasKul.end(), [host](const pair<HostName, IPAddress> &x) { return x.first == host; });

    if(position == kalasKul.end()) {
        return false;
    }

    kalasKul.erase(position);

    return true;
}

IPAddress VNS::lookup(const HostName &host) const {
    auto position = find_if(kalasKul.begin(), kalasKul.end(), [host](const pair<HostName, IPAddress> &x) { return x.first == host; });

    if(position != kalasKul.end()) {
        //the HostName exists in the vector
        return position->second;
    }

    else {
        return NON_EXISTING_ADDRESS;
    }
}
