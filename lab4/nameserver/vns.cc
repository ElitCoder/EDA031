#include "vns.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

vector <pair<string, unsigned int>> kalasKul;


VNS::vns(){

}

void VNS::insert(const HostName &host, const IPAddress &ip){





    pair<HostName, IPAddress> p;

    p.make_pair(host, ip);

    kalasKul.push_back(p);



}

bool VNS::remove(const HostName &host)
    pair<string, unsigned int> p;
    p.make_pair(host, lookup(host));

    kalasKul.erase(remove(kalasKul.begin(), kalasKul.end(), p), kalasKul.end());

    return !(find(kalasKul.begin(), kalasKul.end(), p) != kalaskul.end());



}

IPAddress VNS::lookup(const HostName &host) const{

    int index;

    if(find_if(kalasKul.begin(), kalasKul.end(), lambda) != kalasKul.end()) {
        //the HostName exists in the vector
        index = find((kalasKul.begin(), kalasKul.end(), host) - kalasKul.begin();



        return kalasKul.at(index).second;

    }

    else {
        return NON_EXISTING_ADDRESS;
    }

}
