#pragma once
#include <string>
#include <vector>
class Generator
{
private:
	std::vector<int> positions;
	int made;

public:
	Generator();
	void Create(int quantity);
	std::string MakeString();
	std::string GenString();
	std::string GenGroup(int length, bool digits);
	std::string Digit();
	char Letter();
	std::string Change(std::string& changeable, int num);
	~Generator();
};

