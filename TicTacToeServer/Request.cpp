#include "Query/Request.h"
#include "Query/Response.h"

#include "Errors.h"
#include <sstream>
#include <iostream>
#include <regex>

Request::Request(void)
{

}



Request::~Request(void)
{
}

void Request::setIdentity(Server* server, setIdentityRequestQuery query) {

	setIdentityResponseQuery response;
	Errors errors(1);

	bool pseudoAvailable = server->getLogic()->isPseudoAvailable(query.pseudo);

	bool validPseudoFormat = std::regex_match (query.pseudo, std::regex("^[a-z0-9]+$"));

	if(!pseudoAvailable)
		errors.addError(1, "Pseudo unavailable");

	if(!validPseudoFormat)
		errors.addError(2, "Pseudo must respect the [a-z0-9]+ format");
	
	if(pseudoAvailable && validPseudoFormat) {

		query.sender->setName(query.pseudo);

		errors.addError(0, "Pseudo has been define with success");

	}

	response.clients = Response::unicastHelper(query.sender);
	response.pseudo = query.sender->getName();
	response.queryErrors = errors;

	std::cout << "*setIdentity" << std::endl;
}

void Request::getIdentity(Server* server, getIdentityRequestQuery query) {

	getIdentityResponseQuery response;
	Errors errors(2);

	errors.addError(0, "Obtention of the pseudo is a success");;

	response.clients = Response::unicastHelper(query.sender);;
	response.pseudo = query.sender->getName();
	response.queryErrors = errors;

	Response::getIdentity(server, response);

	std::cout << "*getIdentity" << std::endl;
}

void Request::createMatch(Server* server, createMatchRequestQuery query) {
	
	//Tester la taille de la grille

	//Tester la taille de la winsize, supérieur ou égale à 3, et que cette valeur soit possible à atteindre
	//Ex : dans une grille 3 x 3, on ne peut pas aligner 4 pions

	//Tester si les players sont valides, pseudos bien formatés...
	
	createMatchResponseQuery response;
	Errors errors(3);
	/*
	std::stringstream playersList_stream(query.playersList);
	std::string pseudo;


	while (std::getline(ss, item, '|')) {
		cout << item << endl;
	}*/
	/*
	bool validGridSize = query.gridWidth >= 3 && query.gridHeight >= 3;

	bool validWinSize = query.winSize >= 3 && query.winSize <= min(query.gridWidth, query.gridHeight);

	bool validParticipants = true;

	for(std::vector<std::string>::iterator it=query.playersList.begin();it != query.playersList.end();++it) {

		if(*it != "ANYBODY" && server->getLogic()->isPseudoAvailable(*it)) {
			validParticipants = false;
			break;
		}

	}

	if(!validGridSize)
		errors.addError(1, "Pseudo unavailable");

	if(!validPseudoFormat)
		errors.addError(2, "Pseudo must respect the [a-z0-9]+ format");
	
	if(pseudoAvailable && validPseudoFormat) {

		query.sender->setName(query.pseudo);

		errors.addError(0, "Pseudo has been define with success");

	}

	response.clients = Response::unicastHelper(query.sender);
	response.pseudo = query.sender->getName();
	response.queryErrors = errors;

	std::cout << "*setIdentity" << std::endl;*/

	//bool 
/*
	bool pseudoAvailable = server->getLogic()->isPseudoAvailable(query.pseudo);

	bool validPseudoFormat = std::regex_match (query.pseudo, std::regex("^[a-z0-9]+$"));

	if(!pseudoAvailable)
		errors.addError(1, "Pseudo unavailable");

	if(!validPseudoFormat)
		errors.addError(2, "Pseudo must respect the [a-z0-9]+ format");
	
	if(pseudoAvailable && validPseudoFormat) {

		query.sender->setName(query.pseudo);

		errors.addError(0, "Pseudo has been define with success");

	}

	response.clients = Response::unicastHelper(query.sender);
	response.pseudo = query.sender->getName();
	response.queryErrors = errors;
	*/
	std::cout << "*createMatch" << std::endl;
}

void Request::getMatchList(Server* server, getMatchListRequestQuery query) {

	//Aucun test

	std::cout << "*getMatchList" << std::endl;
}

void Request::getMatchInformation(Server* server, getMatchInformationRequestQuery query) {

	//Tester si le match existe

	std::cout << "*getMatchInformation" << std::endl;
}

void Request::joinMatch(Server* server, joinMatchRequestQuery query) {

	//Tester si le match existe

	//Tester si le mode de suivit existe "PLAYER" ou "SPECTATOR"

	//Tester si le joueur est invité dans la partie

	//Tester si il y a assez dez place dans la partie (dans le cas où l'utilisateur pouvait rejoindre la partie?)

	std::cout << "*joinMatch" << std::endl;
}

void Request::playMatch(Server* server, playMatchRequestQuery query) {

	//Tester si la partie est finie

	//Tester si c'est le tour du joueur

	//Tester si les coordonnées sont valides, comprises dans le plateau ...

	//Tester si la case est occupée

	std::cout << "*playMatch" << std::endl;
}

void Request::resetMatch(Server* server, resetMatchRequestQuery query) {

	//Tester si le match existe

	std::cout << "*resetMatch" << std::endl;
}

void Request::quitMatch(Server* server, quitMatchRequestQuery query) {

	//Tester si le match existe

	std::cout << "*quitMatch" << std::endl;
}

void Request::getPlayerInformation(Server* server, getPlayerInformationRequestQuery query) {
	
	//Tester si le pseudo est au bon format

	//Tester si le joueur existe

	std::cout << "*getPlayerInformation" << std::endl;
}