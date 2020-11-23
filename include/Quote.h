#pragma once
#include <string>
#include <iostream>
#include <set>
class Quote
{
	friend class Basket;
public:
	Quote() = default;
	Quote(const std::string& _bookNo, double _price);
	Quote(const Quote& org);
	Quote(Quote&& org) noexcept;
	Quote& operator=(const Quote& rhs);
	Quote& operator=(Quote&& rhs) noexcept;
	virtual ~Quote();
	virtual double net_price(std::size_t n) const { return n * price; }

	std::string isbn() const { return bookNo; } 
private:
	std::string bookNo;
	virtual Quote* clone() const &;
	virtual Quote* clone() && ;
protected:
	double price = 0.0;
};

class Disc_quote : public Quote {
	friend class Basket;
public:
	Disc_quote() = default;
	Disc_quote(const std::string& _bookNo, double _price, std::size_t mq, double disc);
	Disc_quote(const Disc_quote& q) = default;
	Disc_quote(Disc_quote&&) noexcept = default;
	Disc_quote& operator=(const Disc_quote&) = default;
	Disc_quote& operator=(Disc_quote&&) noexcept = default;
	double net_price(std::size_t n) const = 0;
protected:
	std::size_t min_qty = 0;
	double discount = 0.0;
};

class Bulk_quote : public Disc_quote {
	friend class Basket;
public:
	Bulk_quote() = default;
	Bulk_quote(const std::string&, double, std::size_t, double);
	Bulk_quote(const Bulk_quote& org);
	Bulk_quote(Bulk_quote&& org) noexcept;
	Bulk_quote& operator=(const Bulk_quote& rhs);
	Bulk_quote& operator=(Bulk_quote&& rhs) noexcept;
	~Bulk_quote() override;

	double net_price(std::size_t) const override;
private:
	Quote* clone() const & override;
	Quote* clone() && override;
};

class Bulk_quote_limit : public Disc_quote {
public:
	Bulk_quote_limit() = default;
	Bulk_quote_limit(const std::string&, double, std::size_t, std::size_t, double);
	double net_price(std::size_t) const override;
private:
	std::size_t max_qty;
};

double print_total(std::ostream&, const Quote&, std::size_t);


/* A container class for storing derived class types from Quote */
class Basket {
	Basket() = default;
	Basket& addItem(const std::shared_ptr<Quote>&);
	//double totalReceipt(std::istream&);
private:
	static bool isSmallerIsbn(const std::shared_ptr<Quote>&, 
							  const std::shared_ptr<Quote>&);
	std::multiset<std::shared_ptr<Quote>, decltype(isSmallerIsbn)*>
		quote_set{ isSmallerIsbn };
};