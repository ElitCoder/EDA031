#include "mns.h"
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;


map<string, unsigned int> map;

MNS::mns(){

}
void MNS::insert(const HostName &host, const IPAddress &ip){

    map[host] = ip;
}

bool MNS::remove(const HostName &host)

    map.erase(host);

    return !(map.find(host) != map.end());


}

IPAddress MNS::lookup(const HostName &host) const{
    IPAddress value;

    if(map.find(host) =! map.end()){
        value = map.at(host);
        return value;

    }else{
        return NON_EXISTING_ADDRESS;
    }


}
