#include <iostream>
#include <stdexcept>

int main() {
	int a, b;
	while (std::cin >> a >> b) {
		try {
			if (b == 0) throw std::runtime_error("Division by 0");
			std::cout << (a / b) << '\n';
		} catch (const std::runtime_error &e) {
			std::cout << e.what() << "\nTry again? [y/n]" << '\n';
			char c;
			std::cin >> c;
			if (!std::cin || c == 'n') break;
		}
	}
	return 0;
}
