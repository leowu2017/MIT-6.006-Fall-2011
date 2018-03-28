#include <array>
#include <iostream>

#define ARRAY_SIZE 10
#define SHUFFLE_TIMES 30

using namespace std;

typedef array<int, ARRAY_SIZE> Array;

void build_max_heap(Array &arr);
void max_heapify(Array &arr, int idx);
ostream& operator<< (ostream &os, const Array &arr);
void shuffle(Array& arr);

int main() {
	Array arr;
	// Initialize array
	{
		int val = 0;
		for (auto &a : arr)
			a = val++;
	}
	// shuffle array
	shuffle(arr);
	cout << "origin: " << arr << endl;
	build_max_heap(arr);
	cout << "max heap: " << arr << endl;
	return 0;
}

void build_max_heap(Array &arr) {
	int arrLen = arr.size();
	for (int i = (arrLen - 1) / 2; i >= 0; --i)
		max_heapify(arr, i);
}

void max_heapify(Array &arr, int idx) {
	int arrLen = arr.size();
	int leftIdx = idx * 2 + 1;
	int rightIdx = idx * 2 + 2;
	if (leftIdx >= arrLen || (rightIdx >= arrLen && arr[idx] > arr[leftIdx]) || (arr[idx] > arr[leftIdx] && arr[idx] > arr[rightIdx]))
		return;
	else if (rightIdx >= arrLen || arr[leftIdx] >= arr[rightIdx]) {
		int tmp = arr[idx];
		arr[idx] = arr[leftIdx];
		arr[leftIdx] = tmp;
		max_heapify(arr, leftIdx);
	}
	else {
		int tmp = arr[idx];
		arr[idx] = arr[rightIdx];
		arr[rightIdx] = tmp;
		max_heapify(arr, rightIdx);
	}
}

ostream& operator<< (ostream &os, const Array &arr) {
	int arrLen = arr.size();
	for (int idx = 0; idx < arrLen - 1; ++idx)
		os << arr[idx] << ", ";
	os << arr[arrLen - 1];
	return os;
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
