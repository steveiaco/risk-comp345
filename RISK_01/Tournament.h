#pragma once
#include "Game.h"
#include <vector>
#include <string>

class Tournament
{
private:
	//List of maps
	std::vector<Map*> maps;

	//List of games
	std::vector<Game*> games;

	//List of winning players names
	std::vector<std::string> winningPlayers;

	//Maximum number of turn allowed
	int turnLimit;

	//Number of games per map
	int nbGames;

public:
	Tournament(std::vector<Map*> map, std::vector<Game*> game, int turn, int nbGame);
	~Tournament();
	void TournamentStart();
	void TournamentResultsDisplay();
};

