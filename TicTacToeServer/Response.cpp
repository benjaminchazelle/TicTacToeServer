#include "Server.h"
#include "Query/Response.h"
#include "Query/ServerQuery.h"
#include "QueryUtils.h"
#include "Player.h"
#include "Match.h"
#include <sstream>
#include "Query/Notify.h"

void Response::getIdentity(Server* server, getIdentityResponseQuery query) {

	std::string response = "";

	QueryUtils::headerBuilding(response);

	QueryUtils::setValue(response, "Response", "getIdentity");

	if (query.queryErrors.getErrors().size() == 1 && query.queryErrors.getErrors().at(0).errorNumber == 0){

		QueryUtils::setValue(response, "Pseudo", query.pseudo);

	}

	QueryUtils::setErrors(response, query.queryErrors);

	QueryUtils::footerBuilding(response);

	server->sendTo(response, query.clients);

}

void Response::setIdentity(Server* server, setIdentityResponseQuery query){

	std::string response = "";

	QueryUtils::headerBuilding(response);

	QueryUtils::setValue(response, "Response", "setIdentity");

	if (query.queryErrors.getErrors().size() == 1 && query.queryErrors.getErrors().at(0).errorNumber == 0){

		QueryUtils::setValue(response, "Pseudo", query.pseudo);

	}

	QueryUtils::setErrors(response, query.queryErrors);

	QueryUtils::footerBuilding(response);

	server->sendTo(response, query.clients);

}

void Response::createMatch(Server* server, createMatchResponseQuery query) {


	std::string response = "";

	QueryUtils::headerBuilding(response);

	QueryUtils::setValue(response, "Response", "createMatch");

	if (query.queryErrors.getErrors().size() == 1 && query.queryErrors.getErrors().at(0).errorNumber == 0){

		std::vector<Participant> participantsList = query.match->getParticipantsList();
		
		QueryUtils::setValue(response, "MatchId", query.match->getId());
		QueryUtils::setValue(response, "GridWidth", query.match->getGrid()->getGridWidth());
		QueryUtils::setValue(response, "GridHeight", query.match->getGrid()->getGridHeight());

		std::stringstream playersList_stream;

		int i = 0;

		std::string tmpPlayer = "";

		for (std::vector<Participant>::iterator it = participantsList.begin(); it != participantsList.end(); ++it)
		{

			

			if (it->state == ParticipantState::INVITED_ANYONE){

				tmpPlayer = "ANYBODY";

			}
			else if (it->player != nullptr)
			{

				tmpPlayer = it->player->getName();

			}

			if (i == 0){

				playersList_stream << tmpPlayer;

			}

			playersList_stream << "|" << tmpPlayer;

			i++;

		}

		QueryUtils::setValue(response, "PseudoPlayers", playersList_stream.str());
		QueryUtils::setValue(response, "WinSize", query.match->getWinSize());

	}

	QueryUtils::setErrors(response, query.queryErrors);

	QueryUtils::footerBuilding(response);

	server->sendTo(response, query.clients);

}

void Response::getMatchList(Server* server, getMatchListResponseQuery query) {

	std::string response = "";

	QueryUtils::headerBuilding(response);

	QueryUtils::setValue(response, "Response", "getMatchList");

	if (query.queryErrors.getErrors().size() == 1 && query.queryErrors.getErrors().at(0).errorNumber == 0){

		QueryUtils::setValue(response, "MatchCount", query.matchesList.size());

		std::stringstream matchList_stream;
		int i = 0;
		std::string jouable = "-1";

		for (std::map<unsigned int, Match*>::iterator it = query.matchesList.begin(); it != query.matchesList.end(); ++it)
		{

			if (it->second == nullptr) continue;

			if (it->second->canPlayerJoin(query.clients.at(0)))
			{

				jouable = "0";

			}
			else{

				jouable = "1";

			}

			if (i == 0){

				matchList_stream << it->second->getId() << ":" << jouable;

			}

			matchList_stream << " | " << it->second->getId() << ":" << jouable;

			i++;

		}

		QueryUtils::setValue(response, "MatchList", matchList_stream.str());

	}

	QueryUtils::setErrors(response, query.queryErrors);

	QueryUtils::footerBuilding(response);

	server->sendTo(response, query.clients);

}

