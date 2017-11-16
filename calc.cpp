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
		if(std::holds_alternative<double>(left)) {
		}
	}
};

int main(int argc, const char** argv) {
}
