#include "Errors.h"


Errors::Errors(void)
{
}


Errors::~Errors(void)
{
}



Errors* Errors::addError(int errorType, int errorNumber, std::string errorMessage) {

	Error error;
	error.errorType = errorType;
	error.errorNumber = errorNumber;
	error.errorMessage = errorMessage;

	this->errors.push_back(error);

	return this;

}

