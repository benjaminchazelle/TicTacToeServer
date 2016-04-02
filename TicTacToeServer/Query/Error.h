#ifndef ERRORH
#define ERRORH

#include <string>

struct Error {
	int errorType;
	int errorNumber;
	std::string errorMessage;
};


#endif