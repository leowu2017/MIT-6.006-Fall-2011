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
void sort(Array &arr);
void build_max_heap(Array &arr);
void max_heapify(int* arr, int idx, int length);

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
	// heap sort
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
void sort(Array &arr) {
	int size = arr.size();
	if (size < 2)
		return;
	build_max_heap(arr);
	while (size-- > 1) {
		int tmp = arr[0];
		arr[0] = arr[size];
		arr[size] = tmp;
		max_heapify(&arr[0], 0, size);
	}
}

void build_max_heap(Array &arr) {
	int arrLen = arr.size();
	for (int i = (arrLen - 1) / 2; i >= 0; --i)
		max_heapify(&arr[0], i, arrLen);
}

void max_heapify(int *arr, int idx, int length) {
	int leftIdx = idx * 2 + 1;
	int rightIdx = idx * 2 + 2;
	if (leftIdx >= length || (rightIdx >= length && arr[idx] > arr[leftIdx]) || (arr[idx] > arr[leftIdx] && arr[idx] > arr[rightIdx]))
		return;
	else if (rightIdx >= length || arr[leftIdx] >= arr[rightIdx]) {
		int tmp = arr[idx];
		arr[idx] = arr[leftIdx];
		arr[leftIdx] = tmp;
		max_heapify(arr, leftIdx, length);
	}
	else {
		int tmp = arr[idx];
		arr[idx] = arr[rightIdx];
		arr[rightIdx] = tmp;
		max_heapify(arr, rightIdx, length);
	}
}


// cout STL array
ostream& operator<<(ostream& os, const Array& arr) {
	os << "[";
	for (int idx = 0; idx < ARRAY_SIZE - 1; ++idx)
		os << arr[idx] << ", ";
	os << arr[ARRAY_SIZE - 1] << "]";
}