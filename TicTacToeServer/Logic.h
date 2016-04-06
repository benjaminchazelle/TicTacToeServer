#ifndef LOGICH
#define LOGICH

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>
#include <time.h>

#include "Match.h"

#include <string>
#include <iostream>

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

#include "QueryUtils.h"
#include <map>
#include "Server.h"
#include "Match.h"
#include "Player.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////Ensemble de fonctions permettant d'envoyer qui permettent de gérer les parties et de faire les tests adéquats////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Server;
class Match;
class Player;
struct Participant;

class Logic
{
private:

	Server* server;

	std::map<unsigned int, Match*> matchsList;
	std::map<int, Player*> playersList;



public:
	Logic(Server* _server);
	~Logic(void);

	std::map<unsigned int, Match*> getMatchsList();
	std::map<int, Player*> getPlayersList();

	void addPlayer(int socket, sockaddr_in address);
	void removePlayer(int socket, sockaddr_in address);
	Player* getPlayer(int socket);
	Player* getPlayer(std::string pseudo);

	Match* addMatch(unsigned int _gridWidth, unsigned int _gridHeight, unsigned int _winSize, std::vector<Participant> _participantsList);

	bool isPseudoAvailable(std::string pseudo);

	void onMatchClosed( Match* );

	bool routeRequest(Player* player, std::string requestQuery);

};

#endif

