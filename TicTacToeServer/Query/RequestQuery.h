#ifndef REQUESTQUERYH
#define REQUESTQUERYH

#include <string>
#include <vector>

#include "../Match.h"
#include "../Player.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////Ensemble de structures permettant la gestion des données dans les requêtes///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Match;
class Player;

struct RequestQuery {

	Player* sender;
};

struct setIdentityRequestQuery : RequestQuery {

	std::string pseudo;

};

struct getIdentityRequestQuery : RequestQuery {

	std::string pseudo;

};

struct createMatchRequestQuery : RequestQuery {

	int gridWidth;
	int gridHeight;
	std::vector<std::string> playersList;
	int winSize;

};

struct getMatchListRequestQuery : RequestQuery {

};

struct getMatchInformationRequestQuery : RequestQuery {

	int match;

};

struct joinMatchRequestQuery : RequestQuery {

	int match;
	std::string mode;
};

struct playMatchRequestQuery : RequestQuery {

	int match;
	int coordinate_x;
	int coordinate_y;

};


struct resetMatchRequestQuery : RequestQuery {

	int match;

};

struct quitMatchRequestQuery : RequestQuery {

	int match;

};

struct getPlayerInformationRequestQuery : RequestQuery {

	std::string player;

};

#endif