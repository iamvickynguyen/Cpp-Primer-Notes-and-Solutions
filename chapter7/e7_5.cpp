#ifndef PERSONH
#define PERSONH

#include <string>

class Person {
public:
	const std::string& get_name() const { return name; }		
	const std::string& get_address() const { return address; }
	
private:
	std::string name;
	std::string address;
};

#endif
