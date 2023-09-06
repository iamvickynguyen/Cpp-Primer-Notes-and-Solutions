#include <iostream>
#include <string>
#include <vector>

int main() {
	std::string word;
	std::vector<std::string> words;
	while (std::cin >> word) words.push_back(word);
	
	for (auto &s: words) {
		for (auto &c: s) toupper(c);
	}

	for (std::string::size_type i = 0; i < words.size(); i += 8) {
		for (auto j = i; j < std::min(i + 8, (std::string::size_type)words.size()); ++j)
			std::cout << words[j] << " ";
		std::cout << '\n';
	}
	return 0;
}
