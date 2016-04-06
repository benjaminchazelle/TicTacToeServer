#ifndef RESPONSEQUERYH
#define RESPONSEQUERYH

#include <string>
#include <vector>

#include "../Match.h"
#include "../Player.h"
#include "../Errors.h"



struct ServerQuery {
	Errors queryErrors;
	std::vector<Player*> clients;
	/*
	ServerQuery() {}
	ServerQuery(const ServerQuery& q) : clients(q.clients), queryErrors(q.queryErrors) {}*/
};



struct setIdentityResponseQuery : ServerQuery {

	std::string pseudo;

};

struct getIdentityResponseQuery : ServerQuery {

	std::string pseudo;

};

struct createMatchResponseQuery : ServerQuery {

	Match* match;
	/*
	createMatchResponseQuery() : match(nullptr) {}
	createMatchResponseQuery(const createMatchResponseQuery& q) : match(q.match) {}*/

};

struct getMatchListResponseQuery : ServerQuery {

	std::map<unsigned int, Match*> matchesList;

};

struct getMatchInformationResponseQuery : ServerQuery {

	Match* match;


};

struct joinMatchResponseQuery : ServerQuery {

	Match* match;
	bool isPlayerMode;
};

struct playMatchResponseQuery : ServerQuery {

	Match* match;

};


struct resetMatchResponseQuery : ServerQuery {

	Match* match;

};

struct quitMatchResponseQuery : ServerQuery {

	Match* match;

};

struct getPlayerInformationResponseQuery : ServerQuery {

	Player* player;

};






struct setIdentityNotifyQuery : ServerQuery {

};

struct joinMatchNotifyQuery : ServerQuery {

	Match* match;

};

struct playMatchNotifyQuery : ServerQuery {

	Match* match;

};


#endif
