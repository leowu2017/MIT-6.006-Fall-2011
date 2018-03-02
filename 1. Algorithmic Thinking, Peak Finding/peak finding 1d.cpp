#include <cmath>
#include <iostream>
#include <vector>
#include <array>
#include <chrono>

using namespace std;

//#define LOG

array<int, 3> findPeak(vector<int>& in, int from, int to, int counter) {
	array<int, 3> ret = {0, 0, counter + 1};
	if (from == to) {
		ret[0] = from;
		ret[1] = in[from];
		return ret;
	}
	int center = (from + to) >> 1;
	if (center - 1 >= from && in[center - 1] > in[center])
		return findPeak(in, from, center - 1, counter + 1);
	else if (center + 1 <= to && in[center + 1] > in[center])
		return findPeak(in, center + 1, to, counter + 1);
	else {
		ret[0] = center;
		ret[1] = in[center];
		return ret;
	}
}

int main(int argc, char** argv) {
	unsigned arrayLen = 1000;
	unsigned repeatTimes = 1000;
	int seed = 0;
	if (argc > 1)
		arrayLen = atoi(argv[1]);
	if (argc > 2)
		repeatTimes = atoi(argv[2]);
	if (argc > 3)
		seed = atoi(argv[3]);

	srand(seed);

	auto start = chrono::high_resolution_clock::now();
	for (int idx = 0; idx < repeatTimes; ++idx) {
		vector<int>array1d(arrayLen);
		for (auto& a : array1d)
			a = rand();

		array<int, 3> ret = findPeak(array1d, 0, arrayLen - 1, 0);
#ifdef LOG
		for (long idx = 0; idx < array1d.size() - 1; ++idx)
			cout << array1d[idx] << ", ";
		cout << array1d[array1d.size() - 1] << endl;
		cout << "index: " << ret[0] << "\nvalue: " << ret[1] << "\nsearch times: " << ret[2] << endl << endl;
#endif
	}
	auto end = chrono::high_resolution_clock::now();
	auto dur = chrono::duration_cast<chrono::microseconds>(end - start).count();
	cout << "time elapsed: " << dur << " us" << endl;
	return 0;
}