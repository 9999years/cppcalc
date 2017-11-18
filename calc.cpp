#include <iostream>
#include <variant>

class Operation {
public:
	enum class Operator: char {
		add      = '+',
		subtract = '-',
		multiply = '*',
		divide   = '/',
	};
	typedef std::variant<double, Operation> Operand;
protected:
	double operate() {
		double dleft, dright;
		dleft = std::get<double>(*left);
		dleft = std::get<double>(*right);
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

	double evaluate_side(Operand* op) {
		// so what i WANT this to do is evaluate the operator, destroying
		// the Operation field and replacing it with a double in the
		// variant.  what it does is, im pretty sure, not that
		return std::holds_alternative<Operation>(*op)
			// op is an operation
			? std::get<Operation>(*op).evaluate()
			// op is a double
			: std::get<double>(*op);
	}

public:
	Operand* left;
	Operand* right;
	Operator binoperator;

	Operation(std::string expr) {
	}

	Operation(Operand left_, Operand right_, Operator binoperator_) {
		Operand left  = left_;
		Operand right = right_;
		binoperator   = binoperator_;
	}

	~Operation() {
		delete left;
		delete right;
	}

	double evaluate() {
		//left  = evaluate_side(left);
		//right = evaluate_side(right);
		return operate();
	}
};

int main(int argc, const char** argv) {
	//Operation op = new Operation(3, 4, Operation::Operator::multiply);
	//std::cout << "Evaluating 3 * 4: " << op.evaluate();
	return 0;
}
