#pragma once
#include <string>
class HasPtr_Val {
	friend void swap(HasPtr_Val&, HasPtr_Val&);
public:
	HasPtr_Val(const std::string &str = std::string())
		: ps(new std::string(str)), i(0) {}
	HasPtr_Val(const HasPtr_Val &org)
		: ps(new std::string(*org.ps)), i(org.i) {}
	HasPtr_Val(HasPtr_Val &&org) noexcept
		: ps(org.ps), i(org.i) { org.ps = nullptr; }
	HasPtr_Val& operator=(HasPtr_Val rhs) {
		swap(*this, rhs);
		return *this;
	} 
	~HasPtr_Val() { delete ps; }
private:
	std::string *ps;
	int i;
};

class HasPtr_Ptr {
public:
	HasPtr_Ptr(const std::string &str = std::string())
		: use(new size_t(1)), ps(new std::string(str)), i(0) {}
	HasPtr_Ptr(const HasPtr_Ptr &org)
		: ps(org.ps), i(org.i) { 
		(*use)++;
	}
	HasPtr_Ptr& operator=(HasPtr_Ptr &rhs) {
		(*rhs.use)++;
		check_destroy();
		use = rhs.use;
		ps = rhs.ps;
		i = rhs.i;
		return *this;
	}
	~HasPtr_Ptr() {
		check_destroy();
	}
private:
	size_t *use = nullptr;
	std::string *ps = nullptr;
	int i = 0;

	void check_destroy() {
		if (--*use == 0) {
			delete ps;
			delete use;
			ps = nullptr;
			use = nullptr;
		}
	}
};

void swap(HasPtr_Val &lhs, HasPtr_Val &rhs) {
	using std::swap;
	swap(lhs.ps, rhs.ps);
	swap(lhs.i, rhs.i);
}