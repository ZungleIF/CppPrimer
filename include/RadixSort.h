#pragma once
#include <iostream>
#include <vector>
#include <array>

int getMax(const std::vector<int>& vec) {
	int max = 0;
	for (auto i : vec) {
		if (i > max)
			max = i;
	}
	return max;
}

void countSort(std::vector<int>& vec, int exp) {
	std::array<std::vector<int>, 10> count;
	for (auto i : vec) {
		count[(i / exp) % 10].push_back(i);
	}
	std::size_t	cnt = 0;
	for (auto temp_vec : count) {
		for (auto j : temp_vec) {
			vec[cnt++] = j;
		}
	}
}

void radixSort(std::vector<int>& vec) {
	int max = getMax(vec);
	for (int exp = 1; max > exp; exp *= 10) {
		countSort(vec, exp);
	}
}