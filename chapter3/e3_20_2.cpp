#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::vector;

int main() {
	int x;
	vector<int> vec;
	while (cin >> x) vec.push_back(x);

	// if odd size, middle item will be added to itself
	for (auto i = 0; i < (vec.size() + 1) / 2; ++i) cout << (vec[i] + vec[vec.size() - i - 1]) << '\n';
	return 0;
}
