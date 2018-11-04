#include "Game.h"
#include "MapLoader.h"
#include <iostream>
#include <string>
#include <vector>

int main() {

	std::cout << "===================================" << std::endl;
	std::cout << "             RISK GAME             " << std::endl;
	std::cout << "===================================";

	//Keep trying to get map until a valid map is returned
	Map* map = NULL;
	while (map == NULL) {
		//Get map name
		std::string mapName;
		std::cout << std::endl << "Enter name of map to load: ";
		std::getline(std::cin, mapName); std::cout << std::endl;
		try {
			map = MapLoader::readMapFile(mapName);
		}
		catch (std::invalid_argument& e) { //Catch invalid maps
			std::cout << mapName + ".map does not define a valid map!\n";
			std::cout << e.what() << std::endl;
		}
	}
	//Keep trying to get number of players until a valid integer is returned
	int numPlayers = NULL;
	while (numPlayers == NULL) {
		std::string numPlayersString;
		std::cout << std::endl << "Enter number of players playing: ";
		std::getline(std::cin, numPlayersString); std::cout << std::endl;
		try {
			numPlayers = std::stoi(numPlayersString);
			if (numPlayers < 2 || numPlayers>6)
				throw std::invalid_argument("Invalid number of players.");
		}
		catch (std::exception& e) { //Catch invalid maps
			numPlayers = NULL;
			std::cout << "Number of players is invalid!\nPlease enter an integer value between 2 and 6.\n";
		}
	}
	//Create player objects
	std::vector<Player*> players = std::vector<Player*>();
	for (int i = 1; i < numPlayers+1; i++) {
		std::string playerName;
		std::cout << "Enter name of player " << i << ": ";
		std::getline(std::cin, playerName); std::cout << std::endl;
		players.push_back(new Player(playerName));
	}
	//Create deck
	Deck* deck = new Deck(map);

	//Create game
	Game game = Game(players, new Map(), deck);
	//Start up game
	game.start();
}