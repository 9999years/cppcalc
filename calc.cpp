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
	os
		<< '('
		<< *op.left
		<< ' '
		<< op.binoperator
		<< ' '
		<< *op.right
		<< ')';
	return os;
}

std::ostream &operator<< (std::ostream &os, Operation::Operand const &op) {
	if(op.valueless_by_exception()) {
		os << "[VALUELESS OPERATOR]";
	} else {
		std::visit(overloaded {
			[&](Operation o) { os << o; },
			[&](double o)    { os << o; },
			[&](auto o)      { },
		}, op);
	}
	return os;
}

double Operation::operate() {
	double dleft, dright;
	*left  = evaluate_side(*left);
	*right = evaluate_side(*right);
	dleft  = std::get<double>(*left);
	dright = std::get<double>(*right);
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

double Operation::evaluate_side(Operand &op) {
	// evaluates the operator, returning the result
	return std::holds_alternative<Operation>(op)
		// op is an operation
		? std::get<Operation>(op).evaluate()
		// op is a double
		: std::get<double>(op);
}

Operation::Operation(Operand &left_, Operand &right_, Operator binoperator_) {
	left  = new Operand(left_);
	right = new Operand(right_);
	binoperator = binoperator_;
}

Operation::Operation(Operand *left_, Operand *right_, Operator binoperator_) {
	left  = new Operand(*left_);
	right = new Operand(*right_);
	binoperator = binoperator_;
}

Operation::Operation(Operation *op) {
	left  = new Operand(*op->left);
	right = new Operand(*op->right);
	binoperator = op->binoperator;
}

Operation::Operation(Operand left_, Operand right_, Operator binoperator_) {
	left  = new Operand(left_);
	right = new Operand(right_);
	binoperator = binoperator_;
}

Operation::~Operation() {
	delete left;
	delete right;
}

double Operation::evaluate() {
	return operate();
}

int main(int argc, const char** argv) {
	Operation *lhs = new Operation(3, 4, Operation::Operator::multiply);
	Operation *rhs = new Operation(6, 2, Operation::Operator::multiply);
	Operation *op = new Operation(lhs, rhs, Operation::Operator::subtract);
	//Operation *op = new Operation(6, 8, Operation::Operator::subtract);
	std::cout << "lhs: " << *lhs << "\n";
	// segfaults AFTER printing this
	std::cout << "lhs: " << *op->left << "\n";
	std::cout << "rhs: " << *rhs << "\n";
	std::cout << "rhs: " << *op->right << "\n";
	std::cout << "Operation: " << *op << "\n";
	//std::cout << "Evaluating: " << op->evaluate();
	//Operation *op = new Parser("3 * 4").extract();
	return 0;
}
