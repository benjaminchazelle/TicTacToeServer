#include "Server.h"
#include "Query\Response.h"
#include "Query\ServerQuery.h"
#include "QueryUtils.h"
#include "Player.h"
#include "Match.h"
#include <sstream>

void Response::getIdentity(Server* server, getIdentityResponseQuery query) {

	std::string response = "";

	QueryUtils::headerBuilding(response);

	QueryUtils::setValue(response, "Response", "getIdentity");

	QueryUtils::setValue(response, "Pseudo", query.pseudo);

	QueryUtils::setErrors(response, query.queryErrors);

	QueryUtils::footerBuilding(response);

	server->sendTo(response, query.clients);

}

void Response::setIdentity(Server* server, setIdentityResponseQuery query){

	std::string response = "";

	QueryUtils::headerBuilding(response);

	QueryUtils::setValue(response, "Response", "setIdentity");

	QueryUtils::setValue(response, "Pseudo", query.pseudo);

	QueryUtils::setErrors(response, query.queryErrors);

	QueryUtils::footerBuilding(response);

	server->sendTo(response, query.clients);

}

void Response::createMatch(Server* server, createMatchResponseQuery query) {

	std::string response = "";

	std::stringstream playersList_stream;

	int i = 0;

	std::string tmpPlayer = "";

	for (std::vector<Participant>::iterator it = query.match->getParticipantsList().begin(); it != query.match->getParticipantsList().end(); ++it)
	{
		
		if (it->player == nullptr) continue;

		if (it->state == ParticipantState::INVITED_ANYONE){

			tmpPlayer = "ANYBODY";

		}
		else
		{

			tmpPlayer == it->player->getName;

		}

		if (i == 0){

			playersList_stream << tmpPlayer;

		}

		playersList_stream << " | " << tmpPlayer;

		i++;

	}

	QueryUtils::headerBuilding(response);

	QueryUtils::setValue(response, "Response", "createMatch");

	//TODO mettre un id dans match

	//QueryUtils::setValue(response, "MatchId", query.match);
	QueryUtils::setValue(response, "GridWidth", query.match->getGrid()->getGridWidth());
	QueryUtils::setValue(response, "GridHeight", query.match->getGrid()->getGridHeight());
	QueryUtils::setValue(response, "PseudoPlayers", playersList_stream.str());
	QueryUtils::setValue(response, "WinSize", query.match->getGrid();

	QueryUtils::setErrors(response, query.queryErrors);

	QueryUtils::footerBuilding(response);

	server->sendTo(response, query.clients);

}

void Response::getMatchList(Server* server, getMatchListResponseQuery query) {

	std::string response = "";

	QueryUtils::headerBuilding(response);

	QueryUtils::setValue(response, "Response", "getMatchList");

	QueryUtils::setValue(response, "MatchCount", query.matchList.size());
	QueryUtils::setValue(response, "MatchCount", query.matchList.size());

	QueryUtils::setErrors(response, query.queryErrors);

	QueryUtils::footerBuilding(response);

	server->sendTo(response, query.clients);

}

void Response::getMatchInformation(Server* server, getMatchInformationResponseQuery query) {

	std::string response = "";

	QueryUtils::headerBuilding(response);

	QueryUtils::setValue(response, "Response", "setIdentity");

	QueryUtils::setValue(response, "Pseudo", query.pseudo);

	QueryUtils::setErrors(response, query.queryErrors);

	QueryUtils::footerBuilding(response);

	server->sendTo(response, query.clients);

}

void Response::joinMatch(Server* server, joinMatchResponseQuery query) {

	std::string response = "";

	QueryUtils::headerBuilding(response);

	QueryUtils::setValue(response, "Response", "setIdentity");

	QueryUtils::setValue(response, "Pseudo", query.pseudo);

	QueryUtils::setErrors(response, query.queryErrors);

	QueryUtils::footerBuilding(response);

	server->sendTo(response, query.clients);

}

void Response::playMatch(Server* server, playMatchResponseQuery query) {

	std::string response = "";

	QueryUtils::headerBuilding(response);

	QueryUtils::setValue(response, "Response", "setIdentity");

	QueryUtils::setValue(response, "Pseudo", query.pseudo);

	QueryUtils::setErrors(response, query.queryErrors);

	QueryUtils::footerBuilding(response);

	server->sendTo(response, query.clients);

}

void Response::resetMatch(Server* server, resetMatchResponseQuery query) {

	std::string response = "";

	QueryUtils::headerBuilding(response);

	QueryUtils::setValue(response, "Response", "setIdentity");

	QueryUtils::setValue(response, "Pseudo", query.pseudo);

	QueryUtils::setErrors(response, query.queryErrors);

	QueryUtils::footerBuilding(response);

	server->sendTo(response, query.clients);

}

void Response::quitMatch(Server* server, quitMatchResponseQuery query) {

	std::string response = "";

	QueryUtils::headerBuilding(response);

	QueryUtils::setValue(response, "Response", "setIdentity");

	QueryUtils::setValue(response, "Pseudo", query.pseudo);

	QueryUtils::setErrors(response, query.queryErrors);

	QueryUtils::footerBuilding(response);

	server->sendTo(response, query.clients);

}

void Response::getPlayerInformation(Server* server, getPlayerInformationResponseQuery query) {

	std::string response = "";

	QueryUtils::headerBuilding(response);

	QueryUtils::setValue(response, "Response", "setIdentity");

	QueryUtils::setValue(response, "Pseudo", query.pseudo);

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
		return;

	for (std::vector<Participant>::iterator it = match->getParticipantsList().begin(); it != match->getParticipantsList().end(); ++it) {

		if (it->player != nullptr)
			target.push_back(it->player);

	}

	return target;

}