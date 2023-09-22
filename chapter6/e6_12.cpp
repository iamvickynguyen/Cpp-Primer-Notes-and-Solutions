#include <iostream>

void myswap(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}

int main() {
	int x = 1, y = 2;
	myswap(x, y);
	std::cout << "x = " << x << ", y = " << y << '\n';
	return 0;
}
