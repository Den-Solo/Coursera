#pragma once

#include <map>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>
#include <memory>

#include "date.h"


class Database {
public:
	// ��������� ������� ����-������� � ��
	void Add(const Date& d, const string& event);
	// ������� �������� ��, ��������������� ��������
	vector<pair<Date,string>> FindIf(function<bool (const Date & date, const string & event)>) const;
	// ������� ��� �������� �� � �����
	void Print(ostream& os) const;
	// ������� �������� �� �������
	int RemoveIf(function<bool(const Date & date, const string & event)>);
	// ������� ��������� ����������� ������� � � ������ ����
	pair<Date, string> Last(const Date& date) const;
	
private:
	// ���������� ������� ������ � ������� ����������
	map<Date,  vector<string>> data_vec;
	// ��� ���������� �������� ����������� �������/��������� ��������
	map<Date, set<string>> data_set;
};
ostream& operator<<(ostream& os, const pair<Date, string>&);
ostream& operator<<(ostream& os, const map< Date, vector<string>>&);

