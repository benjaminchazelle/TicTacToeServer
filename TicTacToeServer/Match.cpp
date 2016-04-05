#include "Match.h"
#include "Player.h"
#include "Logic.h"

#include "Status.h"

unsigned int Match::LastIDGiven = 0;


Match::Match(unsigned int _gridWidth, unsigned int _gridHeight, unsigned int _winSize, std::vector<Participant> _participantsList, Logic* _logic) : state(WAITING_PLAYERS), winSize(3), grid(new Grid(_gridWidth, _gridHeight)), currentPlayer(nullptr), logic(_logic), currentID(++LastIDGiven) {

	if(_winSize > 3)
		this->winSize = _winSize;

	for(std::vector<Participant>::iterator it = _participantsList.begin(); it!=_participantsList.end(); ++it)
	{
		this->inviteParticipant(*it);
	}

}

Match::~Match(void)
{
	delete this->grid;


	for(std::vector<Participant>::iterator it = this->participantsList.begin(); it!= this->participantsList.end(); ++it)
	{
		if((*it).player != nullptr)
			(*it).player->onMatchRemoved(this);
	}

}

Grid* Match::getGrid()
{
	return this->grid;
}

Status Match::inviteParticipant(Participant invited_participant)
{
	//Si la partie n'a pas commencé
	//Si l'invitation désigne un joueur particulier, Si le joueur invité existe et qu'il n'est pas encore dans la partie ()
	//Ou si l'invitation concerne n'importe qui

	if(this->state != WAITING_PLAYERS)
		return Status::MATCH_EVER_STARTED_OR_FINISHED;

	bool PlayerInvitation_valid = invited_participant.player != nullptr && invited_participant.state == INVITED_PLAYER && !this->ThisPlayerIsParticipant(invited_participant.player);
	bool AnyoneInvitation_valid = invited_participant.state == INVITED_ANYONE;
	bool Invitation_valid = PlayerInvitation_valid || AnyoneInvitation_valid;

	if(!Invitation_valid)
		return Status::INVALID_INVITATION;


	if(AnyoneInvitation_valid)
		invited_participant.player = nullptr;

	this->participantsList.push_back(invited_participant);

	if(PlayerInvitation_valid)
		invited_participant.player->onMatchInvited(this);

	return Status::PARTICIPANT_ADDED;



}


bool Match::onMatchAccepted(Player* player)
{
	//Si la partie n'a pas commencé
	//Si le joueur existe

	if(this->state != WAITING_PLAYERS)
		return false;

	if(player == nullptr)
		return false;

	std::vector<Participant>::iterator place_it = findPlaceToParticipate(player);

	if(place_it == this->participantsList.end()) 
		return false;


	(*place_it).player = player;
	(*place_it).state = ParticipantState::PLAYING;

	bool startMatch = true;

	for(std::vector<Participant>::iterator it = this->participantsList.begin(); it!=this->participantsList.end(); ++it)
	{
		if((*it).state == ParticipantState::INVITED_ANYONE || (*it).state == ParticipantState::INVITED_PLAYER ){

			startMatch = false;
			break;
		}

	}

	if(startMatch) {
		this->state = PROGRESS;
		this->currentPlayer = this->participantsList.at(0).player;
	}

	return true;




}

bool Match::onMatchDeserted(Player* player)
{

	std::vector<Participant>::iterator participant = this->findParticipant(player);

	if(participant == this->participantsList.end())
		return false;

	if(participant->state != ParticipantState::PLAYING)
		return false;

	participant->player->onMatchRemoved(this);

	if(this->state == MatchState::WAITING_PLAYERS) {

		this->participantsList.erase(participant);

	}
	else {

		participant->state = ParticipantState::LEFT;

		if(participant->player == this->currentPlayer) {

			std::vector<Participant>::iterator nextParticipantPlayer = getNextParticipantPlayer(participant);

			if(nextParticipantPlayer != this->participantsList.end()) {
				this->currentPlayer = nextParticipantPlayer->player;
			}
			else {
				this->closeMatch();
			}


		}

	}

	return true;



}



