#include "calc.hpp"

#ifndef PARSER_HPP
#define PARSER_HPP

class Parser {
protected:
	// left-most empty leaf on the tree
	Operation::Operand* active_leaf;
	Precedence head_precedence;
	typedef char Token;
	Token[] dat;
	Precedence precedence(Token op);
	Operation::Operator binoperator(Precedence prec);
	enum TokenType {
		number,
		binoperator,
		space,
		invalid
	};
	TokenType type(Token tok);
public:
	enum Precedence {
		parenthesis,
		exponents,
		multiplication,
		division,
		addition,
		subtraction,
		unknown
	};
	// tree head
	Operation* head;

	void reset();
	void set(std::string);
	Parser(std::string);
	~Parser();
	Operation extract();
}

#endif
