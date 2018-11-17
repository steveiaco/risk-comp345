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
}

//UTILITIES
/**Set up game (assign countries, randomize play order)*/
void Game::start() {
	currentState = SETUP;
	//Display a message
	std::cout << "==================================\n";
	std::cout << "SETUP              \n";
	std::cout << "==================================\n";
	std::cout << "Welcome, " << (*players.begin())->getName(); 
	//We will print the player names nicely
	for (std::vector<Player*>::iterator player = players.begin()+1; player != players.end()-1; player++) std::cout << ", " << (*player)->getName(); std::cout << " and " << (*(players.end()-1))->getName();
	std::cout << ", to RISK, a game of chance and strategy!\nEvery turn, you will receive an amount of armies proportional to your holdings.\nPlace those armies in strategic locations and use them to take territories from your enemies.\nTake a territory to get a card on that turn that can later be cashed in for more armies!\nEliminate an enemy player to receive their cards.\n\nA champion is determined when all other players have been eliminated.\n\n";
	//Randomize order of players vector (vector is a copy of the original, we don't have to worry about the original also being shuffled)
	randomizeOrderOfPlay();
	//Assign each country to a player
	map->assignCountries(players);
	map->display();
	//Prompt player to press to continue
	std::cout << "Hit enter to continue...";
	std::string temp;
	std::getline(std::cin, temp);
	//Prompt players to assign starting armies to countries
	assignArmies();
	//Launch game loop
	runGameLoop();
}
/**Runs main game loop until game is over*/
void Game::runGameLoop() {
	//Run loop until a winner is determined
	while (!map->getWinner()) {
		//Increment turn counter
		turn++;
		//Loop over players
		for (Player* player : players) {
			//Player can only play if they are still in the game (they have countries left to play with)
			if (!player->hasLost()) {
				//Let player do their turn
				currentPlayer = player;
				//REINFORCE
				currentState = REINFORCE;
				notify();
				reinforce(player);
				//ATTACK
				currentState = ATTACK;
				notify();
				attack(player);
				//FORTIFY
				currentState = FORTIFY;
				notify();
				fortify(player);
			}
		}
	}
	//GAME OVER
	currentState = END;
	notify();
}
/**Randomizes order of play (shuffles list of players)*/
void Game::randomizeOrderOfPlay() {

	//Shuffle array of players (randomize turn order)
	auto rng = std::default_random_engine{};
	std::shuffle(players.begin(), players.end(), rng);

	//Show new order clearly
	std::cout << "Player order (after shuffle): ";
	for (Player* player : players)
		std::cout << player->getName() << " > ";
	std::cout << std::endl << std::endl;
}
void Game::assignArmies() {
	//Number of starting armies depends on number of players (Note that constructor ensures that players size is appropriate, we do not have to check for that)
	int startArmies = 40 - (players.size() - 2) * 5;
	//Display a message
	std::cout << "To begin, it is custom that " << players.size() << " players each receive " << startArmies << " armies.\nEvery country must have at least one army on it at all times (countries must always be occupied).\nSome amount of those armies will already have been placed on the countries assigned to you at random (1 per country).\nThe rest are for you to use as you see fit.\n\n";
	//Players take turns placing their starting armies until they run out. They will automatically have placed at least one army on each country assigned to them at this point. Their remaining number of troop will be somewhere between the total start amount and 0.
	for (int i = 0; i < startArmies; i++)
		//Players must take turns. Otherwise, the player placing their armies first is at a disadvantage (the other players already know his/her strategy when their chance to place troops comes)
		for (Player* player : players) {
			currentPlayer = player;
			notify();
			//Make sure that player has troops left (some of players troops will already have been placed on the countries assigned to them by default, that complicates things)
			int armiesLeft = startArmies - i - player->getNumberOfCountries();
			if (0 < armiesLeft) {
				std::cout << player->getName() << ", it is your turn to place troops. The following countries are yours: \n";
				player->printCountriesOwned();
				//Ensure the input is valid (keep prompting until it is)
				while (true) {
					std::string countryName;
					std::cout << "You have " << armiesLeft << " troops remaining. Enter the name of a country where you would place one: ";
					std::getline(std::cin, countryName);
					//We will allow user to skip this part of setup for debugging purposes. To skip, user simply enters "skip".
					if (countryName == "skip") {
						std::cout << std::endl;
						return;
					} try {
						player->reinforce(map->getCountry(countryName), 1);
						break; //If here, input was valid, break out of loop
					}
					catch (std::invalid_argument& e) {
						std::cout << countryName << " is not a valid country!\n" << e.what() << std::endl; //If here, input was invalid, loop again
					}
				}
				std::cout << std::endl;
			}
		}
}
/**Allows player passed as argument to reinforce*/
void Game::reinforce(Player* player) {
	int troopsAvailable = 0;

	//get the number of troops available from the countries the player owns and the contienent values
	troopsAvailable += player->calculateTroopsAwarded();

	//Show player their cards
	player->displayHand();

	//check whether the player must exchange cards (has more than 6 cards)
	while (player->mustExchange()) {
		std::cout << "You have " << player->getNumCards() << ", cards. You can hold no more than 5 at a time. Here is an automatic exchange.\n";
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

	//now we can ask the player to start placing their troops
	std::cout << "You have a total of " << troopsAvailable << " troops available to place.\n";
	std::cout << "You can now start placing troops on the countries you own.\nHere is a list of countries in your possession:\n";
	player->printCountriesOwned();

	while (troopsAvailable != 0) {
		std::string countrySelectedString;
		std::cout << "You have " << troopsAvailable << " troops left to place, which country would you like to add troops to? ";
		std::getline(std::cin, countrySelectedString); std::cout << std::endl;

		Country* countrySelected;
		try {
			countrySelected = map->getCountry(countrySelectedString);
		}
		catch (std::invalid_argument e) {
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
	bool attacking = true;
	bool firstSuccess = true; //We want to give player a card for first victory
	while (attacking) {

		//if there is a winner, then we skip the attack phase completely
		if (map->getWinner())
			break;

		std::cout << player->getName() << ", would you like to attack? (y/n) ";
		std::string input;
		std::getline(std::cin, input); std::cout << std::endl;
		//ask if player would like to continue attacking
		if (input == "N" || input == "n")
			break;

		//Show player their options. Break if no options exist.
		if (!player->displayAttackable()) {
			std::cout << std::endl;
			break;
		}
		std::cout << std::endl;

		//get a valid attacking country and store it in attackingCountry
		Country* attackingCountry = NULL;
		while (attackingCountry == NULL) {
			std::string inp;
			std::cout << player->getName() << ": please select a country to attack from (cancel to cancel): ";
			std::getline(std::cin, inp); std::cout << std::endl;
			if (inp == "cancel")
				break;
			//Make sure country is valid
			try {
				attackingCountry = map->getCountry(inp);
				//check if player owns the attacking country
				if (!player->ownsCountry(attackingCountry)) {
					attackingCountry = NULL;
					throw std::invalid_argument("You do not own this country.");
				}
				//if country has less than two troops then it cannot attack,  ask again
				if (attackingCountry->getTroops() < 2) {
					attackingCountry = NULL;
					throw std::invalid_argument("This country does not have enough troops to attack.");
				}
				//if the country has no attackable neighbors, then continue and ask user to input another country to attack from
				bool listValid = attackingCountry->canAttack();
				if (!listValid) {
					attackingCountry = NULL;
					throw std::invalid_argument("This country has no attackable neighbors.");
				}
			}
			catch (std::invalid_argument e) {
				std::cout << e.what() << std::endl;
			}
		}
		if (attackingCountry == NULL)
			continue;

		//get a valid attacking country and store it in defendingCountry
		Country* defendingCountry = NULL;
		while (defendingCountry == NULL) {
			std::string inp = std::string();
			std::cout << player->getName() << ": please select a country to attack (cancel to cancel): ";
			std::getline(std::cin, inp); std::cout << std::endl;

			try {
				if (inp == "cancel")
					break;
				else {
					defendingCountry = map->getCountry(inp);

					//if the attacking player owns the selected defending country, then it is an invalid selection
					if (player->ownsCountry(defendingCountry)) {
						defendingCountry = NULL;
						throw std::invalid_argument("You cannot attack your own country.");
					}

					//defending country must be a neighbor of the attacking country
					if (!defendingCountry->isNeighbor(attackingCountry)) {
						defendingCountry = NULL;
						throw std::invalid_argument("Country must be a neighbor.");
					}

				}
			}
			catch (std::invalid_argument e) {
				std::cout << e.what() << std::endl;
			}
		}
		if (defendingCountry == NULL)
			continue;

		//query attacker for number of dice
		std::string attackerRollString;
		int attackerRoll = NULL;
		while (attackerRoll == NULL) {
			std::cout << player->getName() << ": how many dice would you like to use to attack? [1-" << ((attackingCountry->getTroops() - 1 > 3) ? 3 : (attackingCountry->getTroops() - 1)) << "] ";
			std::getline(std::cin, attackerRollString); std::cout << std::endl;
			try {
				attackerRoll = std::stoi(attackerRollString);
			}
			catch (std::invalid_argument& e) {
				std::cout << "Invalid input! Input must be a valid integer value.\n";
				attackerRoll = NULL;
				continue;
			}
			if (attackerRoll <= 0 || attackerRoll >= attackingCountry->getTroops() || attackerRoll > 3) {
				std::cout << "Invalid input! Input must be between 1 and " << ((attackingCountry->getTroops() - 1 > 3) ? 3 : (attackingCountry->getTroops() - 1)) << ".\n";
				attackerRoll = NULL;
				continue;
			}
		}

		//query defender for number of dice
		std::string defenderRollString;
		int defenderRoll = NULL;
		while (defenderRoll == NULL) {
			std::cout << defendingCountry->getOccupant()->getName() << ": how many dice would you like to use to defend? [1-" << ((defendingCountry->getTroops() > 2) ? 2 : (defendingCountry->getTroops())) << "] ";
			std::getline(std::cin, defenderRollString); std::cout << std::endl;
			try {
				defenderRoll = std::stoi(defenderRollString);
			}
			catch (std::invalid_argument& e) {
				std::cout << "Invalid input! Input must be a valid integer value.\n";
				defenderRoll = NULL;
				continue;
			}
			if (defenderRoll < 1 || defenderRoll > defendingCountry->getTroops() || defenderRoll > 2) {
				std::cout << "Invalid input! Input must be between 1 and " << ((defendingCountry->getTroops() > 2) ? 2 : (defendingCountry->getTroops())) << ".\n";
				defenderRoll = NULL;
				continue;
			}
		}

		//if we get here, then we have successfully selected an attacker and attackee, move on to calling the attack function.
		bool attackSuccessful = false; //stores whether attacker has taken over defending country
		try {
			attackSuccessful = player->attack(attackingCountry, defendingCountry, attackerRoll, defenderRoll);
		}
		catch (std::invalid_argument e) {
			std::cout << e.what();
			exit(1);
		}

		if (attackSuccessful) {
			int numTroopsToMove = NULL;
			std::string numTroopsToMoveString;
			std::cout << player->getName() << " has successfully invaded " << defendingCountry->getName() << std::endl;
			if (firstSuccess) {
				firstSuccess = false;
				player->addCard(deck->draw());
				std::cout << player->getName() << " has received a card for their first victory this round." << std::endl;
			}
			std::cout << std::endl;
			while (numTroopsToMove == NULL) {
				std::cout << player->getName() << ": " << attackerRoll << " troop(s) automatically moved into " << defendingCountry->getName() << ", how many additional troops would you like to move into " << defendingCountry->getName() << "? [0-" << attackingCountry->getTroops() - 1 << "] ";
				std::getline(std::cin, numTroopsToMoveString); std::cout << std::endl;
				try {
					numTroopsToMove = std::stoi(numTroopsToMoveString);
					if (numTroopsToMove >= attackingCountry->getTroops() || numTroopsToMove < 0) {
						std::cout << "Invalid input! Input must be at least 0 and less than " << attackingCountry->getTroops() << ".\n";
						numTroopsToMove = NULL;
						continue;
					}
					break;
				}
				catch (std::invalid_argument& e) {
					std::cout << "Invalid input! Input must be a valid integer value.\n";
					numTroopsToMove = NULL;
					continue;
				}
			}
			defendingCountry->addTroops(numTroopsToMove);
			attackingCountry->addTroops(-numTroopsToMove);
		}
	}
}
/**Allows player passed as argument to fortify*/
void Game::fortify(Player* player) {

	while (true) {

		//Ask if player would like to fortify
		std::cout << player->getName() << ": would you like to fortify? (y/n) ";
		std::string input;
		std::getline(std::cin, input); std::cout << std::endl;
		if (input == "N" || input == "n")
			break;

		//Display owned countries
		std::cout << player->getName() << ": you may fortify from/to the following countries.\n";
		player->printCountriesOwned();

		/*GET VALID MOVE FROM COUNTRY*/
		Country* moveFrom = NULL;
		while (moveFrom == NULL) {
			std::string inp;
			std::cout << std::endl << player->getName() << ": please select a country to move players from (cancel to cancel): ";
			std::getline(std::cin, inp); std::cout << std::endl;
			if (inp == "cancel")
				break;
			try {
				moveFrom = map->getCountry(inp);
				//check if player owns the country
				if (!player->ownsCountry(moveFrom)) {
					moveFrom = NULL;
					throw std::invalid_argument("You do not own this country.");
				}
				//moveFrom must have enough armies
				if (moveFrom->getTroops() < 2) {
					moveFrom = NULL;
					throw std::invalid_argument("Country must have more than one army on it.");
				}
			}
			catch (std::invalid_argument e) {
				std::cout << e.what();
			}
		}
		//If player canceled before moveFrom could be set, restart
		if (moveFrom == NULL)
			continue;

		std::cout << "You may fortify " << moveFrom->getName() << "'s neighboring countries.\n";
		moveFrom->display();
		Country* moveTo = NULL;
		/*GET VALID MOVE TO COUNTRY*/
		while (moveTo == NULL) {
			std::string inp = std::string();
			std::cout << std::endl << player->getName() << ": please select a country to move armies to (cancel to cancel): ";
			std::getline(std::cin, inp); std::cout << std::endl;
			try {
				if (inp == "cancel")
					break;
				moveTo = map->getCountry(inp);
				//moveFrom must be a neighbor to moveTo
				if (!moveTo->isNeighbor(moveFrom)) {
					moveTo = NULL;
					throw std::invalid_argument("Country must be a neighbor.");
				}
				//Player must own destination
				if (!player->ownsCountry(moveTo)) {
					moveTo = NULL;
					throw std::invalid_argument("You do not own this country.");
				}
			}
			catch (std::invalid_argument e) {
				std::cout << e.what();
			}
		}
		if (moveTo == NULL)
			continue;

		/*QUERY FOR NUMBER OF TROOPS TO MOVE*/
		std::string moveNumTroopsString;
		int moveNumTroops = NULL;
		while (moveNumTroops == NULL) {
			std::cout << player->getName() << ": how many troops would you like to move from " << moveFrom->getName() << " to " << moveTo->getName() << " ? [1 - " << (moveFrom->getTroops() - 1) << "] (cancel to cancel): ";
			std::getline(std::cin, moveNumTroopsString); std::cout << std::endl;
			if (moveNumTroopsString == "cancel")
				break;
			//Make sure input is valid int
			try { moveNumTroops = std::stoi(moveNumTroopsString); }
			catch (std::invalid_argument& e) {
				std::cout << "Invalid input. Input must be a valid integer value.\n";
				moveNumTroops = NULL;
				continue;
			}
			//Make sure input is within valid range
			if (moveNumTroops < 1 || moveNumTroops >(moveFrom->getTroops() - 1)) {
				std::cout << "Invalid input. Can only move a number of troops between 1 and " << (moveFrom->getTroops() - 1) << ".\n";
				moveNumTroops = NULL;
				continue;
			}
		}
		if (moveNumTroops == NULL)
			continue;

		//Make the move
		player->fortify(moveFrom, moveTo, moveNumTroops);
		std::cout << player->getName() << ": successfully moved " << moveNumTroops << " troop(s) from " << moveFrom->getName() << " to " << moveTo->getName() << ".\n";
		break;
	}
}