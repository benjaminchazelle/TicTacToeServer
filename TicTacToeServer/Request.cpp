#include "Query/Request.h"
#include "Query/Response.h"

#include <iostream>

Request::Request(void)
{

}


Request::~Request(void)
{
}

void Request::setIdentity(Server* server, setIdentityRequestQuery query) {
	std::cout << "*setIdentity" << std::endl;
}

void Request::getIdentity(Server* server, getIdentityRequestQuery query) {

	getIdentityResponseQuery response;

	std::vector<Player*> clientsTarget;
	clientsTarget.push_back(query.sender);

	std::vector<Error> errors;
	Error ok_error;
	ok_error.errorMessage = "heloo world";
	ok_error.errorNumber = 462;
	ok_error.errorType = 472;


	response.clients = clientsTarget;
	response.pseudo = query.sender->getName();
	response.queryErrors = errors;

	Response::getIdentity(server, response);

	std::cout << "*getIdentity" << std::endl;
}

void Request::createMatch(Server* server, createMatchRequestQuery query) {
	std::cout << "*createMatch" << std::endl;
}

void Request::getMatchList(Server* server, getMatchListRequestQuery query) {
	std::cout << "*getMatchList" << std::endl;
}

void Request::getMatchInformation(Server* server, getMatchInformationRequestQuery query) {
		std::cout << "*getMatchInformation" << std::endl;
}

void Request::joinMatch(Server* server, joinMatchRequestQuery query) {
		std::cout << "*joinMatch" << std::endl;
}

void Request::playMatch(Server* server, playMatchRequestQuery query) {
		std::cout << "*playMatch" << std::endl;
}

void Request::resetMatch(Server* server, resetMatchRequestQuery query) {
	std::cout << "*resetMatch" << std::endl;
}

void Request::quitMatch(Server* server, quitMatchRequestQuery query) {
	std::cout << "*quitMatch" << std::endl;
}

void Request::getPlayerInformation(Server* server, getPlayerInformationRequestQuery query) {
	std::cout << "*getPlayerInformation" << std::endl;
}