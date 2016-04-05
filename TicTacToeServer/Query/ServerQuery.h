#ifndef RESPONSEQUERYH
#define RESPONSEQUERYH

#include <string>
#include <vector>

#include "../Match.h"
#include "../Player.h"
#include "Errors.h"



struct ServerQuery {
	Errors queryErrors;
	std::vector<Player*> clients;
};



struct setIdentityResponseQuery : ServerQuery {

	std::string pseudo;

};

struct getIdentityResponseQuery : ServerQuery {

	std::string pseudo;

};

struct createMatchResponseQuery : ServerQuery {

	Match* match;

};

struct getMatchListResponseQuery : ServerQuery {

	std::map<unsigned int, Match*> matchesList;

};

struct getMatchInformationResponseQuery : ServerQuery {

	Match* match;

};

struct joinMatchResponseQuery : ServerQuery {

	Match* match;

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
