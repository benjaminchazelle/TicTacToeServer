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

	Response::setIdentity(server, response);

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

	Response::createMatch(server, response);

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

	Match* match =  server->getLogic()->getMatchsList()[query.match] ;

	bool matchExists = match != nullptr;

	if(!matchExists) {
		errors.addError(1, "Match does not exist");

	}
	else {
		errors.addError(0, "Information about the game have been fetch successfuly");

		response.match = match;
	}

	response.clients = Response::unicastHelper(query.sender);

	response.queryErrors = errors;

	Response::getMatchInformation(server, response);

	std::cout << "*getMatchInformation" << std::endl;
}

void Request::joinMatch(Server* server, joinMatchRequestQuery query) {

	joinMatchResponseQuery response;
	Errors errors(6);

	Match* match = server->getLogic()->getMatchsList()[query.match];

	bool matchExists = match != nullptr;

	bool isPlayerMode = query.mode == "PLAYER";
	bool validMode = isPlayerMode || query.mode == "SPECTATOR";

	if(!matchExists) {
		errors.addError(1, "Match does not exist");
	}
	else {

		if(!validMode) {
			errors.addError(2, "Incorrect mode");
		}
		else {

			response.isPlayerMode = isPlayerMode;
			response.match = match;

			if(isPlayerMode) {

				Status matchInvitationStatus = query.sender->acceptMatchInvitation(match);

				if(matchInvitationStatus == Status::MATCH_USER_ACCEPTED)
					errors.addError(0, "You have join the match");
				if(matchInvitationStatus == Status::MATCH_USER_ALREADY_INNER)
					errors.addError(3, "You are already in this match");
				else if(matchInvitationStatus == Status::MATCH_NOT_INVITED)
					errors.addError(4, "You are not invited in this match or unassigned place taken");
				else if(matchInvitationStatus == Status::MATCH_EVER_STARTED_OR_FINISHED)
					errors.addError(5, "The match ever started or finished");

			}
			else {


				match->addSpectator(query.sender);

				

				errors.addError(0, "You have join the match");

			}


		}

	}

	response.clients = Response::unicastHelper(query.sender);

	response.queryErrors = errors;


	Response::joinMatch(server, response);

	std::cout << "*joinMatch" << std::endl;
}

void Request::playMatch(Server* server, playMatchRequestQuery query) {

	playMatchResponseQuery response;
	Errors errors(7);

	Match* match = server->getLogic()->getMatchsList()[query.match];

	bool matchExists = match != nullptr;

	if(!matchExists) {

		errors.addError(1, "Match does not exist");

	}
	else {



		Status strokeStatus = match->play(query.sender, query.coordinate_x, query.coordinate_y);

		switch(strokeStatus){

		case MATCH_STROKE_DONE:
			errors.addError(0, "Your move have been done with success");
			break;

		case MATCH_NOT_STARTED:
			errors.addError(4, "The game is not in progress");
			break;

		case MATCH_PLAYER_IS_NOT_PARTICIPANT:
			errors.addError(6, "You are not in the match");
			break;

		case MATCH_NOT_PLAYED_BY_CURRENT_PLAYER:
			errors.addError(5, "This is not your turn");
			break;

		case MATCH_INCORRECT_STROKE:
			errors.addError(2, "Coordinates are incorrect");
			break;

		default:

			errors.addError(3, "You can not play on this case");
		}

	}

	response.clients = Response::unicastHelper(query.sender);

	response.queryErrors = errors;

	Response::playMatch(server, response);

	//Tester si la partie est finie

	//Tester si c'est le tour du joueur

	//Tester si les coordonnées sont valides, comprises dans le plateau ...

	//Tester si la case est occupée

	std::cout << "*playMatch" << std::endl;
}

void Request::resetMatch(Server* server, resetMatchRequestQuery query) {

	resetMatchResponseQuery response;
	Errors errors(8);

	Match* match = server->getLogic()->getMatchsList()[query.match];

	bool matchExists = match != nullptr;

	if(!matchExists) {
		errors.addError(1, "Match does not exist");

	}
	else {

		Status resetMacthStatus = match->resetMatch(query.sender);
		
		switch(resetMacthStatus) {

		case MATCH_RESETED:
			response.match = match;
			errors.addError(0, "Restart of the game have been done");
			break;

		case MATCH_PLAYER_IS_NOT_PARTICIPANT:
			errors.addError(2, "You are not is the match");
			break;

		case WAITING_PLAYERS:
			errors.addError(1, "The match ever started or finished");
			break;

		}


		response.match = server->getLogic()->getMatchsList()[query.match];
	}

	response.clients = Response::unicastHelper(query.sender);

	response.queryErrors = errors;

	Response::resetMatch(server, response);


	std::cout << "*resetMatch" << std::endl;
}

void Request::quitMatch(Server* server, quitMatchRequestQuery query) {

	quitMatchResponseQuery response;
	Errors errors(9);

	Match* match = server->getLogic()->getMatchsList()[query.match];

	bool matchExists = match != nullptr;

	if(!matchExists) {
		errors.addError(1, "Match does not exist");

	}
	else {

		Status resetMacthStatus = match->resetMatch(query.sender);
		
		switch(resetMacthStatus) {

		case MATCH_DESERTED:
			errors.addError(0, "You have quit the game … Bad Looser!");
			break;

		case MATCH_PLAYER_IS_NOT_PARTICIPANT:
			errors.addError(2, "You are not is the match");
			break;

		case MATCH_PLAYER_ALREADY_DESERTED:
			errors.addError(3, "You have already desert the match");
			break;

		}

		response.match = match;
	}

	response.clients = Response::unicastHelper(query.sender);

	response.queryErrors = errors;

	Response::quitMatch(server, response);

	std::cout << "*quitMatch" << std::endl;
}

void Request::getPlayerInformation(Server* server, getPlayerInformationRequestQuery query) {

	getPlayerInformationResponseQuery response;
	Errors errors(10);

	Player* player = server->getLogic()->getPlayer(query.player);;

	bool playersExists = player != nullptr;

	bool validPseudoFormat = std::regex_match (query.player, std::regex("^[a-z0-9]+$"));

	if(!playersExists)
		errors.addError(1, "The player does not exist");

	if(!validPseudoFormat)
		errors.addError(2, "Bad syntax of the player’s pseudo");

	if(playersExists && validPseudoFormat) {

		response.player = player;

		errors.addError(0, "You have access to your information");

	}

	response.clients = Response::unicastHelper(query.sender);
	response.queryErrors = errors;

	Response::getPlayerInformation(server, response);

	std::cout << "*getPlayerInformation" << std::endl;
}

void Request::nonSense(Server* server, RequestQuery query) {

	ServerQuery response;
	response.clients =  Response::unicastHelper(query.sender);

	Response::genericError(server, response);

}