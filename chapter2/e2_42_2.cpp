#include "Sales_data.h"

int main() {
	Sales_data data1, data2;
	double price;

	std::cin >> data1.bookNo >> data1.units_sold >> price;
	data1.calRevenue(price);

	std::cin >> data2.bookNo >> data2.units_sold >> price;
	data2.calRevenue(price);

	data1.updateSales(data2);
	data1.printInfo();
	return 0;
}
