#include <vector>
#include <string>

#include "calc.hpp"

#ifndef PARSER_HPP
#define PARSER_HPP

class Parser {
public:
	enum class Precedence {
		parenthesis,
		exponents,
		multiplication,
		division,
		addition,
		subtraction,
		unknown
	};
protected:
	// left-most empty leaf on the tree
	Operation::Operand* active_leaf;
	Precedence head_precedence;
	Precedence precedence(char op);
	Operation::Operator binoperator(char tok);
	enum class TokenType {
		number,
		binoperator,
		space,
		invalid
	};
	TokenType type(char tok);
	std::vector<char> dat_v;
	void dat(const char* dat);
	void init();
public:
	// tree head
	Operation* head;
	char dat();

	void reset();
	Parser(std::string dat);
	Parser(char* dat);
	~Parser();
	Operation& extract();
};

std::ostream &operator<< (std::ostream &os, const Parser &parser);
#endif
