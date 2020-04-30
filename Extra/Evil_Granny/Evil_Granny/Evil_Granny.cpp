// EvilGranny.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <regex>
#include <string>
#include <iostream>
#include <locale>
#include <fstream>

int ReadFromFile(const std::string&, const std::regex&, std::ofstream&, int type);

int main()
{
	setlocale(LC_ALL, "Rus");
	std::string mail = "(\\w+\\s*(@|\\(at\\))\\s*(\\w+\\s*(\\.|dot)\\s*)*\\s*\\w+)";
	//std::string telephone = "(\\+\\d{2}\\(\\d{3}\\)\\d{3}-\\d{2}-\\d{2})";
	//std::string mail = "[-a-z0-9!#$%&'*+/=?^_`{|}~]+((\\.|dot)[-a-z0-9!#$%&'*+/=?^_`{|}~]+)*\\s*(@|\\(?\\s*at\\s*\\)?)\\s*([a-z0-9]([-a-z0-9]{0,61}[a-z0-9])\\s*?(\\.|dot)\\s*)*(aero|arpa|asia|biz|cat|com|coop|edu|gov|info|int|jobs|mil|mobi|museum|name|net|org|pro|tel|travel|[a-z][a-z])";
	
	//std::string mail = "((?(?[\\d\\w~](?\\.|dot)?)+)|(?\"(?(?[\\s\\d\\w~](?\\.|dot)?)+)\"))\\s*\\)\\s*(@|at)\\s*((?.)\\.\\s*((?\\w\\d~)(?(?\\.|\\s*dot\\s*))(?\\w\\d~))*)";
	std::string telephone = "(\\s*)?(\\+)?([- _():=+]?\\d[- _():=+]?){10,14}";
	//std::string regular = mail + "|" + telephone;
	std::smatch victor;
	std::regex reg1(mail, std::regex::icase);
	std::regex reg2(telephone, std::regex::icase);
	std::string buf;
	std::ifstream INPUT("Input");
	std::ofstream OUTPUT("OUT_File_Spam_LORD");
	while (std::getline(INPUT, buf)) {
		ReadFromFile(buf, reg1, OUTPUT, 1);
		ReadFromFile(buf, reg2, OUTPUT, 2);

	}
	return 0;
}

int ReadFromFile(const std::string& fname, const std::regex& reg1, std::ofstream& out, int type) {
	std::ifstream file(fname);
	std::string buf;
	out << "Файл " << fname << std::endl;
	if (file.good()) {
		while (std::getline(file, buf)) {
			for (std::sregex_iterator it(buf.begin(), buf.end(), reg1), end_it; it != end_it; ++it) {
				std::string mail = it->str();
				if (type == 1) {
					std::regex repa("at|\\(\\s*at\\s*\\)", std::regex::icase);
					std::string dog("@");
					mail = std::regex_replace(mail, repa, dog);
					std::regex rpoint("dot|\\s*dot\\s*", std::regex::icase);
					std::string point(".");
					mail = std::regex_replace(mail, rpoint, point);
					for (std::string::iterator it = mail.begin(); it < mail.end(); ++it) {
						if ((*it == ' ') || (*it == '\t'))	mail.erase(it);
					}
					std::string suf = it->suffix();
					if ((suf[0] != ' ') && (suf[0] != '\t') && (suf[0] != '\0') && (suf[0]) != '\'' && (suf[0] != '\"')) {
						mail.erase((mail.end() - 3), mail.end());
					}
				}
				out << "Полученное : " << mail << std::endl;
			}
		}
	}
	return 1;
}


