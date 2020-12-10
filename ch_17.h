#pragma once
#include <tuple>
#include <vector>
#include <string>
#include <utility>
// tuple, #include <tuple>
// make_tuple and get<i>(t)
// 17.1
void ch_17_1() {
	std::tuple<int, int, int>{1, 2, 3};
}

// 17.2
void ch_17_2() {
	std::tuple<std::string, std::vector<std::string>, std::pair<std::string, int>> tu;
}