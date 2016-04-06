#ifndef PLAYERH
#define PLAYERH

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

#include "Match.h"
#include <string>
#include <vector>
#include "Server.h"
#include "Status.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////Ensemble de fonctions permettant de gérer un joueur /////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Match;



class Player
{
private:

   static unsigned int LastIDGiven;
   const unsigned int currentID;

	std::string name;
	int clientSocket;

	std::vector<Match*> matchesList;

	bool connected;


	int globalScore;

public:

	Player(int socket, sockaddr_in address);
	~Player(void);

	void setName(std::string _name);
	std::string getName();

	int getGlobalScore();

	Status acceptMatchInvitation(Match* match);
	Status quitMatch(Match* match);
	
	void onMatchInvited(Match* match);
	void onMatchRemoved(Match* match);

	bool haveThisMatch(Match* match);

	void disconnect();

	int getSocket();
/*
	*/
};



#endif