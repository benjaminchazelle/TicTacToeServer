#ifndef LOGICH
#define LOGICH

#include "QueryUtils.h"
#include <map>
#include "Server.h"
#include "Match.h"
#include "Player.h"

class Server;
class Match;

class Logic
{
private:

	Server* server;

	std::map<unsigned int, Match*> matchsList;
	std::map<unsigned int, Player*> playersList;



public:
	Logic(Server* _server);
	~Logic(void);

	std::map<unsigned int, Match*> getMatchsList();
	std::map<unsigned int, Player*> getPlayersList();

	void onMatchClosed( Match* );


 bool routeRequest(Player* player, std::string requestQuery);

};

#endif