void Response::getMatchInformation(Server* server, getMatchInformationResponseQuery query) {

	std::string response = "";

	QueryUtils::headerBuilding(response);

	QueryUtils::setValue(response, "Response", "getMatchInformation");

	if (query.queryErrors.getErrors().size() == 1 && query.queryErrors.getErrors().at(0).errorNumber == 0){

		QueryUtils::setValue(response, "MatchId", query.match->getId());

		std::string tmp = "-1";

		if (query.match->getCurrentPlayer() != query.clients.at(0))
		{

			tmp = "0";

		}
		else{

			tmp = "1";

		}

		QueryUtils::setValue(response, "DoYouPlay", tmp);

		if (query.match->canPlayerJoin(query.clients.at(0)))
		{

			tmp = "1";

		}
		else{

			tmp = "0";

		}

		QueryUtils::setValue(response, "CanYouJoin", tmp);

		std::stringstream grid_stream;

		Grid* grid = query.match->getGrid();
		Player*** gridData = grid->getGrid();

		for (int j = 0; j < grid->getGridHeight(); j++){

			for (int i = 0; i < grid->getGridWidth(); i++){

				if (i != 0 || j != 0)
					grid_stream << "|";

				std::cout << gridData << std::endl;

				if (gridData[j][i] == nullptr){

					grid_stream << "|";

				}
				else
				{

					grid_stream << gridData[j][i]->getName();

				}

			}

		}

		QueryUtils::setValue(response, "Grid", grid_stream.str());
		QueryUtils::setValue(response, "GridWidth", grid->getGridWidth());
		QueryUtils::setValue(response, "GridHeight", grid->getGridHeight());

		std::stringstream playersList_stream;

		int i = 0;

		std::string tmpPlayer = "";

		std::vector<Participant> participantsList = query.match->getParticipantsList();

		for (std::vector<Participant>::iterator it = participantsList.begin(); it != participantsList.end(); ++it)
		{

			if (it->player == nullptr) continue;

			if (it->player == query.clients.at(0)){

				playersList_stream << "*";

			}
			else if (it->state == LEFT){

				playersList_stream << "!";

			}
			else if (it->state == INVITED_PLAYER || it->state == INVITED_ANYONE){

				playersList_stream << "?";

			}

			if (it->state == ParticipantState::INVITED_ANYONE){

				tmpPlayer = "ANYBODY";

			}
			else
			{

				tmpPlayer == it->player->getName();

			}

			if (i == 0){

				playersList_stream << tmpPlayer;

			}

			playersList_stream << " | " << tmpPlayer;

			i++;

		}

		QueryUtils::setValue(response, "players", playersList_stream.str());
		QueryUtils::setValue(response, "state", query.match->getState());

	}

	QueryUtils::setErrors(response, query.queryErrors);

	QueryUtils::footerBuilding(response);

	server->sendTo(response, query.clients);

}

void Response::joinMatch(Server* server, joinMatchResponseQuery query) {

	std::string response = "";

	QueryUtils::headerBuilding(response);

	QueryUtils::setValue(response, "Response", "joinMatch");

	if (query.queryErrors.getErrors().size() == 1 && query.queryErrors.getErrors().at(0).errorNumber == 0){

		QueryUtils::setValue(response, "MatchId", query.match->getId());

		std::string mode = "";

		if (query.isPlayerMode == 1){

			mode = "PLAYER";

		}
		else{

			mode = "SPECTATOR";

		}

		QueryUtils::setValue(response, "Mode", mode);

	}

	QueryUtils::setErrors(response, query.queryErrors);

	QueryUtils::footerBuilding(response);

	server->sendTo(response, query.clients);

}

