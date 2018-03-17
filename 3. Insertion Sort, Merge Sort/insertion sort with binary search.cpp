#include <cmath>
#include <array>
#include <iostream>
#include <chrono>

#define ARRAY_SIZE 10000
#define SHUFFLE_TIMES 30000

using namespace std;

typedef array<int, ARRAY_SIZE> Array;

ostream& operator<<(ostream& os, const Array& arr);
void shuffle(Array& arr);
int search(int val, int* arr, int toIdx);
void sort(Array& arr);

int main(int argc, char** argv) {
	int seed = 0;
	if (argc > 1)
		srand(atoi(argv[1]));
	Array arr;
	// Initialize array
	{
		int val = 0;
		for (auto &a : arr)
			a = val++;
	}
	// shuffle array
	shuffle(arr);
	//cout << "Original: " << arr << endl;
	// merge sort
	auto startTime = chrono::high_resolution_clock::now();
	sort(arr);
	auto endTime = chrono::high_resolution_clock::now();
	auto diff = endTime - startTime;
	//cout << "Sorted: " << arr << endl;
	cout << "Time elapsed: " << chrono::duration_cast<chrono::microseconds>(diff).count() << " microseconds" << endl;
	return 0;
}

// shuffle a STL array
void shuffle(Array& arr) {
	for (int i = 0; i < SHUFFLE_TIMES; ++i) {
		int x = rand() % ARRAY_SIZE;
		int y;
		do {
			y = rand() % ARRAY_SIZE;
		} while(x == y);
		int tmp = arr[x];
		arr[x] = arr[y];
		arr[y] = tmp;
	}
}

// Binary search
int search(int val, int* arr, int toIdx) {
	int midIdx = toIdx / 2;
	if (val > arr[midIdx])
		if (midIdx == toIdx)
			return midIdx + 1;
		else
			return midIdx + 1 + search(val, &arr[midIdx + 1], toIdx - midIdx - 1);
	else if (val < arr[midIdx])
		if (midIdx == 0)
			return 0;
		else
			return search(val, arr, midIdx - 1);
	else
		return midIdx;
}

// Merge sort
void sort(Array& arr) {
	if (ARRAY_SIZE <= 1)
		return;
	for (int i = 1; i < ARRAY_SIZE; ++i) {
		int val = arr[i];
		int insertionIdx = search(val, &arr[0], i);
		if (insertionIdx != i) {
			val = arr[i];
			memmove(&arr[insertionIdx + 1], &arr[insertionIdx], (i - insertionIdx) * sizeof(int));
			arr[insertionIdx] = val;
		}
	}
}

// cout STL array
ostream& operator<<(ostream& os, const Array& arr) {
	os << "[";
	for (int idx = 0; idx < ARRAY_SIZE - 1; ++idx)
		os << arr[idx] << ", ";
	os << arr[ARRAY_SIZE - 1] << "]";
}