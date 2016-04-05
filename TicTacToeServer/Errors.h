#ifndef ERRORSH
#define ERRORSH

#include <string>
#include <vector>

struct Error {
	int errorNumber;
	std::string errorMessage;
};

class Errors
{
private:
	std::vector<Error> errors;

	int errorType;

public:
	Errors(int errorType=-1);
	~Errors(void);

	Errors* addError(int errorNumber, std::string errorMessage);

	int getErrorType();
	std::vector<Error> Errors::getErrors();

	bool isThereErrorNumber(int errorNumber);
};

#endif;