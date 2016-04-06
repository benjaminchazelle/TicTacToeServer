#ifndef MATCHH
#define MATCHH

#include "Player.h"
#include <vector>
#include "Grid.h"
#include "Logic.h"
#include "Status.h"


class Player;
class Grid;
class Logic;
/*
enum MatchError {
	OK,
	UNEXISTS,

};*/

enum ParticipantState {
	INVITED_PLAYER,
	INVITED_ANYONE,
	PLAYING,
	LEFT
};


struct Participant {


	Player* player;
	ParticipantState state;

	Participant () : player(nullptr), state(INVITED_ANYONE) {};
		
};

enum MatchState {
	WAITING_PLAYERS,
	PROGRESS,
	FINISHED
};

class Match
{
private:

   static unsigned int LastIDGiven;
   const unsigned int currentID;

	std::vector<Player*> spectatorsList;

	std::vector<Participant> participantsList;
	Grid* grid;

	unsigned int winSize;

	MatchState state;

	Player* currentPlayer;

	Logic* logic;


public:



	Match(unsigned int _gridWidth, unsigned int _gridHeight, unsigned int _winSize, std::vector<Participant> _participantsList, Logic* _logic);

	~Match(void);

	Grid* getGrid();

	void addSpectator(Player* spectator);

	Status inviteParticipant(Participant participant);

	Status onMatchAccepted(Player* player);
	Status onMatchDeserted(Player* player);

	Status play(Player* player, unsigned int x, unsigned int y);

	unsigned int getwinSize();

	Player* getCurrentPlayer();

	std::vector<Participant> getParticipantsList();

	MatchState getState();

	Participant getWinner();

	std::vector<Participant>::iterator Match::getNextParticipantPlayer(std::vector<Participant>::iterator fromParticipant);

	bool canPlayerJoin(Player* player);

	std::vector<Participant>::iterator findParticipant(Player* player);
	bool ThisPlayerIsParticipant(Player* player);

	Status resetMatch(Player* player); //TODO v�irifer que le gars qu idemande est dans la partie

	void closeMatch();

	std::vector<Participant>::iterator findPlaceToParticipate(Player* player);

	unsigned int getWinSize();

	unsigned int getId();

};

#endif

