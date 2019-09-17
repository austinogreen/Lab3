#include <iostream>
#include <fstream>
#include <string>
#include <ios>
#include <iomanip>
#include <vector>

struct drillingRecord {
	double nums[16]; // holds the numeric data, in column order
	std::string strings[2]; // holds the string data, in column order
};

struct drillingArray {
	int capacity; // maximum capacity, in records
	drillingRecord* data = NULL; // pointer to array of records
};

// Doubles the size of the drilling array
drillingArray* doubleDrillingArray(drillingArray* currentDrillingArray) {
	// New Drilling Record with twice the capacity
	drillingRecord* newDR = new drillingRecord[currentDrillingArray->capacity * 2];

	// Copies contents of old array into the new one
	//memcpy(newDR, currentDrillingArray->data, (currentDrillingArray->capacity) * sizeof(drillingRecord));
	for (int i = 0; i < currentDrillingArray->capacity; i++) {
		newDR[i].strings[0] = currentDrillingArray->data[i].strings[0];
		newDR[i].strings[1] = currentDrillingArray->data[i].strings[1];
		for (int j = 0; j < 16; j++) {
			newDR[i].nums[j] = currentDrillingArray->data[i].nums[j];
		}
	}

	// Updates the capacity
	currentDrillingArray->capacity *= 2;

	// Deletes the old array
	delete[] currentDrillingArray->data;

	// Updates old data array to new one
	currentDrillingArray->data = newDR;

	return currentDrillingArray;
}

int main() {
	// The drilling array
	drillingArray* currentDrillingArray = new drillingArray;

	// Adds new valid data to the currentDrillingArray struct
	currentDrillingArray->capacity = 10;
	currentDrillingArray->data = new drillingRecord[10];

	// Temperary string variable
	std::string tempString;

	// Time array
	std::vector<std::string> time;

	bool isValid = true;

	// iterator
	unsigned int i;
	// Line count for error messages and time vector
	int lineCount = 0;
	// Amount of valid data
	int dataPoints = 0;

	// Throws away first line
	std::getline(std::cin, tempString);

	// Puts date in date variable
	std::getline(std::cin, tempString, ',');
	currentDrillingArray->data[0].strings[0] = tempString;

	// While not at end of file
	while (!tempString.empty()) {
		// preps the valid flag to true
		isValid = true;

		// Check size of array
		if (dataPoints >= currentDrillingArray->capacity) {
			currentDrillingArray = doubleDrillingArray(currentDrillingArray);
		}

		// Check if date is the same
		if (tempString.compare(currentDrillingArray->data[0].strings[0]) != 0) {
			std::cout << "Non-matching date stamp " << tempString << " at line " << lineCount + 1 << "." << std::endl;
			isValid = false;
		}

		std::getline(std::cin, tempString, ',');
		// If data is still valid
		if (isValid) {
			// Itterate though time vector to check if time is equal to previous times
			for (std::string s : time) {
				// gives error if so
				if (tempString.compare(s) == 0) {
					std::cout << "Duplicate timestamp " << tempString << " at line " << lineCount + 1 << "." << std::endl;
					isValid = false;
					break;
				}
			}

			// adds new time to time array
			if (isValid) {
				currentDrillingArray->data[dataPoints].strings[1] = tempString;
			}
		}
		time.push_back(tempString);

		// puts data in data array
		// gets first 15 data points that are separated by commas

		for (i = 0; i < ((sizeof(currentDrillingArray->data[dataPoints].nums) / sizeof(*(currentDrillingArray->data[dataPoints].nums))) - 1); i++) {
			std::getline(std::cin, tempString, ',');
			currentDrillingArray->data[dataPoints].nums[i] = std::stof(tempString);
		}
		// gets final data point with newline
		std::getline(std::cin, tempString);
		currentDrillingArray->data[dataPoints].nums[i] = std::stof(tempString);

		// checks if data is valid
		for (i = 0; i < ((sizeof(currentDrillingArray->data[dataPoints].nums) / sizeof(*currentDrillingArray->data[dataPoints].nums))); i++) {
			if ((currentDrillingArray->data[dataPoints].nums[i] <= 0) && isValid) {
				std::cout << "Invalid floating-point data at line " << lineCount + 1 << "." << std::endl;
				isValid = false;
				break;
			}
		}


		// Incrememnt line count
		lineCount++;
		if (isValid) {
			dataPoints++;
		}
		std::getline(std::cin, tempString, ',');
	}
	unsigned int j;
	// Prints data (loop)
	for (int i = (dataPoints - 1); i >= 0; i--) {
		std::cout << currentDrillingArray->data[0].strings[0] << ";";
		std::cout << currentDrillingArray->data[i].strings[1] << ";";
		for (j = 0; j < (((sizeof(currentDrillingArray->data[dataPoints].nums) / sizeof(*currentDrillingArray->data[dataPoints].nums))) - 1); j++) {
			std::cout << std::fixed;
			std::cout << std::setprecision(2);
			std::cout << currentDrillingArray->data[i].nums[j] << ";";
		}
		// ensures that there isn't a semicolon at end of line
		std::cout << currentDrillingArray->data[i].nums[j] << std::endl;
	}
}