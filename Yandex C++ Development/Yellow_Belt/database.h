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
	// доюавляет элемент дата-событие в БД
	void Add(const Date& d, const string& event);
	// находит элементы БД, удовлетворяющие условиям
	vector<pair<Date,string>> FindIf(function<bool (const Date & date, const string & event)>) const;
	// выводит все элементы БД в поток
	void Print(ostream& os) const;
	// удаляет элементы по условию
	int RemoveIf(function<bool(const Date & date, const string & event)>);
	// выводит последнее добавленное событие в к данной дате
	pair<Date, string> Last(const Date& date) const;
	
private:
	// необходимо хранить записи в порядке добавления
	map<Date,  vector<string>> data_vec;
	// для увеличения скорости определения наличия/отсуствия элемента
	map<Date, set<string>> data_set;
};
ostream& operator<<(ostream& os, const pair<Date, string>&);
ostream& operator<<(ostream& os, const map< Date, vector<string>>&);

