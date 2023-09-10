#include <iostream>
#include <string>
#include <cstring>

int main() {
	std::string s1 = "hello there";
	std::string s2 = "hello here";	
	if (s1 == s2) std::cout << "equal\n";
	else if (s1 < s2) std::cout << "less\n";
	else std::cout << "greater\n";
	
	const char *c1 = "hello there!";
	const char *c2 = "hello here!";
	auto cmp = strcmp(c1, c2);
	if (cmp == 0) std::cout << "equal\n";
	else if (cmp < 0) std::cout << "less\n";
	else std::cout << "greater\n";
	
	return 0;
}
