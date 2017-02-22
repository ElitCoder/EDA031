#include "hns.h"

#include <algorithm>
#include <functional>

using namespace std;

HNS::HNS(const unsigned int size) : hashTable(size, vector<pair<HostName, IPAddress>>()) {
}

void HNS::insert(const HostName &host, const IPAddress &ip) {
    auto hash = hashKey(host);

    hashTable.at(hash).push_back(make_pair(host, ip));
}

bool HNS::remove(const HostName &host) {
    auto hash = hashKey(host);
    vector<pair<HostName, IPAddress>> &table = hashTable.at(hash);

    auto position = find_if(table.begin(), table.end(), [&host](const pair<HostName, IPAddress> &x) { return x.first == host; });

    if(position == table.end()) {
        return false;
    }

    table.erase(position);

    return true;
}

IPAddress HNS::lookup(const HostName &host) const {
    auto hash = hashKey(host);
    const vector<pair<HostName, IPAddress>> &table = hashTable.at(hash);

    auto position = find_if(table.begin(), table.end(), [&host](const pair<HostName, IPAddress> &x) { return x.first == host; });

    if(position == table.end()) {
        return NON_EXISTING_ADDRESS;
    }

    return position->second;
}

unsigned int HNS::hashKey(const HostName &host) const {
    return hash<HostName>()(host) % hashTable.size();
}
