#include <vector>
#include <string>
#include <cstring>

class A {
	std::vector<char> &x_v;
	void init() {
		x_v = *new std::vector<char>();
	}
public:
	void x(const char* x) {
		x_v = x;
	}
	A(const std::string x) {
		init();
		x(x.c_str());
	}

	~A() = default;
};

int main(int argc, char** argv) {
	A& a = *new A("foo");
	return 0;
}
