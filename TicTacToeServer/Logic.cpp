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


bool Logic::routeRequest(Player* ClientPlayer, std::string requestQuery) {

	std::string bufferedQuery = requestQuery;

	bool validHeader = QueryUtils::headerParsing(bufferedQuery);

	if(!validHeader)
		return false;


	ParsedEntity<std::string> method = QueryUtils::getStringParsing(bufferedQuery);

	if(method.key != "Request")
		return false;

	if(method.value == "getIdentity") {

		getIdentityRequestQuery query;

		query.sender = ClientPlayer;

		Request::getIdentity(this->server, query);
		

	}
	else if(method.value == "setIdentity") {


		ParsedEntity<std::string> Pseudo = QueryUtils::getStringParsing(bufferedQuery);

		if(Pseudo.error && Pseudo.key != "Pseudo")
			return false;

		if(QueryUtils::footerParsing(bufferedQuery)) {

			setIdentityRequestQuery query;

			query.pseudo = Pseudo.value;
			query.sender = ClientPlayer;

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
			
			query.sender = ClientPlayer;

			Request::createMatch(this->server, query);

		}

	}

	else if (method.value == "getMatchList") {


		if (QueryUtils::footerParsing(bufferedQuery)) {

			getMatchListRequestQuery query;

			query.sender = ClientPlayer;

			Request::getMatchList(this->server, query);

		}

	}

	else if(method.value == "getMatchInformation") {


		ParsedEntity<int> match = QueryUtils::getIntParsing(bufferedQuery);

		if (match.error || match.key != "match")
			return false;

		if(QueryUtils::footerParsing(bufferedQuery)) {

			getMatchInformationRequestQuery query;

			query.match = match.value;
			
			query.sender = ClientPlayer;
			
			Request::getMatchInformation(this->server, query);

		}

	}

	else if (method.value == "playMatch") {


		ParsedEntity<int> match = QueryUtils::getIntParsing(bufferedQuery);

		if (match.error || match.key != "match")
			return false;

		ParsedEntity<int> coordinate_x = QueryUtils::getIntParsing(bufferedQuery);

		if (coordinate_x.error || coordinate_x.key != "coordinate_x")
			return false;

		ParsedEntity<int> coordinate_y = QueryUtils::getIntParsing(bufferedQuery);

		if (coordinate_y.error || coordinate_y.key != "coordinate_y")
			return false;
	


		if (QueryUtils::footerParsing(bufferedQuery)) {

			
			playMatchRequestQuery query;

			query.match = match.value;
			query.coordinate_x = coordinate_x.value;
			query.coordinate_y = coordinate_y.value;
			
			query.sender = ClientPlayer;

			Request::playMatch(this->server, query);

		}

	}

	else if (method.value == "resetMatch") {


		ParsedEntity<int> match = QueryUtils::getIntParsing(bufferedQuery);

		if (match.error || match.key != "MonAttributInt")
			return false;

		if (QueryUtils::footerParsing(bufferedQuery)) {

			resetMatchRequestQuery query;

			query.match = match.value;

			query.sender = ClientPlayer;

			Request::resetMatch(this->server, query);

		}

	}

	else if (method.value == "quitMatch") {


		ParsedEntity<int> match = QueryUtils::getIntParsing(bufferedQuery);

		if (match.error || match.key != "MonAttributInt")
			return false;
		
		if (QueryUtils::footerParsing(bufferedQuery)) {

			quitMatchRequestQuery query;

			query.match = match.value;

			query.sender = ClientPlayer;

			Request::quitMatch(this->server, query);

		}

	}

	else if (method.value == "getPlayerInformation") {

		ParsedEntity<std::string> player= QueryUtils::getStringParsing(bufferedQuery);

		if (player.error || player.key != "MonAttributString")
			return false;


		if (QueryUtils::footerParsing(bufferedQuery)) {

			getPlayerInformationRequestQuery query;

			query.player = player.value;

			query.sender = ClientPlayer;

			Request::getPlayerInformation(this->server, query);

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