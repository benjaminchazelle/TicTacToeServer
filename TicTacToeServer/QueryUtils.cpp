#include "QueryUtils.h"
#include <string>
#include <sstream>
#include <vector>
#include <iostream>



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