std::vector<Participant>::iterator Match::getNextParticipantPlayer(std::vector<Participant>::iterator fromParticipant) {

	for(std::vector<Participant>::iterator it=fromParticipant+1; it!=this->participantsList.end(); ++it) {

		if((*it).state == ParticipantState::PLAYING) {

			return it;

		}

	}


	for(std::vector<Participant>::iterator it=this->participantsList.begin(); it!=fromParticipant; ++it) {

		if((*it).state == ParticipantState::PLAYING) {

			return it;

		}

	}

	return  this->participantsList.end();

}



Status Match::play(Player* player, unsigned int x, unsigned int y)
{
	if(this->state != MatchState::PROGRESS)
		return Status::MATCH_NOT_STARTED;

	if(player == nullptr)
		return Status::PLAYER_NOT_EXISTS;

	std::vector<Participant>::iterator participant = findParticipant(player);

	if(participant == this->participantsList.end())
		return Status::MATCH_PLAYER_IS_NOT_PARTICIPANT;

	if(participant->player != this->currentPlayer)
		return Status::MATCH_NOT_PLAYED_BY_CURRENT_PLAYER;

	if(!this->grid->play(player, x, y))
		return Status::MATCH_INVALID_STROKE;

	std::vector<Participant>::iterator nextParticipantPlayer = this->getNextParticipantPlayer(participant);

	//joueur alone, la partie est sensé être arrêté avant
	if(nextParticipantPlayer == this->participantsList.end()) {

		this->state = MatchState::FINISHED;

	}
	else {
		this->currentPlayer = nextParticipantPlayer->player;
	}

	Player* winner = this->grid->getWinner(this->winSize);

	if(winner != nullptr) {
		this->state = MatchState::FINISHED;
		this->currentPlayer = nullptr;
	}

	return Status::MATCH_STROKE_DONE;
}

std::vector<Participant>::iterator Match::findPlaceToParticipate(Player* player) {


	if(this->state != WAITING_PLAYERS)
		return this->participantsList.end();

	if(player == nullptr)
		return this->participantsList.end();


	//Chercher une place de participant atitré au joueur (ou non atitré en dernier recours)

	std::vector<Participant>::iterator it = this->participantsList.begin();

	std::vector<Participant>::iterator place_it = this->participantsList.end();


	for(; it!=this->participantsList.end(); ++it) {

		if((*it).state == INVITED_ANYONE) {
			place_it = it;
		}
		else if((*it).state == INVITED_PLAYER && (*it).player == player) {
			return it;
		}

	}

	return place_it;

}

Player* Match::getCurrentPlayer()
{
	return this->currentPlayer;
}

std::vector<Participant> Match::getParticipantsList()
{
	return this->participantsList;
}

MatchState Match::getState()
{
	return this->state;
}

Participant Match::getWinner()

{
	this->grid->getWinner(this->winSize);
	Participant dbg;
	return dbg;
}

bool Match::canPlayerJoin(Player* player)
{
	return findPlaceToParticipate(player) != this->participantsList.end(); 
}

std::vector<Participant>::iterator Match::findParticipant(Player* player) {

	std::vector<Participant>::iterator it = this->participantsList.begin();

	for(; it!=this->participantsList.end(); ++it) {
		if((*it).player == player)
			return it;
	}

	return it;
}

bool Match::ThisPlayerIsParticipant(Player* player)
{
	return this->findParticipant(player) != this->participantsList.end();
}

void Match::resetMatch(Player* player)
{
	if(this->state == MatchState::WAITING_PLAYERS)
		return;

	if(!ThisPlayerIsParticipant(player))
		return;


	this->state = MatchState::WAITING_PLAYERS;

	for(std::vector<Participant>::iterator it = this->participantsList.begin(); it!=this->participantsList.end(); ++it)
	{
		if((*it).state != ParticipantState::LEFT)
			(*it).state = ParticipantState::PLAYING;
	}

	this->grid->reset();

	//TODO notifier


} 

void Match::closeMatch()
{

	for(std::vector<Participant>::iterator it = this->participantsList.begin(); it!=this->participantsList.end(); ++it) {

		if(it->state != ParticipantState::LEFT) {

			it->player->onMatchRemoved(this);
			it->state = ParticipantState::LEFT;


		}

	}

	this->logic->onMatchClosed(this);
}

unsigned int Match::getWinSize() {

	return this->winSize;

};

unsigned int Match::getId() {
	return this->currentID;
}