


#include "vns.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

vector <pair<string, unsigned int>> kalasKul;
vector<pair<string, unsigned int>>::iterator it;

void vns::insert(const HostName&, const IPAddress&){


//HÄMTA SKITEN FRÅN .TXT FILEN
    ifstream in;
    in.open("nameserverdata.txt")
    string name;
    unsigned int ip;

    if(!in) {
      std::cout << "Could not open file\n";
  }

    in >> name;
    in >> ip;


    pair<string, unsigned int> p;

    p.make_pair(name, ip);

    kalasKul.push_back(p);



}

bool vns::remove(const HostName&)
    pair<string, unsigned int> p;
    p.make_pair(HostName&, lookup(HostName&));

    kalasKul.erase(remove(kalasKul.begin(), kalasKul.end(), p), kalasKul.end());

    return !(find(kalasKul.begin(), kalasKul.end(), p) != kalaskul.end());



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
