#include <vector>
#include <iostream>

using namespace std;

void max_heapify(vector<int> &arr, int idx);
ostream& operator<< (ostream &os, const vector<int> &arr);

int main() {
	vector<int> arr = {16, 4, 10, 14, 7, 9, 3, 2, 8, 1};
	cout << "origin: " << arr << endl;
	max_heapify(arr, 1);
	cout << "heapify at node 1: " << arr << endl;
	return 0;
}

void max_heapify(vector<int> &arr, int idx) {
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

ostream& operator<< (ostream &os, const vector<int> &arr) {
	int arrLen = arr.size();
	for (int idx = 0; idx < arrLen - 1; ++idx)
		os << arr[idx] << ", ";
	os << arr[arrLen - 1];
	return os;
}