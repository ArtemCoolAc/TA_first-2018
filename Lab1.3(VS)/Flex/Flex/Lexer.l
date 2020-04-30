%option noyywrap
%option c++
%x RECEIVER TAIL
%%
<INITIAL>{
^(?i:mailto:) {BEGIN(RECEIVER);}
\n {return 0;}
. {};
<<EOF>> {return 2;}
}
<RECEIVER>{
(?i:[a-zA-Z0-9]+)/(?i:@([a-zA-Z0-9])+\.([a-zA-Z]+)\?subject=([a-zA-Z0-9]{0,64})\r?\n) {BEGIN(TAIL); return 1;}
. {BEGIN(INITIAL);}
\n {BEGIN(INITIAL); return 0;}

}
<TAIL>
{
. {};
\n {BEGIN(INITIAL);}
}
%%

#include <iostream>
#include <string>
#include "Assoc.h"
int main()
{
	std::cout<<"Хотите чтение из файла?"<<std::endl;
	std::cout<<"0.Нет"<<std::endl;
	std::cout<<"1.Да"<<std::endl;
	
	Assoc stat;
	int ch;
	std::cin>>ch;
	if (ch) {
		std::cout<<"Введите имя файла"<<std::endl;
		std::string fname;
		std::cin>>fname;
		stat.ReadFromFile(fname);
	}
	else { 
		yyFlexLexer ftp;
		while (std::cin.good()) {
			std::cout<<"Введите строчку"<<std::endl;
		if (ftp.yylex())
		std::cout<<"Строка хорошая. Имя получателя : "<<ftp.YYText()<<std::endl;
		else std::cout<<"Плохая строчка"<<std::endl;
		}
	}	
	return 0;
}