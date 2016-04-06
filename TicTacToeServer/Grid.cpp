#include "Grid.h"
#include <iostream>

Grid::Grid(unsigned int _gridWidth, unsigned int _gridHeight) : gridWidth(_gridWidth), gridHeight(_gridHeight), gridData(nullptr) {

	if(this->gridWidth > 0 && this->gridHeight > 0) {

		//unsigned int gridSize = this->gridHeight * this->gridWidth;


		this->gridData = new Player**[this->gridHeight];

		for(unsigned int j = 0; j < this->gridHeight; ++j) {
			this->gridData[j] = new Player*[this->gridWidth];

			for(unsigned int i=0 ;i  < this->gridWidth;++i)
				this->gridData[j][i] = nullptr;
		}


	}

}


Grid::~Grid(void)
{

	for(unsigned int i = 0; i < this->gridHeight; ++i) {
		delete [] this->gridData[i];
	}

	delete [] this->gridData;
}

Player*** Grid::getGrid()
{
	return this->gridData;
}

int Grid::getGridWidth()
{
	return this->gridWidth;
}


int Grid::getGridHeight()
{
	return this->gridHeight;
}



Status Grid::play(Player* player, unsigned int x, unsigned int y)
{
	if(x >= this->gridWidth || y >= this->gridHeight)
		return MATCH_INCORRECT_STROKE;

	if(this->gridData[y][x] == nullptr) {

		this->gridData[y][x] = player;
		return MATCH_STROKE_DONE;
	}

	return MATCH_UNAVAILABLE_CASE;
}

Player* Grid::getWinner(unsigned int winSize)
{
	unsigned int consecutivesPion = 0;
	Player* potentialWinner = nullptr;

	for(unsigned int j=0; j < this->gridHeight; j++) {

		for(unsigned int i=0; i < this->gridWidth; i++) {

			Player* owner = this->gridData[j][i];

			if(potentialWinner != owner) {
				potentialWinner = owner;				
				consecutivesPion = 0;
			}

			consecutivesPion++;

			if(consecutivesPion == winSize && owner != nullptr)
				return potentialWinner;
		}

	}

	consecutivesPion = 0;
	potentialWinner = nullptr;
	
	for(unsigned int i=0; i < this->gridWidth; i++) {
	
		for(unsigned int j=0; j < this->gridHeight; j++) {

		

			Player* owner = this->gridData[j][i];

			if(potentialWinner != owner) {
				potentialWinner = owner;				
				consecutivesPion = 0;
			}

			consecutivesPion++;

			if(consecutivesPion == winSize && owner != nullptr)
				return potentialWinner;
		}

	}

	consecutivesPion = 0;
	potentialWinner = nullptr;

	for(unsigned int i=0; i < this->gridWidth; i++) {

		for(unsigned int k=0; k < this->gridHeight && (i+k) < this->gridWidth; k++) {

			Player* owner = this->gridData[k][i+k];

			if(potentialWinner != owner) {
				potentialWinner = owner;				
				consecutivesPion = 0;
			}

			consecutivesPion++;

			if(consecutivesPion == winSize && owner != nullptr)
				return potentialWinner;
		}

	}

	consecutivesPion = 0;
	potentialWinner = nullptr;

	for(unsigned int i=0; i < this->gridWidth; i++) {

		for(unsigned int k=0; k < this->gridHeight && (i+k) < this->gridWidth; k++) {

			Player* owner = this->gridData[k][i+k];

			if(potentialWinner != owner) {
				potentialWinner = owner;				
				consecutivesPion = 0;
			}

			consecutivesPion++;

			if(consecutivesPion == winSize && owner != nullptr)
				return potentialWinner;
		}

	}

	consecutivesPion = 0;
	potentialWinner = nullptr;

	for(unsigned int j=0; j < this->gridHeight; j++) {

		for(unsigned int k=0; k < this->gridWidth && (j+k) < this->gridHeight; k++) {

			Player* owner = this->gridData[j+k][k];

			if(potentialWinner != owner) {
				potentialWinner = owner;				
				consecutivesPion = 0;
			}

			consecutivesPion++;

			if(consecutivesPion == winSize && owner != nullptr)
				return potentialWinner;
		}

	}
	
	consecutivesPion = 0;
	potentialWinner = nullptr;

	for(unsigned int i=0; i < this->gridWidth; i++) {

		for(unsigned int k=0; k < this->gridHeight && i >= k; k++) {

			Player* owner = this->gridData[k][i-k];

			if(potentialWinner != owner) {
				potentialWinner = owner;				
				consecutivesPion = 0;
			}

			consecutivesPion++;

			if(consecutivesPion == winSize && owner != nullptr)
				return potentialWinner;
		}

	}

	
	consecutivesPion = 0;
	potentialWinner = nullptr;

	for(unsigned int j=0; j < this->gridHeight; j++) {

		for(unsigned int k=0; k < this->gridWidth && j >= k; k++) {

			Player* owner = this->gridData[j-k][k];

			if(potentialWinner != owner) {
				potentialWinner = owner;				
				consecutivesPion = 0;
			}

			consecutivesPion++;

			if(consecutivesPion == winSize && owner != nullptr)
				return potentialWinner;
		}

	}


	return nullptr;

}

void Grid::reset() {

	for(unsigned int j=0;j<this->gridHeight;j++) {
		for(unsigned int i=0;i<this->gridWidth;i++) {
			this->gridData[j][i] = nullptr;
		}
	}

}

void Grid::Debug() {
	std::cout << std::endl;
	for(unsigned int j=0;j<this->gridHeight;j++) {
		for(unsigned int i=0;i<this->gridWidth;i++) {
			Player* cell = this->gridData[j][i];
			if(cell != nullptr)
				std::cout << cell->getName().at(0) << " ";
			else
				std::cout << "  ";
		}
		std::cout << "|" << std::endl;
	}

}