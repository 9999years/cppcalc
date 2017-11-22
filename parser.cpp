#include <vector>

#include "calc.hpp"
#include "parser.hpp"

TokenType Parser::type(Token tok) {
	switch(tok) {
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case '0':
		case '.':
			return TokenType::number;
		case '*':
		case '/':
		case '+':
		case '-':
			return TokenType::binoperator;
		case ' ':
		case '\t':
		case '\r':
		case '\n':
		case '\xa0':
			return TokenType::space;
		default:
			return TokenType::invalid;
	}
}

Parser::precedence(Token op) {
	switch(op) {
		case '*':
			return Parser::Precedence::multiplication;
		case '/':
			return Parser::Precedence::division;
		case '+':
			return Parser::Precedence::addition;
		case '-':
			return Parser::Precedence::subtraction;
		default:
			return Parser::Precedence::unknown;
	}
}

Parser::binoperator(Token op) {
	switch(op) {
		case '*':
			return Operation::Operator::multiply;
		case '/':
			return Operation::Operator::divide;
		case '+':
			return Operation::Operator::add;
		case '-':
			return Operation::Operator::subtract;
		default:
			return Operation::Operator::unknown;
	}
}

Parser::parse_tok(Token tok) {
	switch(type(tok)) {
		case TokenType::Number:
			break;
		case TokenType::Operator:
			Precedence tok_prec = precedence(tok);
			if(tok_prec > head_precedence) {
				// put tok down in active leaf
				active_leaf = new Operation();
				active_leaf.binoperator = 
			}
			break;
		case TokenType::Space:
			break;
		case TokenType::Invalid:
		default:
			break;
	}
}

Parser::Parser(Token[] dat_) {
	dat = dat_;
}

Parser::~Parser() {
	delete active_leaf;
	delete head;
}

Operation Parser::extract() {
	for(Token tok : dat) {
		std::vector<Token> unit = new std::vector<>();
		switch(type(tok)):
			case TokenType::number:
				unit.push_back(tok);
				continue;
			case TokenType::binoperator:
				continue;
			case TokenType::space:
				continue;
			case TokenType::invalid:
			default:
				throw std::invalid_argument(
					"Syntax error: Invalid character `"
					+ tok + "`!"
				);
	}
}
