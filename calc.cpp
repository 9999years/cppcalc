#include <iostream>
#include <variant>
#include <tuple>
#include "calc.hpp"

std::ostream &operator<< (std::ostream &os, Operation::Operator const &op) {
	os << static_cast<char>(op);
	return os;
}

std::ostream &operator<< (std::ostream &os, Operation::Operand const &op) {
	std::visit(std::make_tuple(
		[&](Operation::Operator *op) { os << *op; },
		[&](double op)               { os << op; },
		[&](auto arg)                { os << "UH OH!!!!"; }
	), op);
	//if(std::holds_alternative<Operation>(op)) {
		//// operation, we recurse
		//os << std::get<Operation>(op);
	//} else if(std::holds_alternative<double>(op)){
		//// double
		//os << std::get<double>(op);
	//}
	return os;
}

std::ostream &operator<< (std::ostream &os, Operation const &op) {
	os << *op.left << ' ' << op.binoperator << ' ' << *op.right;
	return os;
}

std::string type(Operation::Operand o) {
	return std::holds_alternative<Operation>(o)
		// op is an operation
		? "operation"
		// op is a double
		: "double";
}

double Operation::operate() {
	double dleft, dright;
	dleft = std::get<double>(*left);
	dleft = std::get<double>(*right);
	std::cout << "left:  " << dleft << "\n";
	std::cout << "right: " << dright << "\n";
	switch(binoperator) {
	case(Operator::add):
		return dleft + dright;
	case(Operator::subtract):
		return dleft - dright;
	case(Operator::multiply):
		return dleft * dright;
	case(Operator::divide):
		return dleft / dright;
	}
}

double Operation::evaluate_side(Operand op) {
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
	left  = &left_;
	right = &right_;
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
	left  = new Operand(evaluate_side(*left));
	right = new Operand(evaluate_side(*right));
	return operate();
}

int main(int argc, const char** argv) {
	Operation *op = new Operation(3, 4, Operation::Operator::multiply);
	std::cout << "Operation: " << *op << "\n";
	std::cout << "left: " << op->left << "\n";
	//std::cout << "Evaluating 3 * 4: " << op->evaluate();
	return 0;
}
