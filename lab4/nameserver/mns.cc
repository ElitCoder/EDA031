


#include "mns.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;





void MNS::insert(const HostName &host, const IPAddress &ip){





    pair<HostName, IPAddress> p;

    p.make_pair(host, ip);

    kalasKul.push_back(p);



}

bool MNS::remove(const HostName &host)
    return false;



}

IPAddress MNS::lookup(const HostName &host){

    return NON_EXISTING_ADDRESS;

}
