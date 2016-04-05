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

	//Tester la taille de la winsize, sup�rieur ou �gale � 3, et que cette valeur soit possible � atteindre
	//Ex : dans une grille 3 x 3, on ne peut pas aligner 4 pions

	//Tester si les players sont valides, pseudos bien format�s...
	
	createMatchResponseQuery response;
	Errors errors(3);

	
	bool validGridSize = query.gridWidth >= 3 && query.gridHeight >= 3;

	bool validWinSize = query.winSize >= 3 && query.winSize <= min(query.gridWidth, query.gridHeight);

	bool validParticipants = true;

	std::vector<Participant> participantsList;

	for(std::vector<std::string>::iterator it=query.playersList.begin();it != query.playersList.end();++it) {

		Player* player = server->getLogic()->getPlayer(*it);

		Participant participant;

		if(*it == "ANYBODY") {
	
			participant.player = nullptr;
			participant.state = ParticipantState::INVITED_ANYONE;
		}
		else if(player != nullptr) {
			participant.player = player;
			participant.state = ParticipantState::INVITED_PLAYER;
		}
		else {
			validParticipants = false;
			break;
		}

		participantsList.push_back(participant);
		
	}

	if(!validParticipants)
		errors.addError(1, "Invalid pseudo in the player list");

	if(!validGridSize)
		errors.addError(2, "Grid size out of range [3,9]");

	if(!validGridSize)
		errors.addError(3, "Pion number for win must be an integer greather than  or equal to 3 and lesser than the minimum grid dimension");

	if(validParticipants && validGridSize && validGridSize) {

		response.match = server->getLogic()->addMatch(query.gridWidth, query.gridHeight, query.winSize, participantsList);

		errors.addError(0, "Match successfuly created");

	}

	response.clients = Response::unicastHelper(query.sender);
	response.queryErrors = errors;


	std::cout << "*createMatch" << std::endl;
}

void Request::getMatchList(Server* server, getMatchListRequestQuery query) {

	//Aucun test

	getMatchListResponseQuery response;
	Errors errors(4);

	errors.addError(0, "The obtention of the list of matchs is a success");

	response.matchesList = server->getLogic()->getMatchsList();

	response.clients = Response::unicastHelper(query.sender);

	response.queryErrors = errors;

	Response::getMatchList(server, response);

	std::cout << "*getMatchList" << std::endl;
}

void Request::getMatchInformation(Server* server, getMatchInformationRequestQuery query) {


	//Tester si le match existe

	getMatchInformationResponseQuery response;
	Errors errors(5);

	bool matchExists = server->getLogic()->getMatchsList()[query.match] != nullptr;

	if(!matchExists) {
		errors.addError(1, "Match does not exist");

	}
	else {
		errors.addError(0, "Information about the game have been fetch successfuly");

		response.match = server->getLogic()->getMatchsList()[query.match];
	}

	response.clients = Response::unicastHelper(query.sender);

	response.queryErrors = errors;

	Response::getMatchInformation(server, response);

	std::cout << "*getMatchInformation" << std::endl;
}

void Request::joinMatch(Server* server, joinMatchRequestQuery query) {

	//Tester si le match existe

	//Tester si le mode de suivit existe "PLAYER" ou "SPECTATOR"

	//Tester si le joueur est invit� dans la partie

	//Tester si il y a assez dez place dans la partie (dans le cas o� l'utilisateur pouvait rejoindre la partie?)

	std::cout << "*joinMatch" << std::endl;
}

void Request::playMatch(Server* server, playMatchRequestQuery query) {

	//Tester si la partie est finie

	//Tester si c'est le tour du joueur

	//Tester si les coordonn�es sont valides, comprises dans le plateau ...

	//Tester si la case est occup�e

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