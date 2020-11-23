#include "TableCalc.h"
#include <Windows.h>
#include <limits>

using namespace std;


void TableCalc::run() {
	print_menu(); 
	CreateThread(NULL, 0, CheckEscape, NULL, 0, NULL);
	int int_val;
	while (true) {
		if (!cin.good()) {
			cin.clear();
		}
		cin >> int_val;
	}

}

void TableCalc::print_menu() const {
	cout << "A simple TableCalc" << endl;
}

DWORD WINAPI CheckEscape(LPVOID lpParam) {
	while (!GetAsyncKeyState(VK_ESCAPE)) {
		Sleep(10);
	}
	exit(0);

}