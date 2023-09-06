#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::vector;

int main () {
	vector<int> vec;
	for (int i = 1; i < 10; ++i) vec.push_back(i);
	for (auto it = vec.begin(); it != vec.end(); ++it) *it *= 2;
	for (auto &d: vec) cout << d << " ";
	cout << '\n';
	return 0;
}
