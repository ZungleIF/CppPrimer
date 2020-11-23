#pragma once
#include <iostream>
#include "String.h"
#include <functional>
#include <map>
#include <vector>
#include <Windows.h>

class TableCalc
{
public:
	TableCalc() = default;
	void run();
private:
	std::map<char, std::function<int(int, int)>> binops = 
	{
		{'+', [](int a, int b) { return a + b; }},
		{'-', [](int a, int b) { return a - b; }},
		{'/', [](int a, int b) { return a / b; }},
		{'*', [](int a, int b) { return a * b; }},
		{'%', [](int a, int b) { return a & b; }},
	};
	std::vector<std::string> commands = 
	{
		"Waiting for first operand",
		"Waiting for an operator",
		"Waiting for sencond operand"
	};

	void print_menu() const;
	int val_type = 0;
	int val = 0;
	char op = '\0';
};

DWORD WINAPI CheckEscape(LPVOID lpParam);