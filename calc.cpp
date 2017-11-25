#include <iostream>
#include <variant>
#include <tuple>
#include <cstring>

#include "calc.hpp"
#include "parser.hpp"

std::ostream &operator<< (std::ostream &os, Operation::Operator const &op) {
	return os << static_cast<char>(op);
}

std::ostream &operator<< (std::ostream &os, Operation const &op) {
	// (lhs op rhs)
	return os
		<< '('
		<< *(op.left)
		<< ' '
		<< op.binoperator
		<< ' '
		<< *(op.right)
		<< ')';
}

std::ostream &operator<< (std::ostream &os, Operation::Operand const &op) {
	if(op.valueless_by_exception()) {
		return os << "[VALUELESS OPERATOR]";
	}

	std::visit(overloaded {
		[&](Operation o) { os << o; },
		[&](double o)    { os << o; },
		[&](auto arg)    { os << "[VALUELESS]"; },
	}, op);
	return os;
}

double Operation::operate(double dleft, double dright) {
	switch(binoperator) {
	case(Operator::add):
		return dleft + dright;
	case(Operator::subtract):
		return dleft - dright;
	case(Operator::multiply):
		return dleft * dright;
	case(Operator::divide):
		return dleft / dright;
	default:
		return 0;
	}
}

double Operation::evaluate_side(Operand *op) {
	// evaluates the operator, returning the result
	return std::visit(overloaded {
		[](Operation o) { return o.evaluate(); },
		[](double o)    { return o; },
	}, *op);
}

double Operation::evaluate() {
	return operate(evaluate_side(left), evaluate_side(right));
}

Operation::Operation(Operand &left_, Operand &right_, Operator binoperator_) {
	left  = new Operand(left_);
	right = new Operand(right_);
	binoperator = binoperator_;
}

Operation::Operation(Operand left_, Operand right_, Operator binoperator_) {
	left  = new Operand(left_);
	right = new Operand(right_);
	binoperator = binoperator_;
}

Operation::~Operation() = default;

std::string join(int argc, const char** argv) {
	// require 2 args, start at 1 in iteration to avoid program name in
	// output string
	if(argc < 2) {
		return "";
	}

	std::string &ret = *new std::string();
	// n elements of the same length + a space for each is probably a
	// decent estimate of the space we'll need
	ret.reserve(argc * (std::strlen(argv[1]) + 1));
	for(int i = 1; i < argc; i++) {
		ret += argv[i];
		ret += ' ';
	}
	ret.pop_back();
	return ret;
}

int main(int argc, const char** argv) {
	//Operation &lhs = *new Operation(3, 40, Operation::Operator::multiply);
	// 3 * 40 - 6 * 2
	// equiv. to
	/*     -
	 *    / \
	 *   *   *
	 *  /|   |\
	 * 3 40  6 2
	 * when properly parsed, as opposed to
	 *       *
	 *      / \
	 *     -   2
	 *    / \
	 *   *   6
	 *  / \
	 * 3  40
	 * when parsed left-to-right
	 */
	Parser &parser = *new Parser(join(argc, argv));
	//std::cout << "Parser: " << parser << "\n";
	//std::cout << "(Parsing)\n";
	//Operation &expr = parser.extract();
	//std::cout << "Parsed expression: " << expr;
	return 0;
}
