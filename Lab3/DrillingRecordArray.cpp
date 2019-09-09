#include "DrillingRecordArray.h"
#include "Driller.cpp"

DrillingRecordArray::DrillingRecordArray() {
	data = new DrillingRecord[DEFAULT_ARRAY_CAPACITY];
}
DrillingRecordArray::DrillingRecordArray(unsigned int capacity) {
	data = new DrillingRecord[capacity];
}

DrillingRecordArray::~DrillingRecordArray() {
	delete data;
}

void DrillingRecordArray::add(DrillingRecord record) {
	if (size >= capacity) {
		data = doubleDrillingArray(data);
	}
	data[size] = record;
	size++;
}

// Doubles the size of the drilling array
DrillingRecord* DrillingRecordArray::doubleDrillingArray(DrillingRecord* currentDrillingArray) {
	// New Drilling Record with twice the capacity
	DrillingRecord* newDR = new DrillingRecord[capacity * 2];

	// Copies contents of old array into the new one
	for (int i = 0; i < capacity; i++) {
		newDR[i].addString[0] = data[i].getString[0];
		newDR[i].addString[1] = data[i].getString[1];
		for (int j = 0; j < 16; j++) {
			newDR[i].getNum[j] = data[i].getNum[j];
		}
	}

	// Updates the capacity
	capacity *= 2;

	// Deletes the old array
	delete[] data;

	// Updates old data array to new one
	data = newDR;

	return data;
}

DrillingRecord DrillingRecordArray::get(unsigned int index) {
	return data[index];
}