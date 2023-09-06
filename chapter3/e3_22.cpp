#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::string;
using std::endl;

int main () {
	string text;
	getline(cin, text);
	
	for (auto it = text.begin(); it != text.end(); ++it {
		if (isalpha(*it)) *it = toupper(*it); 
	}

	cout << text << endl;
	return 0;
}
