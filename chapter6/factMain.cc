#include "Chapter6.h"
#include <iostream>

// run: g++ fact.cc factMain.cc
int main() {
	int j = fact(5); // j equals 120, i.e., the result of fact(5)
	std::cout << "5! is " << j << std::endl;
	return 0;
}
