#include "Tournament.h"



Tournament::Tournament(std::vector<Map*> map, std::vector<Game*> game, int turn, int nbGame)
{
	maps = map;
	games = game;
	turnLimit = turn;
	nbGames = nbGame;
}


Tournament::~Tournament()
{
}

void TournamentStart()
{
	//for each game, start it
	for (Games* actualGame : games)
	{
		//create a player object that will receive the winner returned by the start function;
		Player* player;
		player = actualGame.start();
		
		//Push the name of the player into the WinningPlayer vector, or draw if it was a draw
		if (player == NULL)
			winningPlayers.push_back("Draw");
		else winningPlayers.push_back(player.getName());

	}
}

void TournamentsResultsDisplay()
{
	//first display the first row of the table
	std::cout << std::endl;
	std::cout << "\t\t |";
	for (int i = 0; i < nbGames; i++)
	{
		cout << "Game " << i << "\t |";
	}
	std::cout << std::endl;

	//print the following rows, which have the name of the map and the winner for that map
	for (int x = 0; x < maps.size(); x++)
	{
		std::cout << maps[x].getName << "\t |";   //Print name of map first
		for (int y = 0; y < games.size(); y++)	  //Print winners of all games
		{
			std::cout << winningPlayers[(x*nbGames) + y] << "\t |";
		}
		std::cout << std::endl;
	}
}
