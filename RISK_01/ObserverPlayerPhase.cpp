#include "ObserverPlayerPhase.h"

//CONSTRUCTOR
/**Constructs ObserverPlayerPhase objects for a given game. Adds the game as an attribute and attaches itself to the game.*/
ObserverPlayerPhase::ObserverPlayerPhase(Game* game) { this->game = game; game->attach(this); }

//DESTRUCTOR
/**Destructor for ObserverPlayerPhase objects*/
ObserverPlayerPhase::~ObserverPlayerPhase(){ game->detach(this); }

//UTILITY
/**Update observer with updates from subject (good for updating visuals).*/
void ObserverPlayerPhase::update(){
	//Display relevant information
	switch (game->getCurrentState()) {
		case SETUP:
			diplayHeader();
			displaySetup();
			break;
		case REINFORCE:
			diplayHeader();
			displayReinforce();
			break;
		case ATTACK:
			diplayHeader();
			displayAttack();
			break;
		case FORTIFY:
			diplayHeader();
			displayFortify();
			break;
		case END:
			displayEnd();
			break;
		default:
			std::cout << "\tError?";
	}
}
/**Display header for current game state (Good for if you don't want extra info)*/
void ObserverPlayerPhase::diplayHeader(){
	//Get name of current player
	std::string playerName = game->getCurrentPlayer()->getName();
	std::cout << "=======================================================================\n";
	//Display current turn
	std::cout << "\tTURN " << game->getCurrentTurn() << "\n";
	//Diplay the appropriate header for the current state
	switch(game->getCurrentState()){
		case SETUP: 
			std::cout << "\tPlayer " + playerName + ": Setup Phase\n"; break;
        case REINFORCE: 
			std::cout << "\tPlayer " + playerName + ": Reinforcement Phase\n";break;
        case ATTACK: 
			std::cout << "\tPlayer " + playerName + ": Attack Phase\n";break;
        case FORTIFY: 
			std::cout << "\tPlayer " + playerName + ": Fortification Phase\n";break;
		case END: 
			std::cout << "\tGame over\n\t" + playerName + " is the victor!\n"; break;
		default: 
			std::cout << "\tError?";
    }
	std::cout << "=======================================================================\n\n";
}
/**Display information for setup phase*/
void ObserverPlayerPhase::displaySetup() {
	//Get current player
	Player* crrtPlayer = game->getCurrentPlayer();
	//Number of starting armies depends on number of players
	int startArmies = 40 - (game->getPlayers().size() - 2) * 5;
	//Display a message
	std::cout << "To begin, it is custom that " << game->getPlayers().size() << " players each receive " << startArmies << " armies.\n\nEvery country must have at least one army on it at all times (countries must always be occupied).\nSome amount of those armies will already have been placed on the countries assigned to you at random (1 per country).\nThe rest are for you to use as you see fit.\n\n";
	std::cout << game->getCurrentPlayer()->getName() << ", it is your turn to place troops. The following countries are yours: \n";
	game->getCurrentPlayer()->printCountriesOwned("\t");
	std::cout << std::endl;
}
/**Display information for reinforce phase*/
void ObserverPlayerPhase::displayReinforce() {
}
/**Display information for attack phase*/
void ObserverPlayerPhase::displayAttack() {
}
/**Display information for fortify phase*/
void ObserverPlayerPhase::displayFortify() {
}
/**Display information for end phase*/
void ObserverPlayerPhase::displayEnd() {
}

