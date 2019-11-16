#pragma once
#include <sstream>
#include <vector>
#include <memory>

using namespace std;

enum class TokenType {
	DATE,
	EVENT,
	COLUMN,
	LOGICAL_OP,
	COMPARE_OP,
	PAREN_LEFT,
	PAREN_RIGHT,
};

struct Token {
	const string value;
	const TokenType type;
};
// разбивает условие на токены, с которыми проще работать, и создаем из них вектор
vector<Token> Tokenize(istream& cl);