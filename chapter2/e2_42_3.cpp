#include "Sales_data.h"

int main() {
	Sales_data total;
	double price;

	if (std::cin >> total.bookNo >> total.units_sold >> price) {
		total.calRevenue(price);

		Sales_data data;
		while (std::cin >> data.bookNo >> data.units_sold >> price) {
			data.calRevenue(price);
			total.updateSales(data);

			if (data.bookNo != total.bookNo) {
				total.printInfo();
				total = data;
			}
		}

		total.printInfo();
	} else {
		std::cerr << "No data?!\n";
		return -1;
	}

	return 0;
}
