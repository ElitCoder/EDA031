


#include "vns.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

vector <Pair::pair(string, unsigned int)> kalasKul;
vector<Pair::pair(string, unsigned int)>::iterator it;

void vns::insert(const HostName&, const IPAddress&){

    pair<string, unsigned int> p;

    p.make_pair(HostName&, IPAddress&);

    kalasKul.push_back(p);



}

bool vns::remove(const HostName&)
    pair<string, unsigned int> p;
    p.make_pair(HostName&, lookup(HostName&));

    kalasKul.erase(remove(kalasKul.begin(), kalasKul.end(), p), kalasKul.end());

    if(find(kalasKul.begin(), kalasKul.end(), p) != kalaskul.end() == string.npos){
        return true;
    }else{
        return false;
    }



}

IPAddress vns::lookup(const HostName&){

    int index;

    if(find_if(kalasKul.begin(), kalasKul.end(), lambda) != kalasKul.end()) {
        //the HostName exists in the vector
        index = find((kalasKul.begin(), kalasKul.end(), HostName&) - kalasKul.begin();



        return kalasKul.at(index).second;

    }

    else {
        return NON_EXISTING_ADDRESS;
    }

}
