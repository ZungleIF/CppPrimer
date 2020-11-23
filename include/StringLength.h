#pragma once
#include <string>
class StringLength
{
public:
	StringLength(const size_t n) : len(n) {}
	bool operator()(const std::string& str) const {
		return str.length() == len ? true : false;
	}
private:
	size_t len;
};