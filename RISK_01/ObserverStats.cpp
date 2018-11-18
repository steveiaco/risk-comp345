#include "ObserverStats.h"

//CONSTRUCTOR
/**Constructs ObserverStats objects for a given game. Adds the game as an attribute and attaches itself to the game.*/
ObserverStats::ObserverStats(Game* game) { 
	this->game = game; 
	game->attach(this); 
	players = game->getPlayers();
	map = game->getMap();
}

//DESTRUCTOR
/**Destructor for ObserverStats objects*/
ObserverStats::~ObserverStats() { game->detach(this); }

//UTILITY
/**Update observer with updates from subject (good for updating visuals)*/
void ObserverStats::update() {
	system("CLS");
	//If the game is over, display a congratulations and some fun stats, otherwise, display game stats
	if (game->getCurrentState()==END)
		displayVictory();
	else
		displayStats();
}
/**Display stats for current game*/
void ObserverStats::displayStats() {
	//Width of conquest bars (precision)
	int barWidth = 40;
	//Display the state of the map (this can sometimes clutter the screen, use it if you want)
	//map->display();
	//std::cout << std::endl;
	//Get necessary figures
	int numberOfPlayers = players.size();
	int numberOfCountries = map->getNumberOfCountries();
	int numberOfContinents = map->getNumberOfContinents();
	//We need to know the length of the longest name (for spacing reasons)
	int longestName = 0;
	for (Player* player : players)
		longestName = (player->getName().size() > longestName) ? player->getName().size() : longestName;
	int namingSpace = (int) longestName*2;
	//Display some "world domination" stats in the form of a bar graph for countries
	std::cout << "COUNTRIES OWNED (out of " << numberOfCountries << "):\n";
	//Only display stats for active players (not eliminated ones)
	for (Player* player : players) if (!player->hasLost()) {
		int countriesOwned = player->getNumberOfCountries();
		std::string barTitle = player->getName() + "(" + std::to_string(countriesOwned) + ")";
		//Calculate percentage of countries owned
		float percentCountriesOwned = countriesOwned * 1. / numberOfCountries;
		std::cout << barTitle + std::string(namingSpace- barTitle.size(), ' ');
		std::cout << "|" << std::string((int)(percentCountriesOwned * barWidth), '*') << std::string(barWidth - (int)(percentCountriesOwned * barWidth), ' ') << "| " << countriesOwned * 100. / numberOfCountries << "%\n";
	}
	std::cout << std::endl;
	//Display some "world domination" stats in the form of a bar graph for continents
	std::cout << "CONTINENTS OWNED (out of " << numberOfContinents << "):\n";
	for (Player* player : players) if (!player->hasLost()) {
		int continentsOwned = player->getNumberOfContinents();
		std::string barTitle = player->getName() + "(" + std::to_string(continentsOwned) + ")";
		//Calculate percentage of continents owned
		float percentContinentsOwned = continentsOwned * 1. / numberOfContinents;
		std::cout << barTitle + std::string(namingSpace - barTitle.size(), ' ');
		std::cout << "|" << std::string((int)(percentContinentsOwned * barWidth), '*') << std::string(barWidth - (int)(percentContinentsOwned * barWidth), ' ') << "| " << continentsOwned * 100. / numberOfContinents << "%\n";
	}
	std::cout << std::endl;
	//Display number of cards in each hand
	std::cout << "CARDS IN HAND:\n";
	for (Player* player : players) if (!player->hasLost())
		std::cout << player->getName() << std::string(namingSpace - player->getName().size(), ' ') << ":   " << player->getNumCards() << std::endl;
	std::cout << std::endl;
}
/**Display congratulations to victor and display dice stats (might as well since we have them)*/
void ObserverStats::displayVictory() {
	Player* winner = map->getWinner();
	//Congratulate the victor
	std::cout << "Congratulations on winning the game, " << winner->getName() << "!\n";
	std::cout << "It took you " << game->getCurrentTurn() << " turn(s) to win the game.\n\n";
	//Display dice stats
	std::cout << "Along the way, some proved luckier than others...\nHere are how the rolls played out for each player:\n";
	std::cout << std::endl;
	for (Player* player : players) {
		std::cout << player->getName() << ": \n";
		player->displayDice();
	}
}