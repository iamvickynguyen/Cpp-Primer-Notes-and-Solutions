#include <iostream>
using std::cout; using std::cin;

int increment() {
	static int i = 0;
	return i++;
}

int main() {
	for (int j = 0; j < 10; ++j) {
		cout << increment() << '\n';
	}
	return 0;
}
