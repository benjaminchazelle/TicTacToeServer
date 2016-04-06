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

#include "Player.h"
#include <sstream>

unsigned int Player::LastIDGiven = 0;


Player::Player(int socket, sockaddr_in address) : clientSocket(socket), name(""), connected(true), currentID(++LastIDGiven) {

	std::stringstream name_stream;

	name_stream << inet_ntoa(address.sin_addr) << ":" << ntohs(address.sin_port);

	this->name = name_stream.str();

};

Player::~Player(void)
{
}


void Player::setName(std::string _name)
{
	this->name = _name;
	//check si le pseudo existe ?
}

std::string Player::getName()
{
	return this->name;
}


int Player::getGlobalScore()
{
	return this->globalScore;
}

Status Player::acceptMatchInvitation(Match* match) {

	if(match == nullptr)
		return Status::MATCH_NOT_EXISTS;

	if(this->haveThisMatch(match))
		return Status::MATCH_USER_ALREADY_INNER;

	Status status_onMatch_Accepted = match->onMatchAccepted(this);
	if(match->onMatchAccepted(this) != Status::MATCH_USER_ACCEPTED) 
		return status_onMatch_Accepted;

	this->matchesList.push_back(match);
	return Status::MATCH_USER_ACCEPTED;
}

Status Player::quitMatch(Match* match) {

	if(match == nullptr)
		return Status::MATCH_NOT_EXISTS;

	Status onMatchDesertedStatus = match->onMatchDeserted(this);
	if(onMatchDesertedStatus != Status::MATCH_DESERTED)
		return onMatchDesertedStatus;

	return Status::MATCH_DESERTED;

}

void Player::onMatchInvited(Match* match)
{
}

void Player::onMatchRemoved(Match* match)
{
	for(std::vector<Match*>::iterator it = this->matchesList.begin(); it!= this->matchesList.end();)
	{
		if(*it == match)
			it = this->matchesList.erase(it);
		else
			++it;
	}
}

bool Player::haveThisMatch(Match* match) {

	for(std::vector<Match*>::iterator it = this->matchesList.begin(); it!= this->matchesList.end(); ++it)
	{
		if(*it == match)
			return true;
	}

	return false;
}

void Player::disconnect() {
	this->connected = false;
}

int Player::getSocket() {
	return this->clientSocket;
}