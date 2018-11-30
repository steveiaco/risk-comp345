#include "Tournament.h"

//VICTORY STUFF
/**Victory constructor*/
Tournament::Victory::Victory(Player* player, Map* map) {
	this->player = player;
	this->map = map;
}
/**Victory destructor*/
Tournament::Victory::~Victory() {}

//CONSTRUCTOR
/**Tournament constructor. Counstructs a tournament of nbGames per map on a list of maps with a list of players where each game has, at most, turnLimit number of turns.*/
Tournament::Tournament(std::vector<Map*> maps, std::vector<Player*> players, int turnLimit, int nbGames) {
	this->maps = maps;
	this->players = players;
	this->turnLimit = turnLimit;
	this->nbGames = nbGames;
}

//DESTRUCTOR
/**Tournament destructor. Only clears up list of victories. We might still need the other attributes elsewhere.*/
Tournament::~Tournament() {
	victories.clear();
}

void Tournament::start() {
	//Iterate over maps
	for (Map* map : maps) {
		//Variables
		Player* winner = NULL;
		Deck* deck = new Deck(map);
		Game game = Game(players, map, deck, turnLimit);
		game.setPauseToRead(false);
		game.setSwapType(false);
		//Play the number of games specified. Keep count of winners.
		for (int i = 0; i < nbGames; i++)
			victories.push_back(Victory(game.start(), map));
	}
}

void Tournament::displayResults()
{
	//Set table specifications
	int cellWidth = 20;

	//first display the tournament options used
	system("CLS");
	std::cout << "Tournament Results: \n";
	std::cout << "\nM: ";
	for (std::vector<Map*>::iterator map = maps.begin(); map != maps.end() - 1; map++) std::cout << (*map)->getName() << ", "; std::cout << (*(maps.end() - 1))->getName();
	std::cout << "\nP: ";
	for (std::vector<Player*>::iterator player = players.begin(); player != players.end() - 1; player++) std::cout << (*player)->getName() << ", "; std::cout << (*(players.end() - 1))->getName();
	std::cout << "\nG: " << nbGames;
	std::cout << "\nD: " << turnLimit;
	std::cout << std::endl << std::endl;

	//then display the first row of the table
	std::cout << std::string(cellWidth, ' ');
	for (int i = 1; i <= nbGames; i++)
		std::cout << "| Game " << i << std::string(cellWidth-6, ' ');
	std::cout << std::endl;

	//print the following rows, which have the name of the map and the winners for that map for each game
	for (Map* map: maps) {
		std::string mapName = map->getName();
		std::cout << mapName << std::string(cellWidth-mapName.length(), ' ');
		for(Victory victory : victories) //Find and print all winners on that map in order
			if(victory.map == map)
				if (victory.player) {
					std::string winnerName = victory.player->getName();
					std::cout << "| " << winnerName << std::string(cellWidth - winnerName.length(), ' ');
				} else
					std::cout << "| Draw" << std::string(cellWidth - 4, ' ');
		std::cout << std::endl;
	}
}
