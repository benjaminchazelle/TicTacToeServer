#ifndef NOTIFYH
#define NOTIFYH

#include "ServerQuery.h"
#include "../Server.h"


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