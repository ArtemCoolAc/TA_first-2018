// Reg.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <regex>
#include <string>
#include <locale.h>
#include <Windows.h>
#include <iostream>
#include "Assoc.h"

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Assoc stat;
	std::string input;
	//const std::string expr = "^mailto:(\\w+)@(\\w+)[.](\\w+)[?]subject=(\\w){0,64}$";
	const std::string expr = "^mailto:([a-z0-9]+)@([a-z0-9]+)\\.([a-z0-9]+)[?]subject=([a-z0-9]){0,64}$";
	std::smatch m;
	std::regex reg(expr, std::regex::icase);
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
			//std::cout << stat;
			std::cout << "Работа завершена" << std::endl;
			system("pause");
		}
		catch (std::exception &ex) {
			std::cout << ex.what() << std::endl;
		}
	}
	do {
		std::cout << "Введите выражение" << std::endl;
		std::cin >> input;
		bool res = std::regex_match(input, m, reg);
		std::cout << res << std::endl;
		if (res) stat.Add(m[1]);
		for (int i = 1; i < m.size(); ++i) {
			std::cout << m[i] << std::endl;
		}
		std::cout << "Словарь:" << std::endl;
		std::cout << stat;
		
		system("pause");
	} while (std::cin.good());
	return 0;
}

