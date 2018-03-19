#include <cmath>
#include <array>
#include <iostream>
#include <chrono>
#include <string.h>

#define ARRAY_SIZE 10000
#define SHUFFLE_TIMES 30000

using namespace std;

typedef array<int, ARRAY_SIZE> Array;

ostream& operator<<(ostream& os, const Array& arr);
void shuffle(Array& arr);
int search(int val, int* arr, int toIdx);
void sort(int *arr, long size);

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
	sort(&arr[0], arr.size());
	auto endTime = chrono::high_resolution_clock::now();
	auto diff = endTime - startTime;
	//cout << "Sorted: " << arr << endl;
	cout << "Time elapsed: " << chrono::duration_cast<chrono::microseconds>(diff).count() << " microseconds" << endl;
	return 0;
}

// shuffle a STL array
void shuffle(Array& arr) {
	for (long i = 0; i < SHUFFLE_TIMES; ++i) {
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

// merge sort
void sort(int *arr, long size) {
	if (size < 2)
		return;
	long midIdx = size / 2;
	sort(arr, midIdx);
	sort(arr + midIdx, size - midIdx);
	int left = 0, right = midIdx;
	int tmpArr[size];
	for (long idx = 0; idx < size; ++idx) {
		if (left < midIdx && (arr[left] < arr[right] || right >= size))
			tmpArr[idx] = arr[left++];
		else
			tmpArr[idx] = arr[right++];
	}
	memcpy(arr, tmpArr, size * sizeof(int));
}

// cout STL array
ostream& operator<<(ostream& os, const Array& arr) {
	os << "[";
	for (int idx = 0; idx < ARRAY_SIZE - 1; ++idx)
		os << arr[idx] << ", ";
	os << arr[ARRAY_SIZE - 1] << "]";
}