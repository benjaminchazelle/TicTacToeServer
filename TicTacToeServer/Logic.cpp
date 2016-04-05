#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>
#include <time.h>

#ifdef WIN32

#include <winsock2.h> 
#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)  
#define close(s) closesocket(s)

#elif defined (linux) 

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

#else 

#error not defined for this platform

#endif

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


std::map<int, Player*> Logic::getPlayersList(){

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

void Logic::addPlayer(int socket, sockaddr_in address) {

	this->playersList[socket] = new Player(socket, address);

}

void Logic::removePlayer(int socket){

	if(this->playersList[socket] != nullptr) {

		this->playersList.at(socket)->disconnect();

		this->playersList.erase(socket);
	}


}

Player* Logic::getPlayer(int socket){

	return this->playersList[socket];

}

Player* Logic::getPlayer(std::string pseudo) {

	for(std::map<int, Player*>::iterator it = this->playersList.begin(); it!= this->playersList.end();)
	{
		if(it->second->getName() == pseudo)
			return it->second;
	}

	return nullptr;
}

bool Logic::isPseudoAvailable(std::string pseudo) {

	return this->getPlayer(pseudo) != nullptr;

};

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
			query.playersList = PseudoPlayers.value;
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


Match* Logic::addMatch(unsigned int _gridWidth, unsigned int _gridHeight, unsigned int _winSize, std::vector<Participant> _participantsList) {

	Match* match = new Match(_gridWidth, _gridHeight, _winSize, _participantsList);

	this->matchsList[match->getId()] = match;

	return match;

}