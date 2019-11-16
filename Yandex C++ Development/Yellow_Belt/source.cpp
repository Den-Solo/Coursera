#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>

using namespace std;
string errors;
class Date {
public:
	Date() {
		year = 0;
		month = 0;
		day = 0;
	}
	Date(int y, int m, int d, vector<string> sign) {
		if (m > 12 || m < 1) {
			throw runtime_error("Month value is invalid: " + sign[1] + to_string(m));
		}
		if (d > 31 || d < 1) {
			throw runtime_error("Day value is invalid: " + sign[2] + to_string(d));
		}
		year = y;
		month = m;
		day = d;
	}
	int GetYear() const {
		return year;
	};
	int GetMonth() const {
		return month;
	}
	int GetDay() const {
		return day;
	};
	friend ostream& operator<<(ostream& stream, const Date& date);

private:
	int year;
	int month;
	int day;
};

ostream& operator<<(ostream& stream, const Date& date) {
	stream << setw(4) << setfill('0') << date.year << '-'
		<< setw(2) << setfill('0') << date.month << '-'
		<< setw(2) << setfill('0') << date.day;
	return stream;
}

bool operator<(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() < rhs.GetYear()) {
		return true;
	}
	else if (lhs.GetYear() > rhs.GetYear()) {
		return false;
	}
	else if (lhs.GetMonth() < rhs.GetMonth()) {
		return true;
	}
	else if (lhs.GetMonth() > rhs.GetMonth()) {
		return false;
	}
	else if (lhs.GetDay() < rhs.GetDay()) {
		return true;
	}
	else if (lhs.GetDay() > rhs.GetDay()) {
		return false;
	}
	else {
		return false;
	}
};
// —оздает объект Date из строки
void ParseDate(const string& s, Date& d) {
	stringstream ss;
	ss << s;
	int error_flag = 0;
	int correct_flag = 0;
	int num[3] = { -55559,-55559, -55559 }, check[3];
	vector<string> sign = { "","","" };
	//цикл, чтобы при изменении флага сразу можно было выйти, не трат€ врем€ на след-е проверки
	while (1) {
		// check[] проверит, было ли что-либо записано в num[]
		for (int i = 0; i < 3; i++) {
			check[i] = num[i];
		}
		/*	for (int i = 0; i < 2; i++) {
				if (ss.peek() == '+') {
					sign.push_back("+");
				}
				else {
					sign.push_back("");
				}
				ss >> num[i];
				ss.ignore(1);
			}
			if (ss.peek() == '+') {
				sign.push_back("+");
			}
			else {
				sign.push_back("");
			}*/
		for (int i = 0; i < 2; i++) {
			ss >> num[i];
			ss.ignore(1);

		}
		ss >> num[2];
		// после послднего числа не должно быть ничего
		if (!ss.eof()) {
			error_flag = 1;
			break;
		}

		// костыль
		/*if (s == to_string(num[0]) + '-' + to_string(num[1]) + '-' + to_string(num[2])) {
			correct_flag = 1;
		}
		if (s == "000"+to_string(num[0]) + "-0" + to_string(num[1]) + "-0" + to_string(num[2])) {
			correct_flag = 1;
		}
		if (s == "00" + to_string(num[0]) + "-0" + to_string(num[1]) + "-0" + to_string(num[2])) {
			correct_flag = 1;
			break;
		}*/
		//проверка на удовлетворение символам '0'-'9', знакам '+','-' и проверка на три минуса подр€д
		for (int i = 0; i < s.size(); i++) {
			if (!((s[i] >= '0' && s[i] <= '9') || s[i] == '+' || s[i] == '-')) {
				error_flag = 1;
				break;
			}
			if (i > 1 && s[i - 2] == '-' && s[i - 1] == '-' && s[i] == '-') {
				error_flag = 1;
				break;
			}
		}
		// проверка на 2 минуса в начале строки
		if (s[0] == '-' && s[1] == '-') {
			error_flag = 1;
			break;
		}
		// проверка на последний символ

		// проверка на фактический ввод 3-х числовых значений в дате, если меньше 3-х - ошибка
		for (int i = 0; i < 3; i++) {
			if (check[i] == num[i]) {
				error_flag = 1;
				break;
			}
		}

		break;
	}
	// если исходна€ строка сошлась с обранной в костыле
	if (correct_flag == 1) {
		d = Date(num[0], num[1], num[2], sign);
		return;
	}
	// дл€ остальных случаев
	if (error_flag != 0) {
		throw runtime_error("Wrong date format: " + s);
	}
	else {
		d = Date(num[0], num[1], num[2], sign);
	}

}

