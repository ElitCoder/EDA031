#include <ctime>  // time and localtime
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>

#include "date.h"

using namespace std;

int Date::daysPerMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

Date::Date() {
	time_t timer = time(0); // time in seconds since 1970-01-01
	tm* locTime = localtime(&timer); // broken-down time
	year = 1900 + locTime->tm_year;
	month = 1 + locTime->tm_mon;
	day = locTime->tm_mday;
}

Date::Date(int y, int m, int d): year(y), month(m), day(d) {

}

int Date::getYear() const {
	return year;
}

int Date::getMonth() const {
	return month;
}

int Date::getDay() const {
	return day;
}


void Date::next() {
	if (day != daysPerMonth[month-1]){
		day++;
	}else{
		if(month != 12){
			month++;
		}else{
			month = 1;
			year++;
		}

		day = 1;
	}
}

ostream& operator<<(ostream& out, const Date &d) {
	cout << setw(4) << setfill('0') << d.getYear() << '-';
	cout << setw(2) << setfill('0') << d.getMonth() << '-';
	cout << setw(2) << setfill('0') << d.getDay();
	
	return out;
}

istream& operator>>(istream &in, Date &date) {
	string input;
	getline(in, input);
	
	replace(input.begin(), input.end(), '-', ' ');
	istringstream stream(input);
	
	stream >> date.year;
	stream >> date.month;
	stream >> date.day;
	
	if(date.month <= 0 || date.month > 12 || date.day <= 0 || date.day > Date::daysPerMonth[date.month - 1]) {
		in.setstate(ios_base::failbit);
	}
	
	return in;
}