#include "stdafx.h"
#include "Assoc.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include "Mail.h"
#include <time.h>
const std::string tr = "корректная";
const std::string fa = "инвалид";

Assoc::Assoc()
{
}

void Assoc::Add(const std::string& a)
{
	std::string b = a;
	std::transform(b.begin(), b.end(), b.begin(), tolower);
	auto it = pair.find(b);
	if (it != pair.end()) ++(it->second);
	else {
		std::pair<std::string, int> elem(b, 1);
		pair.insert(elem);
	}
}

void Assoc::Add(const char* a)
{
	std::string b(a);
	Add(b);
}

std::ostream& operator << (std::ostream& os, Assoc& assoc)
{
	auto it = assoc.pair.begin();
	for (; it != assoc.pair.end(); ++it) {
		os << it->first << " - " << it->second << std::endl;
	}
	return os;
}

Assoc& Assoc::ReadFromFile(const std::string& fname)
{
	std::ifstream file(fname);
	if (!file.good()) throw std::exception("Файл не найден");
	else {
		std::string buf;
		std::string a1 = fname;
		int pos = a1.find(".txt");
		a1.erase(pos, 4);
		a1+="Log.txt";
		std::ofstream out(a1);
		std::string input;
		clock_t start = 0; clock_t before = 0; clock_t after = 0;
		while (std::getline(file, buf)) {
			const char* copy = buf.c_str();
			Mail thisContext;
			before = clock();
			bool res = thisContext.CheckString(copy);
			after = clock();
			start += (after - before);
			std::string ans;
			res ? ans = tr : ans = fa;
			out << buf << " : " << ans << "\n";
			//std::cout << buf << " : " << ans << std::endl;
			if (res) Add(thisContext.getName());
		}
		std::cout << "Количество временных тактов " << start << std::endl;
		out << "\n";
		out << "Статистика использования имен получателя (все ники приведены к нижнему регистру):" << "\n";
		out << "Количество временных тактов равно " << start << std::endl;
		auto it = pair.begin();
		for (; it != pair.end(); ++it) {
			out << it->first << " - " << it->second << "\n";
		}
	}
	return *this;
}

Assoc::~Assoc()
{
}
