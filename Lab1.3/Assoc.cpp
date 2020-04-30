//#include "stdafx.h"
#include "Assoc.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
//#include "Mail.h"
#include "lex.yy.cc"
#include <ctime>
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
	if (!file.good()) throw std::runtime_error("Файл не найден");
	else {
		std::string buf; int fl=0;
		std::string a1 = fname;
		int pos = a1.find(".txt");
		a1.erase(pos, 4);
		a1 += "Log.txt";
		std::ofstream out(a1);
		std::string input;
		clock_t start = 0; clock_t before = 0; clock_t after = 0;
		yyFlexLexer ftp(&file, &std::cout);
		 do {
			std::cin.clear(); 
			bool res;
			before = clock();
			if (fl = ftp.yylex()) { res = true;  }
			else res = false;
			after = clock();
			start += (after - before);
			std::string ans;
			res ? ans = tr : ans = fa;
			out << buf << " : " << ans << "\r\n";
			//std::cout << buf << " : " << ans << std::endl;
			if (res && (fl!=2)) Add(ftp.YYText());
		 } while (!file.eof() && (fl != 2));
		out << "\r\n";
		out << "Статистика использования имен получателя (все ники приведены к нижнему регистру):" << "\r\n";
		auto it = pair.begin();
		for (; it != pair.end(); ++it) {
			out << it->first << " - " << it->second << "\r\n";
		}
		out << "Число тактов " << start << std::endl;
	}
	system("pause");
	return *this;
}


Assoc::~Assoc()
{
}
