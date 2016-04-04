#ifndef LOGICH
#define LOGICH

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>
#include <time.h>

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

class Server;
class Match;
class Player;

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
	void removePlayer(int socket);
	Player* getPlayer(int socket);

	void onMatchClosed( Match* );

	bool routeRequest(Player* player, std::string requestQuery);

};

#endif

