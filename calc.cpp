#include <iostream>
#include <variant>
#include <tuple>
#include "calc.hpp"

std::ostream &operator<< (std::ostream &os, Operation::Operator const &op) {
	os << static_cast<char>(op);
	return os;
}

std::ostream &operator<< (std::ostream &os, Operation::Operand const &op) {
	if(op.valueless_by_exception()) {
		os << "[VALUELESS OPERATOR]";
	} else {
		std::visit(overloaded {
			[&](Operation::Operator &o) { os << o; },
			[&](double o)               { os << o; },
			[&](auto arg)               { }
		}, op);
	}
	return os;
}

std::ostream &operator<< (std::ostream &os, Operation const &op) {
	os << *op.left << ' ' << op.binoperator << ' ' << *op.right;
	return os;
}

double Operation::operate() {
	double dleft, dright;
	dleft = std::get<double>(*left);
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
	// so what i WANT this to do is evaluate the operator, destroying
	// the Operation field and replacing it with a double in the
	// variant.  what it does is, im pretty sure, not that
	return std::holds_alternative<Operation>(op)
		// op is an operation
		? std::get<Operation>(op).evaluate()
		// op is a double
		: std::get<double>(op);
}

Operation::Operation(std::string expr) {
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
	std::cout << "\n";
	std::cout << this << "\n";
	//std::cout << "left:  " << left << "\n";
	//std::cout << "right: " << right << "\n";
	*left  = evaluate_side(*left);
	*right = evaluate_side(*right);
	return operate();
}

int main(int argc, const char** argv) {
	Operation *op = new Operation(3, 4, Operation::Operator::multiply);
	//std::cout << "Operation: " << *op << "\n";
	std::cout << "left: " << *op->left << "\n";
	//std::cout << "Evaluating 3 * 4: " << op->evaluate();
	return 0;
}
