#include "DrillingRecord.h"
#include <iomanip>

std::ostream& operator<<(std::ostream& os, const DrillingRecord& record) {
	std::cout << record.getString[0] + ";";
	std::cout << record.getString[1] + ";";
	std::cout << std::fixed;
	std::cout << std::setprecision(2);

	for (int i = 0; i < 15; i++) {
		std::cout << record.getNum[i] << ";";
	}
	// ensures that there isn't a semicolon at end of line
	std::cout << record.getNum[16] << std::endl;
	return os;
}

void DrillingRecord::addNum(double num) {
	nums[numCtr] = num;
	if (numCtr == 15) {

		numCtr = 0;
	}
	numCtr++;
	return;
}

void DrillingRecord::addString(std::string string) {
	strings[strCtr] = string;
	// if prev 0, = 1
	// if prev 1, = 0
	strCtr = (strCtr + 1) % 2;
	return;
}

double DrillingRecord::getNum(unsigned int index) const {
	return nums[index];
}

std::string DrillingRecord::getString(unsigned int index) const {
	return strings[index];
}