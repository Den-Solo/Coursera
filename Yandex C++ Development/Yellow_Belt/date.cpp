#include "date.h"

Date ParseDate(istringstream& date_stream) {
	size_t a[3];

	for (auto i = 0; i < 3; i++) {
		date_stream >> a[i];
		date_stream.ignore(1);
	}
	return Date(a[0], a[1], a[2]);
}
Date ParseDate(istream& date_stream) {
	size_t a[3];

	for (auto i = 0; i < 3; i++) {
		date_stream >> a[i];
		date_stream.ignore(1);
	}
	return Date(a[0], a[1], a[2]);
}
ostream& operator<<(ostream& os, const Date& date) {
	os << setw(4) << setfill('0') << date.year_ << '-'
		<< setw(2) << setfill('0') << date.month_ << '-'
		<< setw(2) << setfill('0') << date.day_;
	return os;
}

bool operator<(const Date& lhs, const Date& rhs) {
	return vector<size_t>{lhs.year_, lhs.month_, lhs.day_} <
		vector<size_t>{rhs.year_, rhs.month_, rhs.day_};
}
bool operator<=(const Date& lhs, const Date& rhs) {
	return vector<size_t>{lhs.year_, lhs.month_, lhs.day_} <=
		vector<size_t>{rhs.year_, rhs.month_, rhs.day_};
}
bool operator>(const Date& lhs, const Date& rhs) {
	return vector<size_t>{lhs.year_, lhs.month_, lhs.day_} >
		vector<size_t>{rhs.year_, rhs.month_, rhs.day_};
}
bool operator>=(const Date& lhs, const Date& rhs) {
	return vector<size_t>{lhs.year_, lhs.month_, lhs.day_} >=
		vector<size_t>{rhs.year_, rhs.month_, rhs.day_};
}
bool operator==(const Date& lhs, const Date& rhs) {
	return vector<size_t>{lhs.year_, lhs.month_, lhs.day_} ==
		vector<size_t>{rhs.year_, rhs.month_, rhs.day_};
}
bool operator!=(const Date& lhs, const Date& rhs) {
	return vector<size_t>{lhs.year_, lhs.month_, lhs.day_} !=
		vector<size_t>{rhs.year_, rhs.month_, rhs.day_};
}