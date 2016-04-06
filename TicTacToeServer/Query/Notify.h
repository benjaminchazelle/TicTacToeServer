#ifndef NOTIFYH
#define NOTIFYH

#include "ServerQuery.h"
#include "../Server.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////Ensemble de fonctions permettant de notifier les joueurs qu'il peuvent faire certaines actions///////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class Notify
{
public:
	Notify(void);
	~Notify(void);

	static void setIdentity(Server* server, setIdentityNotifyQuery query);

	static void joinMatch(Server* server, joinMatchNotifyQuery query);

	static void playMatch(Server* server, playMatchNotifyQuery query);


};

#endif