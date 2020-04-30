// main.cpp: ���������� ����� ����� ��� ����������� ����������.
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
	std::cout << "������ ������ �� �����?" << std::endl;
	std::cout << "0.���" << std::endl;
	std::cout << "1.��" << std::endl;
	int ans;
	std::cin >> ans;
	if (ans) {
		std::string fname;
		std::cout << "������� ��� �����" << std::endl;
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
		std::cout << "������� ������" << std::endl;
		std::cin >> input;
		const char* copy = input.c_str();
		bool res = thisContext.CheckString(copy);
		res ? output = "����������" : output = "�������";
		std::cout << "������ : '" << input << "' - " << output << std::endl;
		if (res) {
			std::string name = thisContext.getName();
			std::cout << name << std::endl;
			stat.Add(name);
		}
		input.clear();
	}
	return 0;
}

