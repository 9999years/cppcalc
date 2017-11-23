#include <iostream>
#include <variant>
#include <tuple>

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

int main(int argc, const char** argv) {
	Operation &lhs = *new Operation(3, 40, Operation::Operator::multiply);
	Operation &rhs = *new Operation(6, 2, Operation::Operator::multiply);
	Operation &op = *new Operation(
		lhs,
		rhs,
		Operation::Operator::subtract);
	std::cout << "Operation: " << op << "\n";
	std::cout << "Evaluating: " << op.evaluate();
	//Operation *op = new Parser("3 * 4").extract();
	return 0;
}
