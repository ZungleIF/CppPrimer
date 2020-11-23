#pragma once
#include <memory>
#include <iostream>

using str_ptr = char*;
class String
{
	friend std::ostream& operator<<(std::ostream&, const String&);
	friend std::istream& operator>>(std::istream&, const String&);
	friend String operator+(const String&, const String&);

public:
	using size_type = size_t;
	using value_type = char;
	String() : _begin(nullptr), _end(nullptr) {}
	String(const char *);
	String(const String&);
	String &operator=(const String&);
	~String();

	size_t length() const { return _end - _begin; }

	str_ptr begin() { return _begin; }
	str_ptr end() { return _end; }

	String& operator+=(const String&);
	char& operator[](std::size_t n)					{ return _begin[n]; }
	const char& operator[](std::size_t n) const		{ return _begin[n]; }
	String& append(const String&);
private:
	static std::allocator<char> alloc;
	str_ptr _begin;
	str_ptr _end;

	void free();
};

std::ostream& operator<<(std::ostream&, const String&);
std::istream& operator>>(std::istream&, String&);
String operator+(const String&, const String&);

size_t c_str_len(const char *);