#include <ctime>
#include <fstream>
#include <iostream>

#include "Server.h"

using namespace std;

int main(int argc, char *argv[])
{
	/*
	vector<Match*> matchsList;
	
	Player* alice = new Player();
	Player* bob = new Player();
	Player* chuck = new Player();

	vector<Player*> noplayer_match3x3;

	Match* nomatch3x3 = new Match(3, 3, 3, noplayer_match3x3);
	matchsList.push_back(nomatch3x3);

	vector<Player*> players_match3x3;
	players_match3x3.push_back(alice);
	players_match3x3.push_back(bob);

	Match* match3x3 = new Match(3, 3, 3, players_match3x3);
	matchsList.push_back(match3x3);

	vector<Player*> players_match5x5;
	players_match5x5.push_back(alice);
	players_match5x5.push_back(bob);
	players_match5x5.push_back(chuck);

	Match* match5x5 = new Match(5, 5, 4, players_match5x5);
	matchsList.push_back(match5x5);

	match5x5->play(alice, 0, 0);
	match5x5->play(alice, 0, 0);//peut pas rejouer
	match5x5->play(bob, 0, 0); //non autorisé
	match5x5->play(bob, 0, 1);
	match5x5->play(bob, 0, 2);//peut pas rejouer
	match5x5->play(chuck, 0, 3);

	//match5x5->close(match3x3);



	delete nomatch3x3;
	delete match3x3;
	delete match5x5;

	delete alice;
	delete bob;
	delete chuck;*/

	/*
	Server* tictactoe = new Server();

	delete tictactoe;
	*/
/*
	Logic* logic = new Logic();

	Player* alice = new Player("Alice");
	Player* bob = new Player("Bob");
	Player* chuck = new Player("Chuck");
	Player* derik = new Player("Derik");

	std::vector<Participant> pool;

	Participant alice_p;
		alice_p.player = alice;
		alice_p.state = INVITED_PLAYER;

	Participant bob_p;
		bob_p.player = bob;
		bob_p.state = INVITED_PLAYER;

	Participant chuck_p;
		chuck_p.player = chuck;
		chuck_p.state = INVITED_PLAYER;

	Participant derik_p;
		derik_p.player = derik;
		derik_p.state = INVITED_PLAYER;

	Participant any_p;
		any_p.player = nullptr;
		any_p.state = INVITED_ANYONE;


	pool.push_back(alice_p);
	pool.push_back(bob_p);

	pool.push_back(any_p);

	Match* match = new Match(5, 5, 3, pool, logic);



	//match->play(bob, 1, 0); //partie non commencée
	
	alice->acceptMatchInvitation(match);
	bob->acceptMatchInvitation(match);
	derik->acceptMatchInvitation(match);

	bob->quitMatch(match);


	match->play(alice, 2, 1);
	match->play(bob, 4, 0);



	match->play(derik, 3, 0);


	match->play(alice, 3, 2);
	match->play(bob, 4, 1);
	match->play(derik, 3, 1);

	match->play(alice, 4, 3);
	match->play(bob, 4, 4);
	match->play(derik, 3, 4);



	match->getGrid()->Debug();
	
	
	match->getWinner();
	

	delete match;

	delete alice;
	delete bob;
	delete chuck; */
	/*
	Logic logic(nullptr);

	std::string setIdentityOKRequest = "TICTACTOE/1.0\r\nRequest: setIdentity\r\nPseudo: CapitaineBanana\r\n\r\n\r\n";
	
	std::string createMatchOKRequest = "TICTACTOE/1.0\r\nRequest: createMatch\r\nGridWidth: 5\r\nGridHeight: 6\r\nPseudoPlayers: jeff03|ostro|ANYBODY\r\nWinSize: 3\r\n\r\n\r\n";
	std::string createMatchKORequest = "TICTACTOE/1.0\r\nRequest: createMatch\r\nGridWidth: {grid_width}\r\nGridHeight: {grid_height}\r\nPseudoPlayers: {players}\r\nWinSize: {winsize}\r\n\r\n\r\n";
	logic.routeRequest(nullptr, createMatchKORequest);
	*/
	Server tictactoeserver;
	tictactoeserver.start();
}