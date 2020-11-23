#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <map>

using namespace std::placeholders;
namespace zungleif {
	class PrintString {
	public:
		PrintString(std::ostream& _os = std::cout, const char c = ' ')
			: os(_os), delim(c) {}
		void operator()(const std::string& str) const {
			os << str << delim;
		}
	private:
		std::ostream& os;
		char delim;
	};

	class ReadString {
	public:
		ReadString(std::istream& _is = std::cin) : is(_is) {}
		std::string operator()() {
			std::string temp_str;
			std::getline(is, temp_str);
			return temp_str;
		}
	private:
		std::istream& is;
	};

	void readStrToVec(std::vector<std::string>& vec) {
		std::string temp;
		ReadString rs;
		while ((temp = rs()).size()) {
			vec.push_back(temp);
		}
	}


	template<typename T>
	class IsEqual {
	public:
		IsEqual() = default;
		bool operator()(T a, T b) {
			return a == b ? true : false;
		}
	};

	template<typename T>
	void change_if(std::vector<T>& vec, const T target_val, const T new_val) {
		replace_if(vec.begin(), vec.end(), std::bind(IsEqual<T>(), _1, target_val), new_val);
	}


	class StringLenRange {
	public:
		StringLenRange(size_t from, size_t to) : str_range({ from, to }) {}
		void operator()(const std::string& chk) {
			size_t size = chk.size();
			if (str_range.first <= size && size <= str_range.second) {
				if (str_count.find(size) == str_count.end()) {
					str_count.insert({ size, 0 });
				}
				++str_count[size];
			}
		}
		void printCount() {
			for (auto &p : str_count) {
				std::cout << "length(" << p.first << "): " << p.second << std::endl;
			}
		}
	private:
		std::map<size_t, size_t> str_count;
		std::pair<size_t, size_t> str_range;
	};
}
