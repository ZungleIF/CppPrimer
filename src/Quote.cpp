#include "Quote.h"

using namespace std;

Quote::Quote(const string& _bookNo, double _price)	: bookNo(_bookNo), price(_price) {}
Quote::Quote(const Quote& org)						: bookNo(org.bookNo), price(org.price) {}
Quote::Quote(Quote&& org) noexcept					: bookNo(org.bookNo), price(org.price) {}
Quote::~Quote() {}
Quote& Quote::operator=(const Quote& rhs) {
	Quote temp = rhs;
	bookNo = temp.bookNo;
	price = temp.price;
	return *this;
}
Quote& Quote::operator=(Quote&& rhs) noexcept{
	if (this != &rhs) {
		bookNo = rhs.bookNo;
		price = rhs.price;
	}
	return *this;
}

Disc_quote::Disc_quote(const string& _bookNo, double _price, size_t mq, double disc)
													: Quote(_bookNo, _price), min_qty(mq), discount(disc) {}

Bulk_quote::Bulk_quote(const string& s, double p, size_t n, double rate) 
													: Disc_quote(s, p, n, rate) {}

Bulk_quote::Bulk_quote(const Bulk_quote& org)		: Disc_quote(org) {}
Bulk_quote::Bulk_quote(Bulk_quote&& org) noexcept	: Disc_quote(org) {}
Bulk_quote& Bulk_quote::operator=(const Bulk_quote& rhs){
	Disc_quote::operator=(rhs);
	return *this;
}
Bulk_quote& Bulk_quote::operator=(Bulk_quote&& rhs) noexcept {
	Disc_quote::operator=(std::move(rhs));
	return *this;
}
Bulk_quote::~Bulk_quote() {}

Bulk_quote_limit::Bulk_quote_limit(const string& s, double p, size_t min, size_t max, double rate)
													: Disc_quote(s, p, min, rate), max_qty(max) {}

Quote* Quote::clone() const & {
	return new Quote(*this);
}

Quote* Quote::clone() && {
	return new Quote(move(*this));
}

Quote* Bulk_quote::clone() const & {
	return new Bulk_quote(*this);
}

Quote* Bulk_quote::clone() && {
	return new Bulk_quote(move(*this));
}

double Bulk_quote::net_price(size_t n) const {
	if (n >= min_qty)
		return n * (1 - discount) * price;
	else
		return n * price;
}

double Bulk_quote_limit::net_price(size_t n) const {
	if (n >= min_qty) {
		if (n < max_qty)
			return n * (1 - discount) * price;
		else
			return Quote::net_price(n);
	}
	else
		return Quote::net_price(n);
}

double print_total(ostream& os, const Quote& q, size_t n) {
	cout << "ISBN: " << q.isbn() << " No. of books sold: " << n << endl
		<< "Total revenue produced: " << q.net_price(n) << endl;
	return q.net_price(n);
}

Basket& Basket::addItem(const shared_ptr<Quote>& q) {
	quote_set.insert(shared_ptr<Quote>(q->clone()));
	return *this;
}

//double Basket::totalReceipt(istream& is) {
//
//}

bool Basket::isSmallerIsbn(const shared_ptr<Quote>& q1, const shared_ptr<Quote>& q2) {
	return q1->isbn() < q2->isbn() ? true : false;
}