#pragma once
#include <string>
#include <iostream>
template <typename T> struct std::hash;
class Sales_data
{	
	friend struct std::hash<Sales_data>;
	friend bool operator==(const Sales_data&, const Sales_data&);
	friend Sales_data operator+(const Sales_data&, const Sales_data&);
	friend std::istream &operator>>(std::istream&, Sales_data&);
	friend std::ostream &operator<<(std::ostream&, const Sales_data&);
public:
	Sales_data() = default;
	Sales_data(const std::string &s, unsigned int us = 0, double p = 0.0)
		: bookNo(s), unitsSold(us), revenue(us * p) {}
	explicit Sales_data(std::istream &is)  
		{ is >> *this; }
	~Sales_data() = default;
	Sales_data &operator+=(const Sales_data&);
	std::string isbn() const { return bookNo; }

	Sales_data& operator=(const std::string&);

	operator std::string() const { return bookNo; }
	operator double() const { return revenue; }
private:
	double avg_price() const 
		{ return unitsSold ? revenue / unitsSold : 0; }
	std::string bookNo;
	unsigned int unitsSold = 0;
	double revenue = 0.0;
};

bool operator==(const Sales_data &lhs, const Sales_data &rhs);
Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs);
std::istream &operator>>(std::istream &is, Sales_data &rhs);
std::ostream &operator<<(std::ostream &os, const Sales_data &rhs);


void check_bookNo(const Sales_data&, const Sales_data&);

// hash class specialization for unordered_multiset of Sales_data
namespace std {
	template <>
	struct hash<Sales_data> {
		using result_type = size_t;
		using argument_type = Sales_data;
		size_t operator()(const Sales_data&) const;
	};
}
