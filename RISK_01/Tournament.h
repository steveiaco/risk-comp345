#pragma once
#include "Game.h"
#include <vector>
#include <string>

class Tournament {
private:
	/**Datatype for storing tournament victories and their details**/
	class Victory {
	public:
		/**Victory constructor*/
		Victory(Player* player, Map* map);
		/**Victory destructor*/
		~Victory();
		/**Winning player*/
		Player* player;
		/**Map that player won on*/
		Map* map;
	};

	//List of maps
	std::vector<Map*> maps;
	//List of players
	std::vector<Player*> players;
	//List of victories
	std::vector<Victory> victories;
	//Maximum number of turns per game
	int turnLimit;
	//Number of games per map
	int nbGames;

public:
	//CONSTRUCTORS
	/**Tournament constructor*/
	Tournament(std::vector<Map*> maps, std::vector<Player*> players, int numTurns, int numGames);

	//DESTRUCTOR
	/**Tournament destructor*/
	~Tournament();

	//UTILITY
	/**Start tournament*/
	void start();
	/**Display results of tournament in a table*/
	void displayResults();
};

