#ifndef PLAYERH
#define PLAYERH

#include "Match.h"
#include <string>
#include <vector>

class Match;



class Player
{
private:

   static unsigned int LastIDGiven;
   const unsigned int currentID;

	std::string name;
	int clientSocket;

	std::vector<Match*> matchesList;


	int globalScore;

public:

	Player(void);
	Player(std::string n ) : name(n), currentID(++LastIDGiven) {};
	~Player(void);

	void setName(std::string _name);
	std::string getName();

	int getGlobalScore();

	bool acceptMatchInvitation(Match* match);
	bool quitMatch(Match* match);
	
	void onMatchInvited(Match* match);
	void onMatchRemoved(Match* match);

	bool haveThisMatch(Match* match);
/*
	*/
};



#endif