#pragma once
#include "date.h"
#include <memory>


enum class Comparison {
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual,
};

enum class LogicalOperation {
	Or,
	And,
};

// ������� ����� ��� ������ ������� ���������� ������; ����� Evaluate ��������� ������� �� ��������������
// �������� ��������
class Node {
public:
	Node(const Comparison& cmp) : cmp_(cmp) {};
	virtual bool Evaluate(const Date& date, const string& event) const = 0;
protected:
	Comparison cmp_;
};

// ����� ��� ������������� �������; Evaluate ������ ���������� true
class EmptyNode : public Node {
public:
	EmptyNode() : Node(Comparison::Equal) {};
	bool Evaluate(const Date& date, const string& event) const override;
};

// ����� ��� �������� ����
class DateComparisonNode : public Node {
public:
	DateComparisonNode(const Comparison& cmp, const Date& date) : Node(cmp), date_(date) {};
	bool Evaluate(const Date& date, const string& event) const override;
private:
	Date date_;
};

// ����� ��� �������� �������
class EventComparisonNode : public Node {
public:
	EventComparisonNode(const Comparison& cmp, const string& event) : Node(cmp), event_(event) {};
	bool Evaluate(const Date& date, const string& event) const override;
private:
	string event_;
};

// ����� ��� ������� ���������� ������� � ������������ ����������� AND, OR
class LogicalOperationNode : public Node {
public:
	LogicalOperationNode(const LogicalOperation& lo, shared_ptr<Node> left, shared_ptr<Node> right) :
		Node(Comparison::Equal), lo_(lo), left_(left), right_(right) {};
	bool Evaluate(const Date& date, const string& event) const override;
private:
	LogicalOperation lo_;
	shared_ptr<Node> left_, right_;
};