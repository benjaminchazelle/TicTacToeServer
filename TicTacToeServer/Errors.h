#ifndef ERRORSH
#define ERRORSH

#include <string>
#include <vector>

struct Error {
	int errorType;
	int errorNumber;
	std::string errorMessage;
};

class Errors
{
private:
	std::vector<Error> errors;

public:
	Errors(void);
	~Errors(void);

	Errors* addError(int errorType, int errorNumber, std::string errorMessage);
};

#endif;