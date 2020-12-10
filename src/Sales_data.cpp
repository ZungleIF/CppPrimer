#include "Sales_data.h"
using namespace std;

Sales_data &Sales_data::operator+=(const Sales_data &rhs) {
	check_bookNo(*this, rhs);
	this->unitsSold += rhs.unitsSold;
	this->revenue += rhs.revenue;
	return *this;
}

Sales_data& Sales_data::operator=(const std::string& _bookNo) {
	this->bookNo = _bookNo;
	return *this;
}

bool operator==(const Sales_data &lhs, const Sales_data &rhs) {
	return lhs.bookNo == rhs.bookNo &&
		lhs.unitsSold == rhs.unitsSold &&
		lhs.revenue == rhs.revenue ?
		true : false;
}

Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs) {
	Sales_data temp = lhs;
	temp += rhs;
	return temp;
	/*return Sales_data(
		lhs.bookNo,
		lhs.unitsSold + rhs.unitsSold,
		lhs.avg_price()
	);*/
}

istream &operator>>(istream &is, Sales_data &rhs) {
	is >> rhs.bookNo >> rhs.unitsSold >> rhs.revenue;
	return is;
}

ostream &operator<<(ostream &os, const Sales_data &rhs) {
	os << rhs.bookNo << rhs.unitsSold << rhs.revenue;
	return os;
}

void check_bookNo(const Sales_data &sd1, const Sales_data &sd2) {
	if (sd1.isbn() != sd2.isbn()) {
		throw logic_error("Adding Sales_data with different isbn's");
	}
}

size_t hash<Sales_data>::operator()(const Sales_data& sd) const {
	return
		hash<unsigned int>()(sd.unitsSold) ^
		hash<double>()(sd.revenue) ^
		hash<std::string>()(sd.bookNo);
}
