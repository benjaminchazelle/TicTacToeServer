#ifndef RESPONSEH
#define RESPONSEH

#include "ServerQuery.h"
#include "../Server.h"

class Server;

class Response
{
public:
	Response(void);
	~Response(void);


	static void setIdentity(Server* server, setIdentityResponseQuery query);

	static void getIdentity(Server* server, getIdentityResponseQuery query);

	static void createMatch(Server* server, createMatchResponseQuery query);

	static void getMatchList(Server* server, getMatchListResponseQuery query);

	static void getMatchInformation(Server* server, getMatchInformationResponseQuery query);

	static void joinMatch(Server* server, joinMatchResponseQuery query);

	static void playMatch(Server* server, playMatchResponseQuery query);

	static void resetMatch(Server* server, resetMatchResponseQuery query);

	static void quitMatch(Server* server, quitMatchResponseQuery query);

	static void getPlayerInformation(Server* server, getPlayerInformationResponseQuery query);


};

#endif