#include "Player.h"

unsigned int Player::LastIDGiven = 0;

Player::Player(void) : currentID(++LastIDGiven)
{
}


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

bool Player::acceptMatchInvitation(Match* match) {

	if(match == nullptr)
		return false;

	if(this->haveThisMatch(match))
		return false;

	if(!match->onMatchAccepted(this)) 
		return false;

	this->matchesList.push_back(match);
	return true;
}

bool Player::quitMatch(Match* match) {

	if(match == nullptr)
		return false;

	if(!match->onMatchDeserted(this))
		return false;

	return true;

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