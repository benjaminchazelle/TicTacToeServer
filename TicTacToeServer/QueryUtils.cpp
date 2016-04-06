#include "QueryUtils.h"
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include "Errors.h"

class Errors;

std::string QueryUtils::getLine(std::string &buffer){

	int delimiterPosition = buffer.find("\r\n");

	std::string gotLine = buffer.substr(0,delimiterPosition);

	buffer = buffer.substr(delimiterPosition+2);

	return gotLine;
}

bool QueryUtils::headerParsing(std::string &buffer){

	std::string line = QueryUtils::getLine(buffer);

	return line == "TICTACTOE/1.0";
}

ParsedEntity<std::string> QueryUtils::getStringParsing(std::string &buffer){

	ParsedEntity<std::string> parsedEntity;
	parsedEntity.error = true;

	std::string line = QueryUtils::getLine(buffer);

	int delimiterPosition = line.find(": ");

	if(delimiterPosition != -1) {

		parsedEntity.error = false;

		parsedEntity.key = line.substr(0,delimiterPosition);
		parsedEntity.value = line.substr(delimiterPosition+2);

	}

	return parsedEntity;
}

ParsedEntity<int> QueryUtils::getIntParsing(std::string &buffer){

	ParsedEntity<std::string> parsedStringEntity = QueryUtils::getStringParsing(buffer);

	ParsedEntity<int> parsedEntity;

	if(parsedStringEntity.error) {
		parsedEntity.error = true;
		return parsedEntity;
	}

	parsedEntity.error = false;
	parsedEntity.key = parsedStringEntity.key;

	char* p;
	long converted = strtol(parsedStringEntity.value.c_str(), &p, 10);

	if (*p) {
		parsedEntity.value = -1;
	}
	else {
		parsedEntity.value = converted;
	}

	return parsedEntity;
}

ParsedEntity<bool> QueryUtils::getBoolParsing(std::string &buffer) {

	ParsedEntity<std::string> parsedStringEntity = QueryUtils::getStringParsing(buffer);

	ParsedEntity<bool> parsedEntity;

	if(parsedStringEntity.error && (parsedStringEntity.value != "0" && parsedStringEntity.value != "1")) {
		parsedEntity.error = true;
		return parsedEntity;
	}

	parsedEntity.error = false;
	parsedEntity.key = parsedStringEntity.key;
	parsedEntity.value = parsedStringEntity.value == "1";

	return parsedEntity;
}

ParsedEntity<std::vector<std::string>> QueryUtils::getPseudoPlayersParsing(std::string &buffer) {

	ParsedEntity<std::string> parsedStringEntity = QueryUtils::getStringParsing(buffer);

	ParsedEntity<std::vector<std::string>> parsedEntity;

	if(parsedStringEntity.error) {
		parsedEntity.error = true;
		return parsedEntity;
	}

	parsedEntity.error = false;
	parsedEntity.key = parsedStringEntity.key;

	std::stringstream ss(parsedStringEntity.value);
	std::string item;
	while (std::getline(ss, item, '|')) {
		parsedEntity.value.push_back(item);
	}

	return parsedEntity;

}
/*
void QueryUtils::nextLine(std::string &line) {

};*/


void QueryUtils::headerBuilding(std::string &response) {

	response += "TICTACTOE/1.0\r\n";

}

void QueryUtils::setValue(std::string &response, std::string key, std::string value) {

	response += key + ": " + value + "\r\n";

}

void QueryUtils::setValue(std::string &response, std::string key, int value) {

	std::stringstream int_stream;

	int_stream << value;

	QueryUtils::setValue(response, key, int_stream.str());

}

void QueryUtils::setErrors(std::string &response, Errors errors) {

	std::stringstream errorCode_stream;
	errorCode_stream << errors.getErrorType() << "-" ;

	std::vector<Error> errorsList = errors.getErrors();

	unsigned int errorsNumber = errorsList.size();

	if(errorsNumber == 0) {
		setValue(response, "ErrorCode", "?");
		setValue(response, "ErrorMessage", "If you see this message, it means the developer is only stupid.");
		return;
	}


	for(std::vector<Error>::iterator it=errorsList.begin(); it!=errorsList.end(); ++it) {

		if(errorsNumber > 1)
			errorCode_stream << "+";

		errorCode_stream << it->errorNumber;

	}

	setValue(response, "ErrorCode", errorCode_stream.str());
	
	if(errorsNumber == 1) {
		setValue(response, "ErrorMessage", errorsList.at(0).errorMessage);
	}
	else {

		for(std::vector<Error>::iterator it=errorsList.begin(); it!=errorsList.end(); ++it) {

			std::stringstream errorMessage_stream;
			errorMessage_stream << "#" << it->errorNumber << " " << it->errorMessage;

			setValue(response, "ErrorMessage", errorMessage_stream.str());

		}

	}

}

void QueryUtils::footerBuilding(std::string &response) {

	response += "\r\n\r\n";

}