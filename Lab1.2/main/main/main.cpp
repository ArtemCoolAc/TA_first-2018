// main.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Mail.h"
#include <locale.h>
#include <Windows.h>
#include "Assoc.h"

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::string input; std::string output;
	Assoc stat;
	std::cout << "Хотите чтение из файла?" << std::endl;
	std::cout << "0.Нет" << std::endl;
	std::cout << "1.Да" << std::endl;
	int ans;
	std::cin >> ans;
	if (ans) {
		std::string fname;
		std::cout << "Введите имя файла" << std::endl;
		std::cin >> fname;
		try {
			stat.ReadFromFile(fname);
			std::cout << stat;
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << std::endl;
		}
	}
	while (std::cin.good()) {
		Mail thisContext;
		std::cout << "Введите строку" << std::endl;
		std::cin >> input;
		const char* copy = input.c_str();
		bool res = thisContext.CheckString(copy);
		res ? output = "корректная" : output = "инвалид";
		std::cout << "Строка : '" << input << "' - " << output << std::endl;
		if (res) {
			std::string name = thisContext.getName();
			std::cout << name << std::endl;
			stat.Add(name);
		}
		input.clear();
	}
	return 0;
}

