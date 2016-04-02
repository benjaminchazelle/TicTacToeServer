#include "Logic.h"
#include "Match.h"
#include "QueryUtils.h"
#include <string>
#include "Query\RequestQuery.h"
#include "Query\Request.h"

#include <iostream>

Logic::Logic(Server* _server) : server(_server)
{
}


Logic::~Logic(void)
{
}

std::map<unsigned int, Match*> Logic::getMatchsList() {
	return this->matchsList;
	//todo qqch
}


std::map<unsigned int, Player*> Logic::getPlayersList(){
	return this->playersList;
}

void Logic::onMatchClosed(Match* match) {

	for(std::map<unsigned int, Match*>::iterator it = this->matchsList.begin(); it!= this->matchsList.end();)
	{
		if(it->second == match)
			it = this->matchsList.erase(it);
		else
			++it;
	}

}


bool Logic::routeRequest(Player* player, std::string requestQuery) {

	std::string bufferedQuery = requestQuery;

	bool validHeader = QueryUtils::headerParsing(bufferedQuery);

	if(!validHeader)
		return false;


	ParsedEntity<std::string> method = QueryUtils::getStringParsing(bufferedQuery);

	if(method.key != "Request")
		return false;

	if(method.value == "getIdentity") {

		getIdentityRequestQuery query;

		query.sender = player;

		Request::getIdentity(this->server, query);
		

	}
	else if(method.value == "setIdentity") {


		ParsedEntity<std::string> Pseudo = QueryUtils::getStringParsing(bufferedQuery);

		if(Pseudo.error && Pseudo.key != "Pseudo")
			return false;

		if(QueryUtils::footerParsing(bufferedQuery)) {

			setIdentityRequestQuery query;

			query.pseudo = Pseudo.value;
			query.sender = player;

			Request::setIdentity(this->server, query);

		}

	}

	else if(method.value == "createMatch") {


		ParsedEntity<int> GridWidth = QueryUtils::getIntParsing(bufferedQuery);

		if(GridWidth.error || GridWidth.key != "GridWidth" )
			return false;

		ParsedEntity<int> GridHeight = QueryUtils::getIntParsing(bufferedQuery);

		if(GridHeight.error || GridHeight.key != "GridHeight")
			return false;

		ParsedEntity<std::vector<std::string>> PseudoPlayers = QueryUtils::getPseudoPlayersParsing(bufferedQuery);

		if(PseudoPlayers.error || PseudoPlayers.key != "PseudoPlayers")
			return false;

		ParsedEntity<int> WinSize = QueryUtils::getIntParsing(bufferedQuery);

		if( WinSize.error || WinSize.key != "WinSize")
			return false;

		

		if(QueryUtils::footerParsing(bufferedQuery)) {

			createMatchRequestQuery query;

			query.gridWidth = GridWidth.value;
			query.gridHeight = GridHeight.value;
			query.playerList = PseudoPlayers.value;
			query.winSize = WinSize.value;
			
			query.sender = player;

			Request::createMatch(this->server, query);

		}

	}

	else if(method.value == "...") {


		ParsedEntity<int> MonAttributInt = QueryUtils::getIntParsing(bufferedQuery);

		if(MonAttributInt.error || MonAttributInt.key != "MonAttributInt" )
			return false;

		ParsedEntity<std::string> MonAttributString = QueryUtils::getStringParsing(bufferedQuery);

		if(MonAttributString.error || MonAttributString.key != "MonAttributString")
			return false;


		if(QueryUtils::footerParsing(bufferedQuery)) {

			/*
			maRequeteRequestQuery query;

			query.MonAttributInt = MonAttributInt.value;
			query.MonAttributString = MonAttributString.value;
			
			query.sender = player;
			
			Request::maRequete(this->server, query);

			*/

		}

	}
	else {
		return false;
	}


	return true;
};

bool QueryUtils::footerParsing(std::string &bufferedQuery) {

	return bufferedQuery == "\r\n\r\n";
}