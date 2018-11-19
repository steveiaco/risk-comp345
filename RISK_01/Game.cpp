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
}

//UTILITIES
/**Set up game (assign countries, randomize play order)*/
void Game::start() {
	currentState = SETUP;
	system("CLS");
	//Display a message
	std::cout << "=======================================================================\n";
	std::cout << "\tSETUP              \n";
	std::cout << "=======================================================================\n";
	std::cout << "Welcome, " << (*players.begin())->getName(); 
	//We will print the player names nicely
	for (std::vector<Player*>::iterator player = players.begin()+1; player != players.end()-1; player++) std::cout << ", " << (*player)->getName(); std::cout << " and " << (*(players.end()-1))->getName();
	std::cout << ", to RISK, a game of chance and strategy!\n"; //"Every turn, you will receive an amount of armies proportional to your holdings.\nPlace those armies in strategic locations and use them to take territories from your enemies.\nTake a territory to get a card on that turn that can later be cashed in for more armies!\nEliminate an enemy player to receive their cards.\n\nA champion is determined when all other players have been eliminated.\n\n";
	std::cout << std::endl;
	//Randomize order of players vector (vector is a copy of the original, we don't have to worry about the original also being shuffled)
	randomizeOrderOfPlay();
	//Assign each country to a player
	map->assignCountries(players);
	map->display();
	//Prompt player to press to continue
	std::cout << std::endl;
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
	for (std::vector<Player*>::iterator player = players.begin(); player != players.end() - 1; player++) std::cout << (*player)->getName() << " > "; std::cout << (*(players.end() - 1))->getName();
	std::cout << std::endl << std::endl;
}
void Game::assignArmies() {
	//Number of starting armies depends on number of players (Note that constructor ensures that players size is appropriate, we do not have to check for that)
	int startArmies = 40 - (players.size() - 2) * 5;
	//Players take turns placing their starting armies until they run out. They will automatically have placed at least one army on each country assigned to them at this point. Their remaining number of troop will be somewhere between the total start amount and 0.
	for (int i = 0; i < startArmies; i++)
		//Players must take turns. Otherwise, the player placing their armies first is at a disadvantage (the other players already know his/her strategy when their chance to place troops comes)
		for (Player* player : players) {
			//Make sure that player has troops left (some of players troops will already have been placed on the countries assigned to them by default, that complicates things)
			int armiesLeft = startArmies - i - player->getNumberOfCountries();
			if (0 < armiesLeft) {
				currentPlayer = player;
				notify();
				//Prompt player to select a country
				Country* countryChosen;
				std::cout << "You have " << armiesLeft << " troops remaining. Enter the name of a country where you would place one: ";
				countryChosen = player->askSetup();
				//Returns null if player chose to skip
				if (countryChosen == NULL)
					return;
				player->reinforce(countryChosen, 1);
				pause();
			}
		}
}
/**Allows player passed as argument to reinforce*/
void Game::reinforce(Player* player) {
	player->promptReinforce();
	pause();
}
/**Allows player passed as argument to attack*/
void Game::attack(Player* player) {
	//Give the player a card for their first success
	bool firstSuccess = true;
	//skip if player can not attack
	if (player->canAttack()) {
		std::cout << player->getName() << ": Would you like to attack? (y/n): ";
		while (player->askAttack()) {
			//If first success is currently false and attack is successful, player should receive a card
			if (firstSuccess = player->promptAttack() && firstSuccess == true) {
				firstSuccess = false;
				player->addCard(deck->draw());
				std::cout << player->getName() << " has received a card for their first victory this round." << std::endl;
			}
			pause();
			notify();
			std::cout << player->getName() << ": Would you like to attack? (y/n): ";
		}
	}
	else {
		pause();
		notify();
	}
}
/**Allows player passed as argument to fortify*/
void Game::fortify(Player* player) {
	player->promptFortify();
	pause();
}
/**Pause the output and wait for user to read*/
void Game::pause() {
	//Prompt player to press to continue
	std::cout << std::endl;
	std::cout << "Hit enter to continue...";
	std::string temp;
	std::getline(std::cin, temp);
}