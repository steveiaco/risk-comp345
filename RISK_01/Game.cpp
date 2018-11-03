#include "Game.h"

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
}

/**Randomizes order of play (shuffles list of players)*/
void Game::randomizeOrderOfPlay() {
	std::cout << "Before shuffle: " << std::endl;
	for (Player* player : players)
		std::cout << player->getName() << std::endl;

	//Shuffle array of players (randomize turn order)
	auto rng = std::default_random_engine{};
	std::shuffle(players.begin(), players.end(), rng);

	std::cout << "After shuffle: " << std::endl;
	for (Player* player : players)
		std::cout << player->getName() << std::endl;
}
void Game::assignArmies() {
	//Number of starting armies depends on number of players (Note that constructor ensures that players size is appropriate, we do not have to check for that)
	int startArmies = 40 - (players.size() - 2) * 5;
}