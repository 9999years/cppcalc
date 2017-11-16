#include <iostream>
#include <variant>

enum class Operator: char {
	add      = '+',
	subtract = '-',
	multiply = '×',
	divide   = '⁄',
};

variant<double, Operation> Operand;

class Operation {
	double operate() {
		switch(binoperator):
		case(Operator::add):
			return left + right;
		case(Operator::subtract):
			return left - right;
		case(Operator::multiply):
			return left * right;
		case(Operator::divide):
			return left / right;
	}

	double evaluate_side(Operand op) {
		if(std::holds_alternative<Operation>(op)) {
			// so what i WANT this to do is evaluate the lhs,
			// destroying the Operation field and replacing it with
			// a double in the variant
			// what it does is, im pretty sure, not that
			return op.evaluate();
		} else {
			// double
			return op;
		}
	}

public:
	Operand left;
	Operand right;
	Operator binoperator;

	M(std::string expr) {
	}

	M(Operand lhs, Operand rhs) {
		left = lhs;
		right = rhs;
	}

	double evaluate() {
		left = evaluate_side(left);
		right = evaluate_side(left);
		return operate();
	}
};

int main(int argc, const char** argv) {
}
