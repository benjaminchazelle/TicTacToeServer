#ifndef GRIDH
#define GRIDH

#include "Player.h"
#include "Status.h"

class Player;

class Grid
{
private:
	Player*** gridData;
	unsigned int gridWidth;
	unsigned int gridHeight;

public:
	Grid(unsigned int gridWidth, unsigned int gridHeight);
	~Grid(void);

	Player*** getGrid();

	int getGridWidth();
	int getGridHeight();

	void reset();

	Status play(Player* player, unsigned int x, unsigned int y);

	Player* getWinner(unsigned int winSize);

	void Debug();
};

#endif