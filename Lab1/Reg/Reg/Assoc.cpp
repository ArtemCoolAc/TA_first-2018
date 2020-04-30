#include "stdafx.h"
#include "Assoc.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
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
	std::string buf;
	std::string a1 = fname;
	int pos = a1.find(".txt");
	a1.erase(pos, 4);
	a1 += "Log.txt";
	std::ofstream out(a1);
	if (!file.good()) throw std::exception("Файл не найден");
	else {
		//file.open(fname);
		std::string input;
		const std::string expr = "^mailto:([a-z0-9]+)@([a-z0-9]+)\\.([a-z]+)[?]subject=([a-z0-9]){0,64}$";
		//const std::string expr = "(m|M)(a|A)(i|I)(l|L)(t|T)(o|O):[[:alnum:]]+@[[:alnum:]]+\\.[[:alpha:]]+\\?(s|S)(u|U)(b|B)(j|J)(e|E)(c|C)(t|T)=[[:alnum:]]{0,64}";
		std::smatch m;
		std::regex reg(expr, std::regex::icase);
		clock_t start = 0; clock_t before = 0; clock_t after = 0;
		while (std::getline(file, buf)) {
			before = clock();
			bool res = std::regex_match(buf, m, reg);
			after = clock();
			start += (after - before);
			std::string ans;
			res ? ans = tr : ans = fa;
			out << buf << " : " << ans << "\n";
			//std::cout << buf << " : " << ans << std::endl;
			if (res) Add(m[1]);
		}
		std::cout << "Прошло временных тактов " << start << std::endl;
		out << "\n";
		out << "Статистика использования имен получателя (все ники приведены к нижнему регистру):" << "\n";
		auto it = pair.begin();
		for (; it != pair.end(); ++it) {
			out << it->first << " - " << it->second << "\n";
		}
		out << "Прошло временных тактов " << start << std::endl;
	}
	return *this;
}

Assoc::~Assoc()
{
}
