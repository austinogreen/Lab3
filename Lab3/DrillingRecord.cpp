#include "DrillingRecord.h"

std::ostream& operator<<(std::ostream& os, const DrillingRecord& record) {
	return;
}

void DrillingRecord::addNum(double num) {
	nums[numCtr] = num;
	numCtr++;
	return;
}

void DrillingRecord::addString(std::string string) {
	strings[strCtr] = string;
	strCtr++;
	return;
}

double DrillingRecord::getNum(unsigned int index) {
	return nums[index];
}

std::string DrillingRecord::getString(unsigned int index) {
	return strings[index];
}