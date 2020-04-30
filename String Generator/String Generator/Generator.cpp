#include "stdafx.h"
#include "Generator.h"
#include <time.h>
#include <regex>
using std::string;
using std::vector;
const std::string expr = "^(mailto:)([a-z0-9]+)(@)([a-z0-9]+)(\\.)([a-z]+)([?]subject=)([a-z0-9]){0,64}$";
Generator::Generator()
{
}

void Generator::Create(int quantity)
{

}

std::string Generator::MakeString()
{
	 string buf; string res;
		string mas = "mailto";
		for (int i = 0; i < 6; ++i) {
			int regist = rand() % 2;
			if (regist) mas[i] -= 32;
		}
		mas += ":";
		res += mas;
		int len = rand() % 20 + 1;
		buf = GenGroup(len, true);
		res += buf;
		buf.clear();
		res += "@";
		len = rand() % 20 + 1;
		buf = GenGroup(len, true);
		res += buf;
		buf.clear();
		res += ".";
		len = rand() % 20 + 1;
		buf = GenGroup(len, false);
		res += buf;
		buf.clear();
		res += "?";
		mas.clear();
		mas = "subject";
		for (int i = 0; i < 7; ++i) {
			int regist = rand() % 2;
			if (regist) mas[i] -= 32;
		}
		res += mas;
		res += "=";
		int option = rand() % 2;
		if (option) {
			len = rand() % 64 + 1;
			buf = GenGroup(len, true);
			res += buf;
			buf.clear();
		}
	return res;
}

std::string Generator::GenString()
{	
	string buf; string res;
	string correct = MakeString();
	int correctness = rand() % 2;
	if (correctness) {
		res = correct;
	}
	else {
		int GroupName = rand() % 9;
		res = Change(correct, GroupName);
	}
	positions.clear();
	return res;
}

std::string Generator::GenGroup(int len, bool dig)
{
	string a;
	if (!dig) {
		for (int i = 0; i < len; ++i) {
			char bukva = Letter();
			a += bukva;
		}
	}
	else {
		for (int i = 0; i < len; ++i) {
			int LetDig = rand() % 2;
			if (LetDig) {
				char bukva = Letter();
				a += bukva;
			}
			else {
				a += Digit();
			}
		}
	}
	return a;
}

string Generator::Digit()
{
	int digit = rand() % 10;
	string a = std::to_string(digit);
	return a;
}

char Generator::Letter()
{
	char bukva = rand() % 26 + 65;
	int regist = rand() % 2;
	if (regist) bukva += 32;
	return bukva;
}

string Generator::Change(std::string& a, int num)
{
	char falseSymb = rand() % 13 + 33;  // генерит левый символ аля # $ % ^ & и т.д.
	if (num != 2 && num != 4 && num != 8) {
		int digOrLeft = rand() % 2;
		if (digOrLeft) falseSymb = rand() % 10 + 48;
	}

	std::string buf; std::string fig;
	fig = falseSymb;
	std::smatch m;
	std::regex reg(expr, std::regex::icase);
	std::regex_match(a, m, reg); // выделяет все группы строки

	int summ = 0; int fl = 1;
	if (positions.empty()) {
		for (auto & iter : m) {  // пробегаем итератором по smatch и записываем в свой вектор начальные позиции каждой группы в исходной строке		 
			positions.push_back(summ);
			summ += iter.length();
			if (fl) { summ = 0; fl = 0; }
		}
	}
	buf = m[num]; // строка выбранной рандомом группы
	int len = buf.length();
	if (len) {
	int pos = rand() % len; // место, где возникнет ошибка
	int ChangeOrInsert = rand() % 2; // ВБР выбирает, изменяем ли элемент в строке или вставим новый в эту позицию
	if (ChangeOrInsert) {
		buf[pos] = fig[0];
	}
	else {
		buf.insert(pos, fig);
	}
	int startPos = positions[num];
	a.replace(startPos, len, buf);
	}
	int lllen;
	if ((num == 8) && (lllen = m[8].length())) {
		int tooLongOrNot = rand() % 2; // в последней группе ВБР решает, будет ли она длиннее 64 символов
		if (tooLongOrNot) {
			int restToAdd = 64 - lllen;
			int ToAdd = rand() % 50 + restToAdd;
			string Additive;
			for (int i = 0; i < ToAdd; ++i) {
				Additive += Letter();
			}
		}
	}
	return a;
}

Generator::~Generator()
{
}
