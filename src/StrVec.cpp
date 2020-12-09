#include "StrVec.h"
#include <iostream>
#include <algorithm>
using namespace std;

StrVec::StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}

StrVec::StrVec(size_t n) {
	while (capacity() < n) {
		realloc();
#ifdef _DEBUG
		cout << "capacity():	" << capacity() << "\n";
#endif // DEBUG

	}
}

StrVec::StrVec(initializer_list<string> il) {
	for_each(il.begin(), il.end(),
		[this](string str) {
			check_n_alloc();
			alloc.construct(first_free++, str); 
		}
	);
	/*for (auto str : il) {
		check_n_alloc();
		alloc.construct(first_free++, str);
	}*/
}

StrVec::StrVec(const StrVec& org) {
	auto pair = alloc_n_copy(org.begin(), org.end());
	elements = pair.first;
	first_free = pair.second;
	cap = elements + org.size();
}

StrVec::StrVec(StrVec &&org) noexcept
	: elements(org.elements), first_free(org.first_free), cap(org.cap)	   
{
	org.elements = org.first_free = org.cap = nullptr;
}

StrVec &StrVec::operator=(const StrVec &rhs) {
	auto pair = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = pair.first;
	first_free = pair.second;
	cap = elements + rhs.size();
	return *this;
}

StrVec &StrVec::operator=(StrVec &&rhs) noexcept {
	if (this != &rhs) {
		elements = rhs.elements;
		first_free = rhs.first_free;
		cap = rhs.cap;
		rhs.elements = rhs.first_free = rhs.cap = nullptr;
	}
	return *this;
}

StrVec::~StrVec() {
	free();
}

StrVec& StrVec::operator=(const initializer_list<string>& il) {
	auto pair = alloc_n_copy((SVIter)(il.begin()), (SVIter)(il.end()));
	free();
	elements = pair.first;
	first_free = cap = pair.second;
	return *this;
}

void StrVec::resize(size_t sz) {
	if (sz < size()) {
		while (size() != sz) {
			alloc.destroy(--first_free);
		}
	}
	else {
		while (capacity() < sz) {
			realloc();
		}
	}
}

void StrVec::push_back(const string& str) {
	check_n_alloc();
	alloc.construct(first_free++, str);
}

allocator<string> StrVec::alloc;

inline void StrVec::check_n_alloc() {
	if (size() == capacity())
		realloc();
}

pair<SVIter, SVIter>
StrVec::alloc_n_copy(const SVIter iter1, const SVIter iter2) {
	auto newdata = alloc.allocate(iter2 - iter1);
	// uninitialized_copy copies [iter1, iter2) into a memory space starting from
	// memory pointed by newdata and returns new first_free keep in mind that 
	// first_free is pointing to one-off actual first available element.
	return { newdata, uninitialized_copy(iter1, iter2, newdata) };
}

void StrVec::free() {
	// use for_each algorithm instead of for or while loop
	for_each(elements, first_free, [](const string &iter) { alloc.destroy(&iter); });
	
	/*while (elements != first_free) {
		alloc.destroy(--first_free);
	}*/
	if(capacity() > 0)
		alloc.deallocate(elements, capacity());
#ifdef _DEBUG
	cout << "StrVec free() called\n";
#endif // DEBUG

}

void StrVec::realloc() {
	auto newsize = capacity() < 1 ? 1 : capacity() * 2;
	auto newdata = alloc.allocate(newsize);
	auto dest = newdata;
	auto elem = elements;
	while (elem != first_free) {
		/*
			std::move makes construct() to call std::string move constructor,
			not copy constructor, this is included in <utility> header
			if it copies, not moves, everytime this reallocates,
			it will create a serious performance problem
		*/
		alloc.construct(dest++, std::move(*elem++));
	}
	free();
	elements = newdata;
	first_free = dest;
	cap = newdata + newsize;
#ifdef _DEBUG
	cout << "reallocated to :\n	"
		<< "size(): " << size() << "\n"
		<< "capacity(): " << capacity() << "\n";
#endif // _DEBUG	
}
