#include <iostream>
#include <variant>

#ifndef CALC_HPP
#define CALC_HPP

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

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
	double operate(double dleft, double dright);
	double evaluate_side(Operand *op);

public:
	Operand* left;
	Operand* right;
	Operator binoperator;

	Operation(std::string expr);
	Operation(Operand left_, Operand right_, Operator binoperator_);
	Operation(Operand *left_, Operand *right_, Operator binoperator_);
	Operation(Operand &left_, Operand &right_, Operator binoperator_);
	Operation(Operation *op);

	~Operation();

	double evaluate();
};

std::ostream &operator<< (std::ostream &os, const Operation::Operator &op);
std::ostream &operator<< (std::ostream &os, const Operation::Operand &op);
std::ostream &operator<< (std::ostream &os, const Operation &op);

int main(int argc, const char** argv);

#endif
