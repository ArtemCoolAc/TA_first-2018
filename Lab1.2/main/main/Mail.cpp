#include "stdafx.h"
#include "Mail.h"
#include <string>

Mail::Mail() : _fsm(*this), isAcceptable(false), TextLen(0)
{
}

bool Mail::CheckString(const char* theString)
{
	_fsm.enterStartState();
	while (*theString != '\0')
	{
		if ((*theString >= 'A' && *theString <= 'Z') || (*theString >= 'a' && *theString <= 'z')) {
			_fsm.letter(*theString);
			++theString;
		}
		else {
			if (*theString >= '0' && *theString <= '9') {
				_fsm.digit(*theString);
				++theString;
			}
			else {
				switch (*theString) {

				case ('?'): {
					_fsm.qmark();
					++theString;
					break;
				}
				case ('.'): {
					_fsm.point();
					++theString;
					break;
				}
				case ('@'): {
					_fsm.at();
					++theString;
					break;
				}
				case (':'): {
					_fsm.tdot();
					++theString;
					break;
				}
				case ('='): {
					_fsm.eq();
					++theString;
					break;
				}
				default: {
					_fsm.Unknown();
					++theString;
					break;
				}

				}
			}
		}
		
	}

	// end of string has been reached - send the EOS transition.
	_fsm.EOS();
	return isAcceptable;
}


Mail::~Mail()
{
}
