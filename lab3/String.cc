#include <iostream>
#include "date.h"
#include <sstream>

using namespace std;


    template<typename T>
    string toString(T& t) {

        ostringstream iss;
        iss << t;

        return iss.str();



}



template<typename T>
T string_cast(string s){
    return 0;




}







int main(){

    try {
        int i = string_cast<int>("123");
        double d = string_cast<double>("12.34");
        Date date = string_cast<Date>("2015-01-10");
}
    catch (std::invalid_argument& e) {
    cout << "Error: " << e.what() << endl;
}

    }

/*
            double d = 1.234;
            Date today;
            string sd = toString(d);
            string st = toString(today);
            cout << sd << "\n" << st << endl;


*/
            return 0;
        }
