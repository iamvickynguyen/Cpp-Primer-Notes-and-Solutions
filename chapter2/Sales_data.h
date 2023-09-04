#ifndef SALES_DATA_H
#define SALES_DATA_H
#include <string>
#include <iostream>

struct Sales_data {
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;

	void calRevenue(const double price);
	double avgPrice();
	void printInfo();
	void updateSales(const Sales_data &data);
};

void Sales_data::calRevenue(const double price) {
	revenue = units_sold * price;
}

double Sales_data::avgPrice() {
	if (units_sold > 0) return revenue / units_sold;
	return 0.0;
}

void Sales_data::printInfo() {
	std::cout << "bookNo: " << bookNo << "\nunits sold: " << units_sold << "\nrevenue: " << revenue << '\n';
	if (units_sold > 0) std::cout << "average price: " << avgPrice() << '\n';
	else std::cout << "no sales\n";
}

void Sales_data::updateSales(const Sales_data &data) {
	if (bookNo == data.bookNo) {
		units_sold += data.units_sold;
		revenue += data.revenue;
	} else {
		std::cout << "Different items\n";
	}
}

#endif
