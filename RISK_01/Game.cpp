#include "Game.h"
#include <string>

//CONSTRUCTORS
/**Constructs a controller from a list of players on a given map*/
Game::Game(std::vector<Player*> listOfPlayers, Map* theControllerMap, Deck* theDeck) {
	//Make sure number of players is valid (we will have problems otherwise)
	if (listOfPlayers.size() < 2 || listOfPlayers.size() > 6)
		throw std::invalid_argument("Invalid nmber of players. Game can only be played by 2-6 players.");
    players = listOfPlayers;
    map = theControllerMap;
	deck = theDeck;
	turn = 0;
}

//DESTRUCTOR
/**Controller destructor*/
Game::~Game(){
	delete map;
	delete deck;
	for (Player* player : players)
		delete player;
	std::cout << "Controller deleted.";
}

//UTILITIES
/**Set up game (assign countries, randomize play order)*/
void Game::start() {
	//Set turn count to 1
	turn = 1;
	//Randomize order of players vector (vector is a copy of the original, we don't have to worry about the original also being shuffled)
	randomizeOrderOfPlay();
	//Assign each country to a player
	map->assignCountries(players);
	//Prompt players to assign starting armies to countries
	assignArmies();
	//Launch game loop
	runGameLoop();
}
/**Runs main game loop until game is over*/
void Game::runGameLoop() {
	//Run loop until a winner is determined
	Player* winner = NULL;
	while (!winner) {
		//Display turn
		std::cout << "==================================\n";
		std::cout << "              TURN " << turn << "              \n";
		std::cout << "==================================\n\n";
		//Loop over players
		for (Player* player : players) 
			//Player can only play if they are still in the game (they have countries left to play with)
			if (!player->hasLost()) {
				//Display player
				std::cout << "==================================\n";
				std::cout << "              " << player->getName() << ":              \n";
				std::cout << "==================================\n\n";
				//Let player do their turn
				reinforce(player);
				attack(player);
				fortify(player);
			}
		//Increment turn counter
		turn++;
		//Check for winner
		winner = map->getWinner();
	}
}
/**Randomizes order of play (shuffles list of players)*/
void Game::randomizeOrderOfPlay() {

	std::cout << "Before shuffle: " << std::endl;
	for (Player* player : players)
		std::cout << player->getName() << std::endl;
	std::cout << std::endl;

	//Shuffle array of players (randomize turn order)
	auto rng = std::default_random_engine{};
	std::shuffle(players.begin(), players.end(), rng);

	std::cout << "After shuffle: " << std::endl;
	for (Player* player : players)
		std::cout << player->getName() << std::endl;
	std::cout << std::endl;
}
void Game::assignArmies() {
	//Number of starting armies depends on number of players (Note that constructor ensures that players size is appropriate, we do not have to check for that)
	int startArmies = 8 - (players.size() - 2) * 5;
	//Players take turns placing their starting armies until they run out. They will automatically have placed at least one army on each country assigned to them at this point. Their remaining number of troop will be somewhere between the total start amount and 0.
	for (int i = 0; i < startArmies; i++)
		//Players must take turns. Otherwise, the player placing their armies first is at a disadvantage (the other players already know his/her strategy when their chance to place troops comes)
		for (Player* player : players) {
			//Make sure that player has troops left (some of players troops will already have been placed on the countries assigned to them by default, that complicates things)
			int armiesLeft = startArmies - i - player->getNumberOfCountries();
			if (0 < armiesLeft) {
				std::cout << player->getName() << ", it is your turn to place troops. The following countries are yours: \n\n";
				player->printCountriesOwned();
				std::cout << std::endl;
				//Ensure the input is valid (keep prompting until it is)
				while (true) {
					std::string countryName;
					std::cout << "You have " << armiesLeft << " troops remaining. Enter the name of a country where you would place one: ";
					std::getline(std::cin, countryName); std::cout << std::endl;
					try {
						player->reinforce(map->getCountry(countryName), 1);
						break; //If here, input was valid, break out of loop
					}
					catch (std::invalid_argument& e) {
						std::cout << countryName << " is not a valid country!\n" << e.what() << std::endl << std::endl; //If here, input was invalid, loop again
					}
				}
			}
		}
}
/**Allows player passed as argument to reinforce*/
void Game::reinforce(Player* player) {
	int troopsAvailable = 0;

	//get the number of troops available from the countries the player owns and the contienent values
	troopsAvailable += player->calculateTroopsAwarded();

	//check whether the player must exchange cards (has more than 6 cards)
	while (player->mustExchange()) {
		std::cout << "You have " << player->getNumCards() << ", a number which is greater than 5, therefore here is an automatic exchange.\n";
		troopsAvailable += player->exchange();
	}

	//now we will check whether the player can exchange, if they can then we will ask if they want to exchange
	while (player->canExchange()) {
		std::string input;
		std::cout << "You currently have " << player->getNumCards() << " cards and can exchange, would you like to do so? (Y/N) ";
		std::getline(std::cin, input); std::cout << std::endl;
		if (input == "Y" || input == "y")
			troopsAvailable += player->exchange();
		else if (input == "N" || input == "n")
			break;
	}

	std::cout << "You have a total of " << troopsAvailable << " troops available to place.\n";

	//now we can ask the player to start placing their troops

	std::cout << "You can now start placing troops on the countries you own.\nHere is a list of countries in your possession:\n";

	player->printCountriesOwned();

	while (troopsAvailable != 0) {
		std::string countrySelectedString;
		std::cout << "You have " << troopsAvailable << " troops lefts to place, which country would you like to add troops to? ";
		std::getline(std::cin, countrySelectedString); std::cout << std::endl;

		Country* countrySelected;
		try {
			countrySelected = map->getCountry(countrySelectedString);
		} catch (std::invalid_argument e) {
			std::cout << "Country does not exist, try again.\n";
			continue;
		} if (!player->ownsCountry(countrySelected)) {
			std::cout << "You do not own this country, try again.\n";
			continue;
		}

		std::string numTroopsToPlaceString;
		int numTroopsToPlace;
		do {
			std::cout << "You have selected " << countrySelected->getName() << ". How many troops would you like to place on this country? (Max: " << troopsAvailable << ") : ";
			std::getline(std::cin, numTroopsToPlaceString); std::cout << std::endl;
			numTroopsToPlace = std::stoi(numTroopsToPlaceString);
		} while (numTroopsToPlace > troopsAvailable || numTroopsToPlace < 0);
		player->reinforce(countrySelected, numTroopsToPlace);
		std::cout << "You have placed " << numTroopsToPlace << " troops on " << countrySelected->getName() << " giving it " << countrySelected->getTroops() << " total members.\n";
		troopsAvailable -= numTroopsToPlace;
	}
}
/**Allows player passed as argument to attack*/
void Game::attack(Player* player) {
	//main loop used for attack phase
	while (true) {
		//Check if player would like to attack
		std::cout << "Would you like to attack? (y/n) ";
		std::string input;
		std::getline(std::cin, input); std::cout << std::endl;
		//ask if player would like to continue attacking
		if (input == "N" || input == "n")
			break;
		//Display options
		if (!player->displayAttackable())
			break;
		//Get valid input and make attack
		Country* attackingCountry = NULL;
		Country* defendingCountry = NULL;
		int attackerRoll;
		int defenderRoll;
		while (true) {
			//Get attack from
			std::string attackFrom;
			std::cout << "\nPlease select a country to attack from (cancel to cancel): ";
			std::getline(std::cin, attackFrom); std::cout << std::endl;
			if (attackFrom == "cancel")
				break;
			try { attackingCountry = map->getCountry(attackFrom); }
			catch (std::invalid_argument e) { 
				std::cout << e.what() << std::endl;
				continue;
			}
			//Get attack to
			std::string attackTo;
			std::cout << "\nPlease select a country to attack (cancel to cancel): ";
			std::getline(std::cin, attackTo); std::cout << std::endl;
			if (attackFrom == "cancel")
				break;
			try { defendingCountry = map->getCountry(attackTo); }
			catch (std::invalid_argument e) {
				std::cout << e.what() << std::endl;
				continue;
			}
			//Get number of dice for attacker
			std::string attackerRollString;
			std::cout << player->getName() << ", how many dice would you like to use to attack? [1-" << ((attackingCountry->getTroops() - 1 > 3) ? 3 : (attackingCountry->getTroops() - 1)) << "] ";
			std::getline(std::cin, attackerRollString); std::cout << std::endl;
			try { attackerRoll = std::stoi(attackerRollString); } 
			catch (std::invalid_argument& e) { 
				std::cout << "Input must be a valid integer value."; 
				continue; 
			}
			//Get number of dice for defender
			std::string defenderRollString;
			std::cout << defendingCountry->getOccupant()->getName() << ", how many dice would you like to use to defend? [1-" << ((defendingCountry->getTroops() > 2) ? 2 : (defendingCountry->getTroops())) << "] ";
			std::getline(std::cin, attackerRollString); std::cout << std::endl;
			try { defenderRoll = std::stoi(defenderRollString); }
			catch (std::invalid_argument& e) {
				std::cout << "Input must be a valid integer value.";
				continue;
			}
			//Make attack
			bool attackSuccessful; //Stores whether attacker has taken over defending country
			try { attackSuccessful = player->attack(attackingCountry, defendingCountry, attackerRoll, defenderRoll); }
			catch (std::invalid_argument& e) {
				std::cout << e.what() << std::endl;
			}
			//If attack is successful, prompt transfer of troops
			if (attackSuccessful) {
				int numTroopsToMove;
				std::string numTroopsToMoveString;
				std::cout << player->getName() << " has successfully invaded " << defendingCountry->getName() << std::endl;
				do {
					std::cout << player->getName() << ", " << attackerRoll << " troop(s) automatically moved into " << defendingCountry->getName() << ", how many additional troops would you like to move into " << defendingCountry->getName() << "? [0-" << attackingCountry->getTroops() - 1 << "] ";
					std::getline(std::cin, numTroopsToMoveString); std::cout << std::endl;
					try { numTroopsToMove = std::stoi(numTroopsToMoveString); }
					catch (std::invalid_argument& e) {
						std::cout << "Number of troops must be a valid integer value.";
					}
				} while (numTroopsToMove >= attackingCountry->getTroops() || numTroopsToMove < 0);
				//Make the change
				defendingCountry->addTroops(numTroopsToMove);
				attackingCountry->addTroops(-numTroopsToMove);
			}
		}
	}
}
/**Allows player passed as argument to fortify*/
void Game::fortify(Player* player) {

}