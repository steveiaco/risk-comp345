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

int main() {
	//Display welcome
	std::cout << "=======================================================================\n";
	std::cout << "\tRISK GAME             \n";
	std::cout << "=======================================================================\n";
	std::cout << std::endl;

	//Choice between normal game and tournament
	int gameModeChoice;
	do {
		std::cout << "Would you like to play a normal game (1) or a tournament (2). Select the corresponding number\n";
		std::cin >> gameModeChoice;
	} while (gameModeChoice != 1 || gameModeChoice != 2)

	if (gameModeChoice == 2)
	{
		//vector of maps for the tournament
		std::vector<Map*> mapsOfTournament;

		//Display list of available maps
		std::cout << "Enter one of the following maps to add to the tournament:\n";
		int i = 1;
		for (auto & p : std::experimental::filesystem::directory_iterator("Maps\\"))
			if (p.path().extension() == ".map") {
				std::cout << "\t" << i << "- " << p.path().filename() << std::endl;
				i++;
			}
		std::cout << std::endl;
		//Keep trying to get map until a valid map is returned
		do {
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
			//*************Push the chosen map into the vector of maps IF IT IS NOT THERE ALREADY (NEED HELP HERE***********)
			mapsOfTournament.push_back(map);

		} while() // goes out of loop when all of the maps are selected
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
			catch (std::exception& e) { //Catch invalid number of players
				numPlayers = NULL;
				std::cout << "Number of players is invalid!\nPlease enter a valid integer value between 2 and 6.\n\n";
			}
		}
		std::cout << std::endl;
		//Create player objects and AI
		std::vector<Player*> players = std::vector<Player*>();
		AggressiveAI* aggressive = new AggressiveAI();
		BenevolentAI* benevolent = new BenevolentAI();
		CheaterAI* cheater = new CheaterAI();
		RandomAI random = new RandomAI();
		std::string choiceOfAI = NULL;

		//used to check if the strategy has already been chosen
		bool aggressiveStatus =0, benevolentStatus =0, cheaterStatus =0, randomStatus =0;

		for (int i = 1; i < numPlayers + 1; i++) {
			std::cout << "Which computer strategy to you wish to attribute to the AI n." << i << "?\n";
			std::cout << "Enter Aggressive, Benevolent, Cheater or Random. A strategy can only be chosen once.\n"
			cin >> choiceOfAI;

			//PLayer is added only if the Entry is correct AND it is not already chosen
			if (choiceOfAI =="Aggressive" && aggressiveStatus == 0) {
				players.push_back(new Player("Aggressive", aggressive))
					aggressiveStatus = 1;
			}
			else if (choiceOfAI == "Benevolent" && benevolentStatus == 0) {
				players.push_back(new Player("Benevolent", benevolent))
					benevolentStatus = 1;
			}
			else if (choiceOfAI =="Cheater" && cheaterStatus == 0) {
				players.push_back(new Player("Cheater", cheater))
					cheaterStatus = 1;
			}
			else if (choiceOfAI =="Random" && randomStatus == 0) {
				players.push_back(new Player("Random", random))
					randomStatus = 1;
			}
			else {
				std::cout<< "Error. The entry is either invalid or the strategy has already been chosen"
			}

		}
		std::cout << std::endl;
		
		//Keep trying to get number of games per map of turns until a valid integer is returned
		int nbGames = NULL;
		while (nbGames = NULL) {
			std::string nbGamesString;
			std::cout << "Enter the number of games for each map in the tournament:";
			std::getline(std::cin, nbGamesString);
			try {
				nbGames = std::stoi(nbGamesString);
				if (nbGames < 1 || nbGames>5)
					throw std::invalid_argument("Invalid number of games per map");
			}
			catch (std::exception& e) { //Catch invalid maps
				numPlayers = NULL;
				std::cout << "Number of games per map is invalid!\nPlease enter a valid integer value between 1 and 5.\n\n";
			}
		}

		//Keep trying to get max number of turns until a valid integer is returned
		int turnMax = NULL;
		while (turnMax= NULL) {
			std::string turnMaxString;
			std::cout << "Enter the maximum number of turns in a game until it is declared a draw:";
			std::getline(std::cin, turnMaxString);
			try {
				turnMax = std::stoi(turnMaxString);
				if (turnMax < 10 || turnMax>50)
					throw std::invalid_argument("Invalid number of maximum turns.");
			}
			catch (std::exception& e) { //Catch invalid maps
				numPlayers = NULL;
				std::cout << "Number of maximum turns is invalid!\nPlease enter a valid integer value between 10 and 50.\n\n";
			}
		}
		//Vector of Game Objects
		std::vector<Game*> gamesOfTournament;

		//For each map in the Map vector, create a deck and a game. Add it to the game vector
		for (Map* map : mapOfTournament)
		{
			Deck* deck = new Deck(map);
			Game* game = Game(players, map, deck);
			game.setSwapType(false);

			//*******MISSING OBSERVERS, NEED HELP HERE****************

			gamesOfTournament.push_back(game);
		}
		//Creation of tournament
		Tournament tournament = new Tournament(mapsOfTournament, gamesOfTournament, turnMax, nbGames);
		//Begin to run tournament
		tournament.start();
	}
	return 0;
}


