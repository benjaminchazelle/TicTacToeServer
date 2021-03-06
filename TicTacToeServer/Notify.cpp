#include "Query/Notify.h"
#include <sstream>


Notify::Notify(void)
{
}


Notify::~Notify(void)
{
}


void Notify::setIdentity(Server* server, setIdentityNotifyQuery query) {

	std::string notify = "";

	QueryUtils::headerBuilding(notify);

	QueryUtils::setValue(notify, "Notify", "setIdentity");

	QueryUtils::setValue(notify, "ErrorCode", "100");

	QueryUtils::setValue(notify, "ErrorMessage", "You should choose your pseudo");

	QueryUtils::footerBuilding(notify);

	server->sendTo(notify, query.clients);

}

void Notify::joinMatch(Server* server, joinMatchNotifyQuery query){

	std::string notify = "";

	QueryUtils::headerBuilding(notify);

	QueryUtils::setValue(notify, "Notify", "joinMatch");

	QueryUtils::setValue(notify, "MatchId", query.match->getId());

	QueryUtils::setValue(notify, "ErrorCode", "60-0");

	QueryUtils::setValue(notify, "ErrorMessage", "You can join this game");

	QueryUtils::footerBuilding(notify);

	server->sendTo(notify, query.clients);

}

void Notify::playMatch(Server* server, playMatchNotifyQuery query) {

	std::string notify = "";

	QueryUtils::headerBuilding(notify);

	QueryUtils::setValue(notify, "Notify", "playMatch");

	QueryUtils::setValue(notify, "MatchId", query.match->getId());

	std::stringstream grid_stream;

	for (int j = 0; j < query.match->getGrid()->getGridHeight(); j++){

		for (int i = 0; i < query.match->getGrid()->getGridWidth(); i++){

			if (i != 0 || j != 0)
				grid_stream << "|";

			if (query.match->getGrid()->getGrid()[j][i] == nullptr){

				grid_stream << "|";

			}
			else
			{

				grid_stream << query.match->getGrid()->getGrid()[j][i]->getName();

			}

		}

	}

	QueryUtils::setValue(notify, "Grid", grid_stream.str());

	std::stringstream playersList_stream;
	std::string tmpPlayer = "";
	int i = 0;

	std::vector<Participant> participantsList =  query.match->getParticipantsList();

	for (std::vector<Participant>::iterator it = participantsList.begin(); it != participantsList.end(); ++it)
	{

		if (it->player == nullptr) continue;

		if (it->player == query.clients.at(0)){

			playersList_stream << "*";

		}
		else if (it->state == LEFT){

			playersList_stream << "!";

		}
		else if (it->state == INVITED_PLAYER || it->state == INVITED_ANYONE){

			playersList_stream << "?";

		}

		if (it->state == ParticipantState::INVITED_ANYONE){

			tmpPlayer = "ANYBODY";

		}
		else
		{

			tmpPlayer == it->player->getName();

		}

		if (i == 0){

			playersList_stream << tmpPlayer;

		}

		playersList_stream << "|" << tmpPlayer;

		i++;

	
	}

	QueryUtils::setValue(notify, "Players", playersList_stream.str());

	QueryUtils::setValue(notify, "ErrorCode", "70-0");

	QueryUtils::setValue(notify, "ErrorMessage", "Match changed");

	QueryUtils::footerBuilding(notify);

	server->sendTo(notify, query.clients);

}

