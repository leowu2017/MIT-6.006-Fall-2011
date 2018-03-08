#include <cmath>
#include <iostream>
#include <vector>
#include <array>
#include <chrono>

using namespace std;

//#define LOG

int findMax(vector<int>& in) {
	long length = in.size();
	int maxVal = INT_MIN;
	int maxIdx = 0;
	for (long idx = 0; idx < length; ++idx) {
		if (in[idx] > maxVal) {
			maxVal = in[idx];
			maxIdx = idx;
		}
	}
	return maxIdx;
}

array<int, 4> findPeak(vector<vector<int>>& in, int from, int to, int counter) {
	array<int, 4> ret = {0, 0, 0, counter + 1};
	if (from == to) {
		ret[0] = from;
		int y = findMax(in[from]);
		ret[1] = y;
		ret[2] = in[from][y];
		return ret;
	}
	int center = (from + to) >> 1;
	int y = findMax(in[center]);
	if (center - 1 >= from && in[center - 1][y] > in[center][y])
		return findPeak(in, from, center - 1, counter + 1);
	else if (center + 1 <= to && in[center + 1][y] > in[center][y])
		return findPeak(in, center + 1, to, counter + 1);
	else {
		ret[0] = center;
		ret[1] = y;
		ret[2] = in[center][y];
		return ret;
	}
}

int main(int argc, char** argv) {
	unsigned arrayLenX = 8;
	unsigned arrayLenY = 4;
	unsigned repeatTimes = 1000;
	int seed = 0;
	if (argc > 1)
		arrayLenX = atoi(argv[1]);
	if (argc > 2)
		arrayLenY = atoi(argv[2]);
	if (argc > 3)
		repeatTimes = atoi(argv[3]);
	if (argc > 4)
		seed = atoi(argv[4]);

	srand(seed);

	auto start = chrono::high_resolution_clock::now();
	for (int idx = 0; idx < repeatTimes; ++idx) {
		vector<vector<int>>array2d(arrayLenX, vector<int>(arrayLenY));
		for (auto& array1d : array2d)
			for (auto& a : array1d)
				a = rand();

		array<int, 4> ret = findPeak(array2d, 0, arrayLenX - 1, 0);
#ifdef LOG
		for (long yIdx = array2d[0].size() - 1; yIdx > 0; --yIdx) {
			for (long xIdx = 0; xIdx < array2d.size() - 1; ++xIdx)
				cout << array2d[xIdx][yIdx] << ",\t";
			cout << array2d[array2d.size() - 1][yIdx] << ",\n";
		}
		for (long xIdx = 0; xIdx < array2d.size() - 1; ++xIdx)
			cout << array2d[xIdx][0] << ",\t";
		cout << array2d[array2d.size() - 1][0] << endl;
		cout << "index: (" << ret[0] << ", " << ret[1] << ")\nvalue: " << ret[2] << "\nsearch columns: " << ret[3] << endl << endl;
#endif
	}
	auto end = chrono::high_resolution_clock::now();
	auto dur = chrono::duration_cast<chrono::microseconds>(end - start).count();
	cout << "time elapsed: " << dur << " us" << endl;
	return 0;
}