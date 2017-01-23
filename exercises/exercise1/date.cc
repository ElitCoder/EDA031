/*
 * Class Date, implementation.
 * The next() function in this implementation cannot handle leap years.
 */

#include "date.h"

#include <ctime>   /* for C routines time and localtime */
#include <iostream>
#include <utility> /* for swap */

using namespace std;

int Date::daysPerMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

Date::Date() {
	time_t timer = time(0); // time in seconds since 1970-01-01
	tm* locTime = localtime(&timer); // broken-down time
	year = 1900 + locTime->tm_year;
	month = 1 + locTime->tm_mon;
	day = locTime->tm_mday;
}

Date::Date(int y, int m, int d) {}

int Date::get_year() const {
	return 0;
}

int Date::get_month() const {
	return 0;
}

int Date::get_day() const {
	return 0;
}

void Date::next() {
}

void print(const Date& d) {
	cout << d.get_year() << "-";
	if (d.get_month() < 10) {
		cout << "0";
	}
	cout << d.get_month() << "-";
	if (d.get_day() < 10) {
		cout << "0";
	}
	cout << d.get_day();
}

bool operator<(const Date& d1, const Date& d2) {
	return (d1.get_year() < d2.get_year()) ||
	(d1.get_year() == d2.get_year() && d1.get_month() < d2.get_month()) ||
	(d1.get_year() == d2.get_year() && d1.get_month() == d2.get_month()
	 && d1.get_day() < d2.get_day());
}

int distance(const Date& d1, const Date& d2) {
	return 0;
}
