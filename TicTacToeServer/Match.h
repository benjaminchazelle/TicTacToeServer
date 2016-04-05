#ifndef MATCHH
#define MATCHH

#include "Player.h"
#include <vector>
#include "Grid.h"
#include "Logic.h"


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

	bool inviteParticipant(Participant participant);

	bool onMatchAccepted(Player* player);
	bool onMatchDeserted(Player* player);

	bool play(Player* player, unsigned int x, unsigned int y);

	unsigned int getwinSize();

	Player* getCurrentPlayer();

	std::vector<Participant> getParticipantsList();

	MatchState getState();

	Participant getWinner();

	std::vector<Participant>::iterator Match::getNextParticipantPlayer(std::vector<Participant>::iterator fromParticipant);

	bool canPlayerJoin(Player* player);

	std::vector<Participant>::iterator findParticipant(Player* player);
	bool ThisPlayerIsParticipant(Player* player);

	void resetMatch(Player* player); //TODO véirifer que le gars qu idemande est dans la partie

	void closeMatch();

	std::vector<Participant>::iterator findPlaceToParticipate(Player* player);

};

#endif

