#pragma once
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <memory>


using namespace std;

class Date {
public:
	Date(size_t y, size_t m, size_t d) : year_(y), month_(m), day_(d) {};
	friend ostream& operator<<(ostream& os, const Date& date);
	friend bool operator<(const Date& lhs, const Date& rhs);
	friend bool operator<=(const Date& lhs, const Date& rhs);
	friend bool operator>(const Date& lhs, const Date& rhs);
	friend bool operator>=(const Date& lhs, const Date& rhs);
	friend bool operator==(const Date& lhs, const Date& rhs);
	friend bool operator!=(const Date& lhs, const Date& rhs);
private:
	size_t year_;
	size_t month_;
	size_t day_;
};

Date ParseDate(istringstream&);
Date ParseDate(istream&);
ostream& operator<<(ostream& os, const Date& date);
bool operator<(const Date& lhs, const Date& rhs);
