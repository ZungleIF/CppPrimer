#pragma once
#include <vector>
#include <string>
#include <memory>
#include <utility>

using SVIter = std::string*;
class StrVec {
public:
	using size_type = size_t;
	StrVec();
	explicit StrVec(size_t);
	StrVec(std::initializer_list<std::string>);
	StrVec(const StrVec&);
	StrVec(StrVec&&) noexcept;
	StrVec &operator=(const StrVec&);
	StrVec &operator=(StrVec&&) noexcept;
	~StrVec();

	StrVec& operator=(const std::initializer_list<std::string>&);
	std::string& operator[](std::size_t n)						{ return elements[n]; }
	const std::string& operator[](const std::size_t n) const	{ return elements[n]; }

	SVIter begin() const		{ return elements; }
	SVIter end() const			{ return first_free; }
	std::string front() const	{ return *elements; }
	std::string back() const	{ return *first_free; }

	size_t size() const			{ return first_free - elements; }
	size_t capacity() const		{ return cap - elements; }

	void resize(size_t);
	void push_back(const std::string&);

private:
	SVIter elements = nullptr;		// -> the first element
	SVIter first_free = nullptr;	// -> the first available memory space that isn't written
	SVIter cap = nullptr;			// -> current capacity
	static std::allocator<std::string> alloc;
	/*
	helper functions
	check_n_alloc :	check if adding elements exceeds current capacity
					if true, reallocates (current cap * 2) and copy
	alloc_n_copy  :	reallocate the same memory space as iterator range 
					and copy returns new element & first_free pointers 
	*/
	
	void check_n_alloc();
	std::pair<SVIter, SVIter> alloc_n_copy(const SVIter, const SVIter);

	void free();
	void realloc();
};