void Response::playMatch(Server* server, playMatchResponseQuery query) {

	std::string response = "";

	QueryUtils::headerBuilding(response);

	QueryUtils::setValue(response, "Response", "playMatch");

	if (query.queryErrors.getErrors().size() == 1 && query.queryErrors.getErrors().at(0).errorNumber == 0){

		QueryUtils::setValue(response, "MatchId", query.match->getId());

		std::stringstream grid_stream;

		for (int j = 0; j < query.match->getGrid()->getGridHeight(); j++){

			for (int i = 0; i < query.match->getGrid()->getGridWidth(); i++){

				if (i != 0 || j != 0)
					grid_stream << "|";

				if (query.match->getGrid()->getGrid()[j][i] == nullptr){

					grid_stream << "|";

				}
				else
				{

					grid_stream << query.match->getGrid()->getGrid()[j][i]->getName();

				}

			}

		}

		QueryUtils::setValue(response, "Grid", grid_stream.str());

		std::stringstream playersList_stream;
		std::string tmpPlayer = "";
		int i = 0;

		std::vector<Participant> participantsList = query.match->getParticipantsList();

		for (std::vector<Participant>::iterator it = participantsList.begin(); it != participantsList.end(); ++it)
		{

			if (it->player == nullptr) continue;

			if (it->player == query.clients.at(0)){

				playersList_stream << "*";

			}
			else if (it->state == LEFT){

				playersList_stream << "!";

			}
			else if (it->state == INVITED_PLAYER || it->state == INVITED_ANYONE){

				playersList_stream << "?";

			}

			if (it->state == ParticipantState::INVITED_ANYONE){

				tmpPlayer = "ANYBODY";

			}
			else
			{

				tmpPlayer == it->player->getName();

			}

			if (i == 0){

				playersList_stream << tmpPlayer;

			}

			playersList_stream << " | " << tmpPlayer;

			i++;

		}

		QueryUtils::setValue(response, "Players", playersList_stream.str());

		std::string result = "";

		if (query.match->getState() == FINISHED){

			if (query.match->getWinner().player == query.clients.at(0)){

				result = "YOU_WIN";

			}
			else{

				result = "YOU_LOOSE";

			}

		}
		else{

			if (query.match->getCurrentPlayer() == query.clients.at(0)){

				result = "YOU_PLAY";

			}
			else{

				result = "YOU_WAIT";

			}

		}

		QueryUtils::setValue(response, "Result", result);

	}

	QueryUtils::setErrors(response, query.queryErrors);

	QueryUtils::footerBuilding(response);

	server->sendTo(response, query.clients);

	playMatchNotifyQuery notifyQuery;
	notifyQuery.clients = Response::multicastHelper(query.match);
	notifyQuery.match = query.match;

	Notify::playMatch(server, notifyQuery);

}

void Response::resetMatch(Server* server, resetMatchResponseQuery query) {

	std::string response = "";

	QueryUtils::headerBuilding(response);

	QueryUtils::setValue(response, "Response", "resetMatch");

	if (query.queryErrors.getErrors().size() == 1 && query.queryErrors.getErrors().at(0).errorNumber == 0){

		QueryUtils::setValue(response, "MatchId", query.match->getId());

	}

	QueryUtils::setErrors(response, query.queryErrors);

	QueryUtils::footerBuilding(response);

	server->sendTo(response, query.clients);

}

void Response::quitMatch(Server* server, quitMatchResponseQuery query) {

	std::string response = "";

	QueryUtils::headerBuilding(response);

	QueryUtils::setValue(response, "Response", "quitMatch");

	if (query.queryErrors.getErrors().size() == 1 && query.queryErrors.getErrors().at(0).errorNumber == 0){

		QueryUtils::setValue(response, "MatchId", query.match->getId());

	}

	QueryUtils::setErrors(response, query.queryErrors);

	QueryUtils::footerBuilding(response);

	server->sendTo(response, query.clients);

}

void Response::getPlayerInformation(Server* server, getPlayerInformationResponseQuery query) {

	std::string response = "";

	QueryUtils::headerBuilding(response);

	QueryUtils::setValue(response, "Response", "getPlayerInformation");

	if (query.queryErrors.getErrors().size() == 1 && query.queryErrors.getErrors().at(0).errorNumber == 0){

		QueryUtils::setValue(response, "Pseudo", query.clients.at(0)->getName());
		QueryUtils::setValue(response, "GlobalScore", query.clients.at(0)->getGlobalScore());

	}

	QueryUtils::setErrors(response, query.queryErrors);

	QueryUtils::footerBuilding(response);

	server->sendTo(response, query.clients);

}








std::vector<Player*> Response::unicastHelper(Player* sender){

	std::vector<Player*> target;

	if (sender != nullptr)
		target.push_back(sender);

	return target;

}

std::vector<Player*> Response::multicastHelper(Match* match){

	std::vector<Player*> target;

	if (match == nullptr)
		return target;

	std::vector<Participant> participantsList =  match->getParticipantsList();

	for (std::vector<Participant>::iterator it = participantsList.begin(); it != participantsList.end(); ++it) {

		if (it->player != nullptr)
			target.push_back(it->player);

	}

	return target;

}

void Response::genericError(Server* server, ServerQuery query) {

	std::string response = "";

	QueryUtils::headerBuilding(response);

	QueryUtils::setValue(response, "Response", "genericError");

	QueryUtils::setValue(response, "ErrorCode", "-1");
	QueryUtils::setValue(response, "ErrorMessage", "This is nonsense !");

	QueryUtils::footerBuilding(response);

	server->sendTo(response, query.clients);
}