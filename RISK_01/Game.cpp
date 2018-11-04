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
	//Set turn count to 0
	turn = 0;
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
	int startArmies = 23 - (players.size() - 2) * 5;
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
		char input;
		std::cout << "You currently have " << player->getNumCards() << " cards and can exchange, would you like to do so? (Y/N) ";
		std::cin >> input;
		if (input == 'Y' || input == 'y')
			troopsAvailable += player->exchange();
		else if (input == 'N' || input == 'n')
			break;
	}

	std::cout << "You have a total of " << troopsAvailable << " troops available to place.\n";

	//now we can ask the player to start placing their troops

	std::cout << "You can now start placing troops on the countries you own.\nHere is a list of countries in your possession:\n";

	player->printCountriesOwned();

	while (troopsAvailable != 0) {
		std::string countrySelectedString;
		std::cout << "You have " << troopsAvailable << " troops lefts to place, which country would you like to add troops to? ";
		std::cin >> countrySelectedString;

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

		int numTroopsToPlace;
		do {
			std::cout << "You have selected " << countrySelected->getName() << ". How many troops would you like to place on this country? (Max: " << troopsAvailable << ") : ";
			std::cin >> numTroopsToPlace;
		} while (numTroopsToPlace > troopsAvailable || numTroopsToPlace < 0);
		player->reinforce(countrySelected, numTroopsToPlace);
		std::cout << "You have placed " << numTroopsToPlace << " troops on " << countrySelected->getName() << " giving it " << countrySelected->getTroops() << " total members.\n";
		troopsAvailable -= numTroopsToPlace;
	}
}
/**Allows player passed as argument to attack*/
void Game::attack(Player* player) {

}
/**Allows player passed as argument to fortify*/
void Game::fortify(Player* player) {

}