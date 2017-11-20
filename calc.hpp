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
	double operate();
	double evaluate_side(Operand& op);

public:
	Operand* left;
	Operand* right;
	Operator binoperator;

	Operation(std::string expr);
	Operation(Operand left_, Operand right_, Operator binoperator_);

	~Operation();

	double evaluate();
};

std::ostream &operator<< (std::ostream &os, Operation::Operator const &op);
std::ostream &operator<< (std::ostream &os, Operation::Operand const &op);
std::ostream &operator<< (std::ostream &os, Operation const &op);

int main(int argc, const char** argv);

#endif