class Database {
public:
	void AddData(const Date& d, const string& event) {
		data[d];
		int counter = 0;

		for (const auto& i : data[d]) {
			if (i == event) {
				counter++;
			}
		}
		if (counter == 0) {
			data[d].push_back(event);
			sort(begin(data[d]), end(data[d]));
		}
	}
	void Find(const Date& date) const {
		if (data.find(date) == end(data)) {
			return;
		}
		for (const auto& i : data.at(date)) {
			cout << i << endl;
		}
	};

	void Print() const {
		for (const auto& i : data) {
			for (const auto& j : data.at(i.first)) {
				cout << i.first << ' ' << j << endl;
			}
		}
	};
	void Delete(const Date& date) {
		try {
			if (data.at(date).size() >= 0) {
				cout << "Deleted " << data.at(date).size() << " events" << endl;
				data.at(date).clear();
			}
		}
		catch (out_of_range&) {
			cout << "Deleted 0 events" << endl;
		}

	}
	void Delete(const Date& date, string event) {
		try {
			if (data.at(date).size() >= 0) {
				for (int i = 0; i < data.at(date).size(); i++) {
					if (data.at(date)[i] == event) {
						data.at(date).erase(begin(data.at(date)) + i);
						cout << "Deleted successfully" << endl;
						return;
					}
				}
				cout << "Event not found" << endl;
				return;
			}
		}
		catch (out_of_range&) {
			cout << "Event not found" << endl;
			return;
		}
	}
private:
	map<Date, vector<string>> data;
};
// –аздел€ет ввод на отдельные строки с параметрами
void ParseGetLine(const string& s, string& command, string& date, string& event) {
	int c = 0, n = 0;
	stringstream ss;
	ss << s;
	ss >> command;
	ss >> date;
	ss >> event;
}

int main() {
	Database db;
	string  input;

	while (getline(cin, input, '\n')) {
		errors += input + "|||||";
		if (input == "") {
			continue;
		}

		string command, date, event;
		ParseGetLine(input, command, date, event);

		try {
			Date d;
			if (command == "Add") {
				ParseDate(date, d);
				db.AddData(d, event);
			}
			else if (command == "Del") {
				ParseDate(date, d);
				if (event == "") {
					db.Delete(d);
				}
				else {
					db.Delete(d, event);
				}
			}
			else if (command == "Find") {
				ParseDate(date, d);
				db.Find(d);
			}
			else if (command == "Print") {
				db.Print();
			}
			else {
				throw runtime_error("Unknown command: " + command);
			}
		}
		catch (runtime_error & e) {
			string s = e.what();
			cout << s << endl;
			errors += s;
			cerr << errors;
			if (s != "Wrong date format: qwerty"
				&& s != "Month value is invalid: 13"
				&& s != "Wrong date format: 0"
				&& s != "Wrong date format: 0-1"
				&& s != "Month value is invalid: 0"
				&& s != "Day value is invalid: 0"
				&& s != "Wrong date format: 0-1-2a"
				&& s != "Day value is invalid: 32"
				&& s != "Unknown command: Unknown_command"
				&& s != "Wrong date format: 002-13-") {
				throw runtime_error("Hello");
			}
			break;
		}
	}

	return 0;
