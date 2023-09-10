#include <iostream>
#include <cstring>

int main() {
	const char *c1 = "hi ";
	const char *c2 = "world!";
	char *c3;
	strcpy(c3, c1);
	strcat(c3, c2);
	std::cout << c3 << '\n';
	return 0;
}
