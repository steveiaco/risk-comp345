#include "ObserverPlayerPhase.h"
#include <iostream>

//CONSTRUCTOR
/**Constructs ObserverPlayerPhase objects for a given game. Adds the game as an attribute and attaches itself to the game.*/
ObserverPlayerPhase::ObserverPlayerPhase(Game* game) { this->game = game; game->attach(this); }

//DESTRUCTOR
/**Constructs ObserverPlayerPhase objects for a given game*/
ObserverPlayerPhase::~ObserverPlayerPhase(){}

//UTILITY
/**Update observer with updates from subject (good for updating visuals).*/
void ObserverPlayerPhase::update(){
	system("CLS");
	diplayHeader();
}
/**Display header for current game state*/
void ObserverPlayerPhase::diplayHeader(){
	//Get name of current player
	std::string playerName = game->getCurrentPlayer()->getName();
	std::cout << "=========================================================\n";
	//Display current turn
	std::cout << "TURN " << game->getCurrentTurn() << "\n";
	//Diplay the appropriate header for the current state
	switch(game->getCurrentState()){
		case SETUP: 
			std::cout << "Player " + playerName + ": Setup Phase\nPlace a number of armies in your countries.\n"; break;
        case REINFORCE: 
			std::cout << "Player " + playerName + ": Reinforcement Phase\nPlace a number of armies in your countries.\n";break;
        case ATTACK: 
			std::cout << "Player " + playerName + ": Attack Phase\nDeclare a series of attacks to try to gain control of\nadditional countries.\n";break;
        case FORTIFY: 
			std::cout << "Player " + playerName + ": Fortification Phase\nMove a number of armies from one of your countries to one \nof its neighbor countries.\n";break;
		case END: 
			std::cout << "Game over\n" + playerName + " is the victor!\n"; break;
		default: 
			std::cout << "Error?";
    }
	std::cout << "=========================================================\n\n";
}