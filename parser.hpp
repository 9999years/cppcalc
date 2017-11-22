#include <vector>

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
	typedef char Token;
	Precedence precedence(Token op);
	Operation::Operator binoperator(Token tok);
	enum class TokenType {
		number,
		binoperator,
		space,
		invalid
	};
	TokenType type(Token tok);
	std::vector<Token> dat;
public:
	// tree head
	Operation* head;

	void reset();
	void set(std::string);
	Parser(std::string);
	~Parser();
	Operation extract();
};

#endif
