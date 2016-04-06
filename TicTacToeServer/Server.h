#ifndef SERVERH
#define SERVERH

#include "Logic.h"
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


class Logic;
class Player;

class Server
{
private:
	Logic* logic;




public:
	Server(void);
	~Server(void);

	static void* onClientTalk(void *_args);

	void start();

	bool sendTo(std::string response, std::vector<Player*> clients);

	Logic* getLogic();
};

#endif