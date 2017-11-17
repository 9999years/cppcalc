#include <iostream>
// using matt park's implementation, which should land in the clang mainstream
// at some point. v1.2.2 if it matters
// https://github.com/mpark/variant/releases
#include <variant.h>

class Operation {
protected:
	double operate() {
		switch(binoperator) {
		case(Operator::add):
			return left + right;
		case(Operator::subtract):
			return left - right;
		case(Operator::multiply):
			return left * right;
		case(Operator::divide):
			return left / right;
		}
	}

	double evaluate_side(Operand op) {
		// so what i WANT this to do is evaluate the operator, destroying
		// the Operation field and replacing it with a double in the
		// variant.  what it does is, im pretty sure, not that
		return mpark::holds_alternative<Operation>(op)
			// op is an operation
			? op.evaluate()
			// op is a double
			: op;
	}
public:
	enum class Operator: char {
		add      = '+',
		subtract = '-',
		multiply = '×',
		divide   = '/',
	};
	typedef mpark::variant<double, Operation> Operand;
	Operand left;
	Operand right;
	Operator binoperator;

	Operation(std::string expr) {
	}

	Operation(Operand lhs, Operand rhs) {
		left = lhs;
		right = rhs;
	}

	~Operation() {
		delete left;
		delete right;
	}

	double evaluate() {
		left = evaluate_side(left);
		right = evaluate_side(left);
		return operate();
	}
};

int main(int argc, const char** argv) {
}
