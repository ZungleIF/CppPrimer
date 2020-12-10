#pragma once
#include <iostream>
#include <vector>
//13.13
using namespace std;
class X {
public:
	X() { cout << "X()\n"; }
	X(const X &org) { cout << "X(const X&)\n"; }
	X& operator=(const X &rhs) { cout << "X& operator=(const X&)\n"; }
	~X() { cout << "~X()\n"; }
};

void refParameter(const X &x) {}
void nonRefParameter(const X x) {}


int ch13_3() {
	X a, *b = new X; // X() X()
	refParameter(a); // binding to a reference does not call the copy constructor
	nonRefParameter(a); // calls to the copy constructor
	vector<X> x_vec;
	x_vec.push_back(a);
	delete b; // calls to the deleter
	return 0; // calls deleter from a and X type element in svec
}


int ch4_33() {
	int x = 0, y = 0;
	//printf("%d\n", true ? ++x, ++y : --x, --y);
	cout << x << "\n";
	return 0;
}