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
protected:
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
		// so what i WANT this to do is evaluate the operator, destroying
		// the Operation field and replacing it with a double in the
		// variant.  what it does is, im pretty sure, not that
		return std::holds_alternative<Operation>(op)
			// op is an operation
			? op.evaluate()
			// op is a double
			: op;
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

	~M() {
		delete left;
		delete right;
		delete binoperator;
	}

	double evaluate() {
		left = evaluate_side(left);
		right = evaluate_side(left);
		return operate();
	}
};

int main(int argc, const char** argv) {
}
