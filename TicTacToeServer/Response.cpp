#include "Server.h"
#include "Query\Response.h"
#include "Query\ServerQuery.h"
#include "QueryUtils.h"
#include "Player.h"
#include "Match.h"

void Response::getIdentity(Server* server, getIdentityResponseQuery query) {

	std::string response = "";

	QueryUtils::headerBuilding(response);

	QueryUtils::setValue(response, "Response", "getIdentity");

	QueryUtils::setValue(response, "Pseudo", query.pseudo);

	QueryUtils::setErrors(response, query.queryErrors);

	QueryUtils::footerBuilding(response);

	server->sendTo(response, query.clients);

}



void Response::createMatch(Server* server, createMatchResponseQuery query) {

}

void Response::getMatchList(Server* server, getMatchListResponseQuery query) {

}

void Response::getMatchInformation(Server* server, getMatchInformationResponseQuery query) {

}

void Response::joinMatch(Server* server, joinMatchResponseQuery query) {

}

void Response::playMatch(Server* server, playMatchResponseQuery query) {

}

void Response::resetMatch(Server* server, resetMatchResponseQuery query) {

}

void Response::quitMatch(Server* server, quitMatchResponseQuery query) {

}

void Response::getPlayerInformation(Server* server, getPlayerInformationResponseQuery query) {

}








std::vector<Player*> Response::unicastHelper(Player* sender){

	std::vector<Player*> target;

	if(sender != nullptr)
		target.push_back(sender);

	return target;

}

std::vector<Player*> Response::multicastHelper(Match* match){

	std::vector<Player*> target;

	if(match == nullptr)
		return;

	for(std::vector<Participant>::iterator it = match->getParticipantsList().begin() ; it != match->getParticipantsList().end() ; ++it) {

		if(it->player != nullptr)
			target.push_back(it->player);

	}

	return target;

}