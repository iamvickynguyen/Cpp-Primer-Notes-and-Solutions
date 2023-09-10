#include <iostream>
#include <vector>
#include <iterator>

using std::cout;
using std::cin;
using std::vector;
using std::begin;
using std::end;

int main() {
	// array
	int arr1[] = {1,2,3,4,5};
	int arr2[] = {1,2,4,5,5};
	int *s1 = begin(arr1), *e1 = end(arr1), *s2 = begin(arr2), *e2 = end(arr2);
	if ((e1 - s1) != (e2 - s2)) std::cout << "Diff\n";

	bool issame = true;
	for (int *p1 = s1, *p2 = s2; p1 != e1 && p2 != e2; ++p1, ++p2) {
		if (*p1 != *p2) {
			issame = false;
			std::cout << "Diff\n";
			break;
		}
	}

	if (issame) std::cout << "Same\n";

	// vector
	vector<int> vec1 = {1,2,3,4,5};
	vector<int> vec2 = {1,2,4,5,5};
	std::cout << ((vec1 == vec2) ? "Same" : "Diff") << '\n';

	return 0;
}
