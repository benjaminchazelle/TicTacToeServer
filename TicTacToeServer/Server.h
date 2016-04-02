#ifndef SERVERH
#define SERVERH

#include "Logic.h"

class Logic;

class Server
{
private:
	Logic* logic;



public:
	Server(void);
	~Server(void);

	static void* Server::onClientTalk(void *_args);

	void Server::start();
};

#endif