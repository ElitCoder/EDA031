#include <iostream>
#include "date.h"
#include <sstream>

using namespace std;

template<typename T>
    string toString(T& t) {

        ostringstream oss;
        oss << t;

        return oss.str();
    }

template<typename T>
    T string_cast(string s){
        T temp;
        istringstream iss(s);

        iss >> temp;

        if(!iss) {
            throw invalid_argument("Not an acceptable input");
        }
        /*
        iss.exceptions(ios::failbit);
    try {
        iss >> temp;

    } catch(...){
        throw invalid_argument("Not an acceptable input");
    }*/



        return temp;

    }

int main(){
    try {
        int i = string_cast<int>("123");
        double d = string_cast<double>("12.34");
        Date date = string_cast<Date>("2015-01-10");
        cout << i << "\n" << d << "\n" << date << endl;

        i = string_cast<int>("a");
    }
    catch (invalid_argument& e) {
        cout << "Error: " << e.what() << endl;
    }

    double d = 1.234;
    Date today;
    string sd = toString(d);
    string st = toString(today);
    cout << sd << "\n" << st << endl;



    return 0;
}
