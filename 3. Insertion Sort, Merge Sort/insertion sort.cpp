#include <cmath>
#include <array>
#include <iostream>
#include <chrono>

#define ARRAY_SIZE 1000
#define SHUFFLE_TIMES 3000

using namespace std;

typedef array<int, ARRAY_SIZE> Array;

ostream& operator<<(ostream& os, const Array& arr);
void shuffle(Array& arr);
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

// Merge sort
void sort(Array& arr) {
	if (ARRAY_SIZE <= 1)
		return;
	for (int i = 1; i < ARRAY_SIZE; ++i) {
		int val = arr[i];
		for (int j = 0; j < i; ++j) {
			if (val < arr[j]) {
				for (int k = i; k > j; --k)
					arr[k] = arr[k - 1];
				arr[j] = val;
				break;
			}
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