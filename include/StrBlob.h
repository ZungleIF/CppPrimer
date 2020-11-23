#pragma once
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
class StrBlobPtr;
class StrBlob {
	friend class StrBlobPtr;
	friend void swap(StrBlob&, StrBlob&);

public:
	using Blob = std::vector<std::string>;
	StrBlob()										: str_blob(std::make_shared<Blob>()) {}
	StrBlob(Blob &b)								: str_blob(std::make_shared<Blob>(b)) {}
	StrBlob(std::initializer_list<std::string> il)	: str_blob(std::make_shared<Blob>(il)) {}
	
	StrBlob(const StrBlob &org)						: str_blob(org.str_blob) {}
	StrBlob& operator=(StrBlob rhs);

	std::string& front();
	std::string& back();
	StrBlobPtr begin();
	StrBlobPtr end();

	std::string& operator[](std::size_t n)				{ return (*str_blob)[n]; }
	const std::string& operator[](std::size_t n) const	{ return (*str_blob)[n]; }

	StrBlob& push_back(const std::string &s) { str_blob->push_back(s); return *this; }
	void pop_back() { str_blob->pop_back(); }

private:
	std::shared_ptr<Blob> str_blob;
};

class StrBlobPtr {
	friend StrBlobPtr operator+(const StrBlobPtr &lhs, const StrBlob::Blob::size_type rhs);
	friend ptrdiff_t operator-(const StrBlobPtr &lhs, const StrBlobPtr &rhs);
	friend inline bool operator!=(const StrBlobPtr &lhs, const StrBlobPtr &rhs);
public:
	StrBlobPtr() : sb_ptr(StrBlob().str_blob), curr(0) {}
	StrBlobPtr(StrBlob& sb, StrBlob::Blob::size_type _curr = 0)
		: sb_ptr(sb.str_blob), curr(_curr) {}

	StrBlobPtr& operator++(); // pre-increment
	StrBlobPtr operator++(int); // post-increment
	StrBlobPtr& operator--();
	StrBlobPtr operator--(int);
	std::string& operator*() const;; // dereference operator
	std::string* operator->() const;
	inline StrBlob::Blob::size_type get_curr() { return curr; }

private:
	// A weak pointer pointing to str_blob shared pointer
	std::weak_ptr <StrBlob::Blob> sb_ptr; 

	// currently pointing index
	StrBlob::Blob::size_type curr;

	// Checks whether sz is in range of str_blob that is pointed by
	// sb_ptr and returns str_blob as a result
	std::shared_ptr<StrBlob::Blob>
	check(StrBlob::Blob::size_type sz, const std::string &msg) const;
};

void swap(StrBlob&, StrBlob&);

StrBlobPtr operator+(const StrBlobPtr &lhs, const StrBlob::Blob::size_type rhs);
ptrdiff_t operator-(const StrBlobPtr &lhs, const StrBlobPtr &rhs);
inline bool operator!=(const StrBlobPtr &lhs, const StrBlobPtr &rhs) {
	return lhs.curr != rhs.curr ? true : false;
}