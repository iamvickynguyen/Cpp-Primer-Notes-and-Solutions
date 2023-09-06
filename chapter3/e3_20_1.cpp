#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::vector;

int main() {
	int x;
	vector<int> vec;
	while (cin >> x) vec.push_back(x);

	for (auto i = 0; i < vec.size() - 1; ++i) cout << (vec[i] + vec[i+1]) << '\n';
	return 0;
}
