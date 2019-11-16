#include "database.h"


void Database::Add(const Date& d, const string& event) {
	if ((data_set.count(d) != 0 && data_set.at(d).count(event) == 0) || data_set.count(d) == 0) {
		data_set[d].insert(event);
		data_vec[d].push_back(event);
	}
	else {
		return;
	}
}
vector<pair<Date, string>> Database::FindIf(function<bool(const Date & date, const string & event)> predicate) const {
	vector<pair<Date, string>> v;
	for (const auto& map_item : data_vec) {
		for (const auto& vec_item : map_item.second) {
			if (predicate(map_item.first, vec_item)) {
				v.push_back(make_pair(map_item.first, vec_item));
			}
		}
	}
	return v;
}

void Database::Print(ostream& os) const {
	os << data_vec;
}
int Database::RemoveIf(function<bool(const Date & date, const string & event)> predicate) {
	int count = 0;
	vector<Date> map_items_to_erase;
	for (auto& map_item : data_vec) {
		auto iter = stable_partition(map_item.second.begin(), map_item.second.end(), 
			[&](const string& s) {return !predicate(map_item.first, s); });
		count += map_item.second.end() - iter;
		// очистка set и vector, если удалить надо целиком
		if (iter == map_item.second.begin()) {
			data_set.erase(map_item.first);
			map_items_to_erase.push_back(map_item.first);
			continue;
		}
		// очистка set и vector, если удалить надо не все элемнты
		for (auto it_vec = iter; it_vec != map_item.second.end(); it_vec++) {
			auto it_set = data_set[map_item.first].find(*it_vec);
			if (it_set != data_set[map_item.first].end()) {
				data_set[map_item.first].erase(it_set);
			}
		}
		data_vec[map_item.first].erase(iter, map_item.second.end());
	}
	for (const auto& i : map_items_to_erase) {
		data_vec.erase(i);
	}
	return count;
}

pair<Date, string> Database::Last(const Date& date) const {
	auto it = data_vec.upper_bound(date);
	if (it != begin(data_vec)) {
		return make_pair(prev(it)->first, prev(it)->second.back());
	}
	else {
		throw invalid_argument("LastFunc");
	}
}

ostream& operator<<(ostream& os,const pair<Date, string>& p) {
	os << p.first << ' ' << p.second;
	return os;
}
ostream& operator<<(ostream& os, const map< Date, vector<string>>& m) {
	for (const auto& item : m) {
		for (const auto& j : item.second) {
			os << item.first << ' ' << j << endl;
		}
	}
	return os;
}

