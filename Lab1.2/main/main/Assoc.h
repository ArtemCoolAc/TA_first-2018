#pragma once
#include <map>
#include <string>
class Assoc
{
private:
	std::map<std::string, int> pair;
public:
	Assoc();
	void Add(const char* a);
	void Add(const std::string& a);
	Assoc& ReadFromFile(const std::string& fname);
	friend std::ostream& operator << (std::ostream& os, Assoc& assoc);
	~Assoc();
};

