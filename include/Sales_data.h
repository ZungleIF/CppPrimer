#pragma once
#include <vector>
#include <string>
#include <tuple>
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

// checks whether isbn's match
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

// 17.4
inline bool compareIsbn(const Sales_data& sd1, const Sales_data& sd2) {
  return sd1.isbn() == sd2.isbn();
}
using matches = std::tuple<std::vector<Sales_data>::size_type,
                           std::vector<Sales_data>::const_iterator,
                           std::vector<Sales_data>::const_iterator>;
std::vector<matches> findBook(const std::vector<std::vector<Sales_data>>& files,
                              const std::string& book_name);

// 17.6
struct matches_ {
  std::vector<Sales_data>::size_type sz;
  std::vector<Sales_data>::const_iterator begin;
  std::vector<Sales_data>::const_iterator end;
};
std::vector<matches_> findBook_(const std::vector<std::vector<Sales_data>>& files, 
                                const std::string& book_name);

// 18.9
class out_of_stock : public std::runtime_error {
public:
  explicit out_of_stock(const std::string& s) noexcept : runtime_error(s) {}
};

class isbn_mismatch : public std::logic_error {
public:
  explicit isbn_mismatch(const std::string& s) noexcept : logic_error(s) {}
  isbn_mismatch(const std::string& s, const Sales_data& lhs, const Sales_data& rhs)
    : logic_error(s), left(lhs.isbn()), right(rhs.isbn()) {}
  std::string left, right;
};

//Sales_data sd1("1234", 1, 0.2);
//Sales_data sd2("4321", 4, 0.1);
//try
//{
//sd1 += sd2;
//} catch (const isbn_mismatch& e)
//{
//  cerr << e.what() << "left: " << e.left << " right: " << e.right << endl;
//}

// 18.10
// 예외를 처리하지 않았을 경우에도 정상적으로 컴파일은 되지만 런타임에서 
// unhandled exception thrown 오류가 나타난다. 반면, 예외를 try...catch 
// 로 정상적으로 처리할 경우, 프로그램은 계속 정상적으로 실행되고 예외에 관련된 메세지가
// 콘솔창으로 나타난다.