#include "MyString.h"
#include <algorithm>
#include <limits>
using namespace std;

allocator<char> String::alloc;

String::String(const char *c_str) {
	size_t size = c_str_len(c_str);
	_begin = _end = alloc.allocate(size);
	for (size_t i = 0; i < size; i++) 
		alloc.construct(_end++, *c_str++);
}

String::String(const String &org) {
	_begin = _end = alloc.allocate(org.length());
	_end = uninitialized_copy(org._begin, org._end, _begin);
}

String &String::operator=(const String &rhs) {
	auto newfront = alloc.allocate(rhs.length());
	auto newback = uninitialized_copy(rhs._begin, rhs._end, newfront);
	free();
	_begin = newfront;
	_end = newback;
	return *this;
}

String::~String() {
	free();
}

void String::free() {
	for_each(_begin, _end, [this](char ch) { alloc.destroy(&ch); });
	alloc.deallocate(_begin, length());
	_begin = _end = nullptr;
}

String& String::operator+=(const String& str) {
	*this = *this + str;
	return *this;
}

String& String::append(const String& str) {
	*this += str;
	return *this;
}

ostream& operator<<(ostream &os, const String &str) {
	auto front = str._begin;
	auto back = str._end;
	while (front != back)
		os << *front++;
	return os;
}

istream& operator>>(istream &is, String &str) {
	char c_str[256];
	if (is) {
		is.getline(c_str, 256);
		str = String(c_str);
	}
	else {
		//if(is.rdstate() & istream::failbit != 0) {}
		cerr << "Invalid input, try again" << endl;
		operator>>(is, str);
		//str = String();
	}
	return is;
}

String operator+(const String& lhs, const String& rhs) {
	auto newsize = rhs.length() + lhs.length();
	str_ptr newbegin, newend;
	newbegin = newend = String::alloc.allocate(newsize);
	newend = uninitialized_copy(lhs._begin, lhs._end, newend);
	newend = uninitialized_copy(rhs._begin, rhs._end, newend);
	String tempStr;
	tempStr._begin = newbegin;
	tempStr._end = newend;
	return tempStr;
}

size_t c_str_len(const char *c_str) {
	int sz = 0;
	for (auto cs_ptr = c_str; *cs_ptr != '\0' && *cs_ptr != '\n'; ++sz, cs_ptr++) {}
	return sz;
}