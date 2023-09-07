#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::vector;

int main() {
	// array
	constexpr int N = 10;
	int arr1[N], arr2[N];
	for (int i = 0; i < N; ++i) arr1[i] = i;
	for (int i = 0; i < N; ++i) arr2[i] = arr1[i];

	// vector
	vector<int> vec1, vec2;
	for (int i = 0; i < N; ++i) vec1.push_back(i);
	vec2 = vec1;

	for (auto &d: vec2) cout << d << " ";
	cout << '\n';

	return 0;
}
