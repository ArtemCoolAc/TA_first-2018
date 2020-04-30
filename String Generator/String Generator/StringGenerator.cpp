// StringGenerator.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Generator.h"
#include <iostream>
#include <time.h>
#include <fstream>
#include <time.h>
#include <locale.h>
#include <Windows.h>

int main()
{
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	Generator gen;
	std::string fname("Generator");
	clock_t start = 0; clock_t before = 0; clock_t after = 0; double def;
	for (int j = 1; j <= 10; ++j) {
		fname += std::to_string(j) += ".txt";
		std::ofstream out(fname);
		before = clock();
		for (int i = 0; i < j*1000; ++i) {
			std::string a = gen.GenString();
			//std::cout << a << std::endl;
			out << a << "\n";
		}
		after = clock();
		def = (after - before) / CLOCKS_PER_SEC;
		std::cout << "Для генерации файла из " << j * 1000 << " строк понадобилось " << def  << " секунд" << std::endl;
		fname = "Generator";
	}
	std::cout << "Закончил" << std::endl;
	return 0;
}

