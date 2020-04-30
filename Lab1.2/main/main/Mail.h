#pragma once
#include "mail_sm.h"
#include <vector>
class Mail
{
private:
	mailContext _fsm;
	bool isAcceptable;
	// If a string is acceptable, then this variable is set to YES;
	// NO, otherwise.
	int TextLen;
	//lhash log;
	//std::vector<char> name;
	std::string rec;
public:
	Mail();
	bool CheckString(const char*);
	// Checks if the string is acceptable.
	//bool CheckString(std::ifstream&);
	inline void Acceptable()
	{
		isAcceptable = true;
	};

	inline void Unacceptable()
	{
		isAcceptable = false;
	};
	// State map actions.
	inline bool TextL(int l) const
	{
		return l >= TextLen;
	};

	inline void TextR()
	{
		TextLen = 0;
	};

	inline void TextLInc()
	{
		TextLen++;
	}
	
	void NPush(char let)
	{
		//name.push_back(let);
		rec.push_back(let);
	}

	std::string getName() { return rec; }
	~Mail();
};

