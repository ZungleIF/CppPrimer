#include "StrBlob.h"
#include <iostream>
using namespace std;

StrBlob& StrBlob::operator=(StrBlob rhs) {
	swap(*this, rhs);
	return *this;
}

string& StrBlob::front() { return str_blob->front(); }
string& StrBlob::back() { return str_blob->back(); }
StrBlobPtr StrBlob::begin() { return StrBlobPtr(*this); }
StrBlobPtr StrBlob::end() { return StrBlobPtr(*this, str_blob->size()); }

void swap(StrBlob &lhs, StrBlob &rhs) {
	using std::swap;
#ifdef DEBUG
	cout << "non-member swap used\n";
#endif
	swap(lhs.str_blob, rhs.str_blob);
}

//	++ increments curr which indicates where this StrBlobPtr is pointing in StrBlob
StrBlobPtr& StrBlobPtr::operator++() {
#ifdef DEBUG
	cout << "Pre-increment called\n";
	check(curr, "Incrementing past the end");
#endif // DEBUG
	check(curr, "incrementing past the end");
	++curr;
	return *this;
}

/*
	Creates a temp instance of *this then increment it but the return value is
	before the incrementation so the sentence this function is called evaluates 
	the original one
*/
StrBlobPtr StrBlobPtr::operator++(int) {
#ifdef DEBUG
	cout << "Post-increment called\n";
	check(curr, "Incrementing past the end");
#endif // DEBUG
	auto ret = *this;
	operator++(); // Equivalents to ++(*this);
	return ret;
}

StrBlobPtr& StrBlobPtr::operator--() {
	check(--curr, "decrementing past the beginning");
	return *this;
}

StrBlobPtr StrBlobPtr::operator--(int) {
	auto ret = *this;
	operator--();
	return ret;
}

string& StrBlobPtr::operator*() const {
	auto deref = check(curr, "Dereferencing an undefined index");
	return (*deref)[curr];
}

string* StrBlobPtr::operator->() const {
	return &this->operator*();
}

shared_ptr<StrBlob::Blob>
StrBlobPtr::check(StrBlob::Blob::size_type sz, const string &msg) const {
	// lock() confirms whether the shared_ptr weak_ptr is 
	// bounded to is valid, if not, returns a nullptr
	auto deref = sb_ptr.lock(); 
	if (!deref) {
		throw runtime_error("Unbound weak pointer");
	}
	if (!(sz <= deref->size())) {
		throw out_of_range(msg);
	}
	return deref;
	// The returning type should not be in reference. deref is a temp value.
}

StrBlobPtr operator+(const StrBlobPtr &lhs, const StrBlob::Blob::size_type rhs) {
	StrBlobPtr temp = lhs;
	temp.curr = lhs.curr + rhs;
	return temp;
}

ptrdiff_t  operator-(const StrBlobPtr &lhs, const StrBlobPtr &rhs) {
	return lhs.curr - rhs.curr;
}