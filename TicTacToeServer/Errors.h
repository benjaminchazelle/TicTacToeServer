#ifndef ERRORSH
#define ERRORSH

#include <string>
#include <vector>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////Classe permettant de g�rer les erreurs dans la r�ponse du serveur au client//////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
	std::vector<Error> getErrors();

	bool isThereErrorNumber(int errorNumber);
};

#endif