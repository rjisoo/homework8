#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

int firstFit(vector<int> weights, int capacity, int itemIndex);
int firstFitDecreasing(vector<int> weights, int capacity, int itemIndex);
int bestFit(vector<int> weights, int capacity, int itemIndex);

int main() {
	int rowIndex = 0;
	int itemIndex = 0;
	int testCases = 0;
	int capacity = 0;
	vector<int> weightsVector;
	string line;
	stringstream row;
	
	ifstream myInputFile("bin.txt");
	if (getline(myInputFile, line)) {
		// read first line and assign it to test case
		stringstream row(line);
		if (row >> rowIndex) {
			testCases = rowIndex;
		}

		for (int i = 0; i < testCases; i++) {
			// read 3 lines for each test cases, and assign it to proper variable
			getline(myInputFile, line);
			stringstream row1(line);
			row1 >> rowIndex;
			capacity = rowIndex;

			getline(myInputFile, line);
			stringstream row2(line);
			row2 >> rowIndex;
			itemIndex = rowIndex;

			getline(myInputFile, line);
			stringstream row3(line);
			row3 >> rowIndex;
			for (int k = 0; k < itemIndex; k++) {
				weightsVector.push_back(rowIndex);
				row3 >> rowIndex;
			}

			int ffResult = firstFit(weightsVector, capacity, itemIndex);
			int ffdResult = firstFitDecreasing(weightsVector, capacity, itemIndex);
			int bfResult = bestFit(weightsVector, capacity, itemIndex);

			cout << "Test Case " << i + 1 << " First Fit: " << ffResult
				<< ", First Fit Decreasing: " << ffdResult
				<< ", Best Fit: " << bfResult << endl;

			for (int i = 0; i < itemIndex; i++) {
				weightsVector.erase(weightsVector.begin());
			}
		}
	}
	return 0;
}

int firstFit(vector<int> weights, int capacity, int itemIndex) {
	int bin = 0;
	int capacityCopy[itemIndex];
	
	// iterate bins in order
	for (int i = 0; i < itemIndex; i++) {
		int j;

		// calculate the bin as encounters
		for (j = 0; j < bin; j++) {
			if (capacityCopy[j] >= weights[i]) {
				capacityCopy[j] -= weights[i];
				break;
			}
		}

		// if no bins available, open new one
		if (j == bin) {
			capacityCopy[bin] = capacity - weights[i];
			bin++;
		}
	}
	return bin;
}

int firstFitDecreasing(vector<int> weights, int capacity, int itemIndex) {
	vector<int>sortedWeightVector = weights;
	sort(sortedWeightVector.begin(), sortedWeightVector.end(), std::greater<int>());
	return firstFit(sortedWeightVector, capacity, itemIndex);
}

/*  Place the
** next item into the bin which will leave the least room left
** over after the item is placed in the bin. If it does not fit
** in any bin, start a new bin. */
int bestFit(vector<int> weights, int capacity, int itemIndex) {
	int bin = 0;
	int capacityCopy[itemIndex];
	
	// put items in arrival order
	for (int i = 0; i < itemIndex; i++) {
		int smallestBinCap = capacity;
		int binIndex = 0;
		for (int j = 0; j < bin; j++) {

			// if bin capacity is bigger than the current weight and substraction of it is smaller than 
			// minimum capacity, next item should be the one leave the minimum room.
			if (capacityCopy[j] >= weights[i] && capacityCopy[j] - weights[i] <= smallestBinCap) {
				binIndex = j;
				smallestBinCap = capacityCopy[j] - weights[i];
			}
		}

		// if the smallest capacity is equal to bin capacity, substract it
		if (smallestBinCap == capacity) {
			capacityCopy[bin] = capacity - weights[i];
			bin++;
		} else {
			capacityCopy[binIndex] -= weights[i];
		}
	}
	return bin;
}