#include "hns.h"
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;


map<string, unsigned int> map;

HNS::hns(){

}
void HNS::insert(const HostName &host, const IPAddress &ip){

    map[host] = ip;
}

bool HNS::remove(const HostName &host)

    return true;


}

IPAddress HNS::lookup(const HostName &host) const{

        return NON_EXISTING_ADDRESS;
    


}
