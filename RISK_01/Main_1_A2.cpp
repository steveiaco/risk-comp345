#include "Game.h"
#include "MapLoader.h"
#include <iostream>
#include <string>
#include <vector>

//Load the game map and players up. Start a game.
int main() {

	std::cout << "===================================\n";
	std::cout << "             RISK GAME             \n";
	std::cout << "===================================\n";

	std::cout << std::endl;
	//Keep trying to get map until a valid map is returned
	Map* map = NULL;
	while (map == NULL) {
		//Get map name
		std::string mapName;
		std::cout << "Enter name of map to load: ";
		std::getline(std::cin, mapName);
		try {
			map = MapLoader::readMapFile(mapName);
		}
		catch (std::invalid_argument& e) { //Catch invalid maps
			std::cout << mapName + ".map does not define a valid map!\n";
			std::cout << e.what() << std::endl << std::endl;
		}
	}
	std::cout << std::endl;
	//Keep trying to get number of players until a valid integer is returned
	int numPlayers = NULL;
	while (numPlayers == NULL) {
		std::string numPlayersString;
		std::cout << "Enter number of players playing: ";
		std::getline(std::cin, numPlayersString);
		try {
			numPlayers = std::stoi(numPlayersString);
			if (numPlayers < 2 || numPlayers>6)
				throw std::invalid_argument("Invalid number of players.");
		}
		catch (std::exception& e) { //Catch invalid maps
			numPlayers = NULL;
			std::cout << "Number of players is invalid!\nPlease enter a valid integer value between 2 and 6.\n\n";
		}
	}
	std::cout << std::endl;
	//Create player objects
	std::vector<Player*> players = std::vector<Player*>();
	for (int i = 1; i < numPlayers+1; i++) {
		std::string playerName;
		std::cout << "Enter name of player " << i << ": ";
		std::getline(std::cin, playerName);
		players.push_back(new Player(playerName));
	}
	std::cout << std::endl;
	//Create deck
	Deck* deck = new Deck(map);

	//Display results
	map->display();
	std::cout << std::endl;
	deck->display();
	std::cout << std::endl;
	for (Player* player : players) {
		std::cout << player->getName() << ": " << std::endl;
		player->displayDice();
		player->displayHand();
		std::cout << std::endl;
	}
	//Delete everything
	for (Player* player : players) {
		delete player;
	}
	delete map;
	delete deck;
	map = NULL;
	deck = NULL;
}