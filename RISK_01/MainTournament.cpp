#include "Tournament.h"
#include "Game.h"
#include "MapLoader.h"
#include "ObserverPlayerPhase.h"
#include "ObserverStats.h"
#include "AggressiveAI.h"
#include "BenevolentAI.h"
#include "HumanPlayer.h"
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

void startTournament() {
	//VARIABLES
	//vector of maps for the tournament
	std::vector<Map*> maps = std::vector<Map*>();
	int numMaps = NULL;
	//vector of players for the tournament
	std::vector<Player*> players = std::vector<Player*>();
	int numPlayers = NULL;
	//Number of games to play on each map
	int numGames = NULL;
	//Number of turns to play for until draw
	int maxTurns = NULL;

	//MAP
	//Display list of available maps
	std::cout << "Enter one of the following maps to add to the tournament:\n";
	int i = 1;
	for (auto & p : std::experimental::filesystem::directory_iterator("Maps\\"))
		if (p.path().extension() == ".map") {
			std::cout << "\t" << i << "- " << p.path().filename() << std::endl;
			i++;
		}
	std::cout << std::endl;

	//Chose number of maps to play on
	while (numMaps == NULL) {
		std::string numMapsString;
		std::cout << "Enter number of maps to play on (1 to 5): ";
		std::getline(std::cin, numMapsString);
		try {
			numMaps = std::stoi(numMapsString);
			if (numMaps < 1 || numMaps > 5)
				throw std::invalid_argument("Invalid number of maps.");
		}
		catch (std::exception& e) { //Catch invalid number of maps
			numMaps = NULL;
			std::cout << "Number of maps is invalid!\nPlease enter a valid integer value between 1 and 5.\n\n";
		}
	}

	//Get numMaps maps
	for (int i = 0; i < numMaps; i++) {
		Map* map = NULL;
		while (map == NULL) {
			//Get map name
			std::string mapName;
			std::cout << "Enter name of map to load: ";
			std::getline(std::cin, mapName);
			try {
				//Get map
				map = MapLoader::readMapFile(mapName);
				for (Map* otherMap : maps) //Make sure same map file is not used twice
					if (map->getName() == otherMap->getName())
						throw std::invalid_argument("You already chose this map.");;
			}
			catch (std::invalid_argument& e) { //Catch invalid maps
				map = NULL;
				std::cout << mapName + ".map does not define a valid map!\n";
				std::cout << e.what() << std::endl << std::endl;
			}
		}
		//Add valid map
		maps.push_back(map);
	}
	std::cout << std::endl;

	//PLAYERS
	//Keep trying to get number of players until a valid integer is provided
	while (numPlayers == NULL) {
		std::string numPlayersString;
		std::cout << "Enter number of players playing (2 to 4): ";
		std::getline(std::cin, numPlayersString);
		try {
			numPlayers = std::stoi(numPlayersString);
			if (numPlayers < 2 || numPlayers > 4)
				throw std::invalid_argument("Invalid number of players.");
		}
		catch (std::exception& e) { //Catch invalid number of players
			numPlayers = NULL;
			std::cout << "Number of players is invalid!\nPlease enter a valid integer value between 2 and 6.\n\n";
		}
	}
	std::cout << std::endl;

	//Select strategies fr players
	std::cout << "Chose strategies for each player. Choices include aggressive (1), benevolent (2), random (3), and cheater (4). Each strategy chosen must be unique.\n\n";
	bool strategiesTaken[4] = {false, false, false, false};

	for (int i = 1; i < numPlayers + 1; i++) {
		//Get choice of strategy
		int choiceOfAI = NULL;
		while (choiceOfAI == NULL) {
			std::string choiceOfAIString;
			std::cout << "Which computer strategy to you wish to attribute to player n." << i << "? ";
			std::getline(std::cin, choiceOfAIString);
			try {
				choiceOfAI = std::stoi(choiceOfAIString);
				if (choiceOfAI < 1 || choiceOfAI > 4)
					throw std::invalid_argument("Choice of startegy must be a valid integer.");
				if (strategiesTaken[choiceOfAI-1] == true)
					throw std::invalid_argument("Strategies must all be unique.");
			}
			catch (std::exception &e) { //Catch invalid strategy
				choiceOfAI = NULL;
				std::cout << "Choice of strategy is invalid!\nPlease enter a valid integer value between 1 and 4 (that has not already been chosen).\n\n";
			}
		}
		//Player is added only if the Entry is correct AND it is not already chosen
		strategiesTaken[choiceOfAI-1] = true;
		switch (choiceOfAI) {
		case 1:
			players.push_back(new Player("Aggressive", new AggressiveAI()));
			break;
		case 2:
			players.push_back(new Player("Benevolent", new BenevolentAI()));
			break;
		case 3:
			players.push_back(new Player("Random", new RandomAI()));
			break;
		case 4:
			players.push_back(new Player("Cheater", new CheaterAI()));
			break;
		default:
			throw std::invalid_argument("There should be no way of reaching here.");
			break;
		}
	}
	std::cout << std::endl;

	//Keep trying to get number of games per map
	while (numGames == NULL) {
		std::string nbGamesString;
		std::cout << "Enter the number of games for each map in the tournament (1 to 5): ";
		std::getline(std::cin, nbGamesString);
		try {
			numGames = std::stoi(nbGamesString);
			if (numGames < 1 || numGames > 5)
				throw std::invalid_argument("Invalid number of games per map");
		}
		catch (std::exception& e) { //Catch invalid number of games per map
			numGames = NULL;
			std::cout << "Number of games per map is invalid!\nPlease enter a valid integer value between 1 and 5.\n\n";
		}
	}
	std::cout << std::endl;

	//Keep trying to get max number of turns per game
	while (maxTurns == NULL) {
		std::string turnMaxString;
		std::cout << "Enter the maximum number of turns in a game until it is declared a draw (10 to 50): ";
		std::getline(std::cin, turnMaxString);
		try {
			maxTurns = std::stoi(turnMaxString);
			if (maxTurns < 10 || maxTurns > 50)
				throw std::invalid_argument("Invalid number of maximum turns.");
		}
		catch (std::exception& e) { //Catch invalid number of turns
			maxTurns = NULL;
			std::cout << "Number of maximum turns is invalid!\nPlease enter a valid integer value between 10 and 50.\n\n";
		}
	}
	std::cout << std::endl;

	//Creation of tournament
	Tournament tournament = Tournament(maps, players, maxTurns, numGames);
	//Begin to run tournament
	tournament.start();
	tournament.displayResults();
	//We are done, delete everything
	players.clear();
	maps.clear();
}

