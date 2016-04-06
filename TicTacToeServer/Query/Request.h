#ifndef REQUESTH
#define REQUESTH

#include "RequestQuery.h"
#include "../Server.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////Ensemble de fonctions permettant d'envoyer des requêtes depuis le client au serveur//////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Server;

class Request
{
public:
	Request(void);
	~Request(void);


	static void setIdentity(Server* server, setIdentityRequestQuery query);

	static void getIdentity(Server* server, getIdentityRequestQuery query);

	static void createMatch(Server* server, createMatchRequestQuery query);

	static void getMatchList(Server* server, getMatchListRequestQuery query);

	static void getMatchInformation(Server* server, getMatchInformationRequestQuery query);

	static void joinMatch(Server* server, joinMatchRequestQuery query);

	static void playMatch(Server* server, playMatchRequestQuery query);

	static void resetMatch(Server* server, resetMatchRequestQuery query);

	static void quitMatch(Server* server, quitMatchRequestQuery query);

	static void getPlayerInformation(Server* server, getPlayerInformationRequestQuery query);


	static void nonSense(Server* server, RequestQuery query);
};

#endif