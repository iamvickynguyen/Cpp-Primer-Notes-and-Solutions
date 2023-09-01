#include <iostream>
#include <typeinfo>
#include <boost/core/demangle.hpp>

int main() {
	const int i = 42;
	auto j = i; const auto &k = i; auto *p = &i;
	const auto j2 = i, &k2 = i;

	std::cout << "j is " << boost::core::demangle(typeid(j).name()) << '\n'
		<< "k is " << boost::core::demangle(typeid(k).name()) << '\n'
		<< "p is " << boost::core::demangle(typeid(p).name()) << '\n'
		<< "j2 is " << boost::core::demangle(typeid(j2).name()) << '\n'
		<< "k2 is " << boost::core::demangle(typeid(k2).name()) << '\n';
	return 0;
}
