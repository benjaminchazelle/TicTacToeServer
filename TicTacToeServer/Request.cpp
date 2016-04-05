#include "Query/Request.h"
#include "Query/Response.h"

#include "Errors.h"

#include <iostream>

Request::Request(void)
{

}


Request::~Request(void)
{
}

void Request::setIdentity(Server* server, setIdentityRequestQuery query) {

	//Tester si le pseudo est mal formaté

	//Tester si le pseudo est déja pris

	std::cout << "*setIdentity" << std::endl;
}

void Request::getIdentity(Server* server, getIdentityRequestQuery query) {

	getIdentityResponseQuery response;

	std::vector<Player*> clientsTarget;
	clientsTarget.push_back(query.sender);

	Errors errors;
	errors.addError(478, 65, "dfndkjfgnjdkf");;

	response.clients = clientsTarget;
	response.pseudo = query.sender->getName();
	response.queryErrors = errors;

	Response::getIdentity(server, response);

	std::cout << "*getIdentity" << std::endl;
}

void Request::createMatch(Server* server, createMatchRequestQuery query) {
	
	//Tester la taille de la grille

	//Tester la taille de la winsize, supérieur ou égale à 3, et que cette valeur soit possible à atteindre
	//Ex : dans une grille 3 x 3, on ne peut pas aligner 4 pions

	//Tester si les players sont valides, pseudos bien formatés...

	std::cout << "*createMatch" << std::endl;
}

void Request::getMatchList(Server* server, getMatchListRequestQuery query) {

	//Aucun test

	std::cout << "*getMatchList" << std::endl;
}

void Request::getMatchInformation(Server* server, getMatchInformationRequestQuery query) {

	//Tester si le match existe

	std::cout << "*getMatchInformation" << std::endl;
}

void Request::joinMatch(Server* server, joinMatchRequestQuery query) {

	//Tester si le match existe

	//Tester si le mode de suivit existe "PLAYER" ou "SPECTATOR"

	//Tester si le joueur est invité dans la partie

	//Tester si il y a assez dez place dans la partie (dans le cas où l'utilisateur pouvait rejoindre la partie?)

	std::cout << "*joinMatch" << std::endl;
}

void Request::playMatch(Server* server, playMatchRequestQuery query) {

	//Tester si la partie est finie

	//Tester si c'est le tour du joueur

	//Tester si les coordonnées sont valides, comprises dans le plateau ...

	//Tester si la case est occupée

	std::cout << "*playMatch" << std::endl;
}

void Request::resetMatch(Server* server, resetMatchRequestQuery query) {

	//Tester si le match existe

	std::cout << "*resetMatch" << std::endl;
}

void Request::quitMatch(Server* server, quitMatchRequestQuery query) {

	//Tester si le match existe

	std::cout << "*quitMatch" << std::endl;
}

void Request::getPlayerInformation(Server* server, getPlayerInformationRequestQuery query) {
	
	//Tester si le pseudo est au bon format

	//Tester si le joueur existe

	std::cout << "*getPlayerInformation" << std::endl;
}