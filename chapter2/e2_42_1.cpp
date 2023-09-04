#include "Sales_data.h"

int main() {
	Sales_data data;
	double price;
	std::cin >> data.bookNo >> data.units_sold >> price;
	data.calRevenue(price);
	data.printInfo();
	return 0;
}