void startGame() {
	//Display list of available maps
	std::cout << "Enter one of the following maps to play (without extension):\n";
	int i = 1;
	for (auto & p : std::experimental::filesystem::directory_iterator("Maps\\"))
		if (p.path().extension() == ".map") {
			std::cout << "\t" << i << "- " << p.path().filename() << std::endl;
			i++;
		}
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
		std::cout << "Enter number of players playing (2 to 6): ";
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
	for (int i = 1; i < numPlayers + 1; i++) {
		std::string playerName;
		std::cout << "Enter name of player " << i << ": ";
		std::getline(std::cin, playerName);
		players.push_back(new Player(playerName, NULL));
	}
	std::cout << std::endl;
	//Create deck
	Deck* deck = new Deck(map);
	//Create game
	Game game = Game(players, map, deck, NULL);
	game.setSwapType(true);
	//Attach observers (order is important)
	ObserverStats statsObserver = ObserverStats(&game);
	ObserverPlayerPhase gameObserver = ObserverPlayerPhase(&game);
	//Start up game
	game.start();
	//We are done, delete everything
	players.clear();
	delete deck;
	delete map;
}

int main() {
	//Display welcome
	std::cout << "=======================================================================\n";
	std::cout << "\tRISK GAME             \n";
	std::cout << "=======================================================================\n";
	std::cout << std::endl;

	//Choice between normal game and tournament
	int gameModeChoice = NULL;
	while (gameModeChoice == NULL) {
		std::string gameModeChoiceString;
		std::cout << "Would you like to play a normal game (1) or a tournament (2)? ";
		std::getline(std::cin, gameModeChoiceString);
		try {
			gameModeChoice = std::stoi(gameModeChoiceString);
			if (gameModeChoice != 1 && gameModeChoice != 2)
				throw std::invalid_argument("Invalid gamemode.");
		}
		catch (std::exception& e) { //Catch invalid choice
			gameModeChoice = NULL;
			std::cout << "Choice is invalid!\nPlease enter a valid integer value between 1 and 2.\n\n";
		}
	}
	std::cout << std::endl;

	if (gameModeChoice == 2)
		startTournament();
	else if (gameModeChoice == 1)
		startGame();
	return 0;
}