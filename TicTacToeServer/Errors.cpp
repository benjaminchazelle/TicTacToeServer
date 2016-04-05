#include "Errors.h"


Errors::Errors(int _errorType) : errorType(_errorType)
{
}


Errors::~Errors(void)
{
}



Errors* Errors::addError(int errorNumber, std::string errorMessage) {

	Error error;
	error.errorNumber = errorNumber;
	error.errorMessage = errorMessage;

	this->errors.push_back(error);



	return this;

}

std::vector<Error> Errors::getErrors() {

	return this->errors;

}

int Errors::getErrorType() {
	return this->errorType;
}

bool Errors::isThereErrorNumber(int errorNumber) {

	for(std::vector<Error>::iterator it = this->errors.begin(); it!= this->errors.end(); ++it)
	{
		if((*it).errorNumber == errorNumber)
			return true;
	}

	return false;

};
