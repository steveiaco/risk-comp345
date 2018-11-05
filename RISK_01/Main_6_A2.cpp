#include "Player.h"
#include "Map.h"
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::cin;

int main() {

	Player* thisPlayer = new Player("datguy"); //it is this player's turn
	Player* defenderPlayer = new Player("disguy");

	//map setup
	Map* thisMap = new Map();

	//give countries to attacker
	thisMap->getCountry("a")->changeOccupant(thisPlayer);
	thisMap->getCountry("c")->changeOccupant(thisPlayer);

	//give countries to defender
	thisMap->getCountry("b")->changeOccupant(defenderPlayer);
	thisMap->getCountry("d")->changeOccupant(defenderPlayer);
	thisMap->getCountry("e")->changeOccupant(defenderPlayer);
	thisMap->getCountry("f")->changeOccupant(defenderPlayer);

	thisMap->getCountry("a")->addTroops(10);
	thisMap->getCountry("b")->addTroops(2);
	thisMap->getCountry("c")->addTroops(1);
	thisMap->getCountry("e")->addTroops(1);
	thisMap->getCountry("f")->addTroops(6);

	//Display map
	thisMap->display();

	//Create deck
	Deck* deck = new Deck(thisMap);

	while (true) {

		//Ask if player would like to fortify
		cout << thisPlayer->getName() << ": would you like to fortify? (y/n) ";
		string input;
		std::getline(std::cin, input); std::cout << std::endl;
		if (input == "N" || input == "n")
			break;

		//Display owned countries
		cout << thisPlayer->getName() << ": you may fortify from/to the following countries.\n";
		thisPlayer->printCountriesOwned();

		/*GET VALID MOVE FROM COUNTRY*/
		Country* moveFrom = NULL;
		while (moveFrom == NULL) {
			string inp;
			cout << std::endl << thisPlayer->getName() << ": please select a country to move players from (cancel to cancel): ";
			std::getline(std::cin, inp); std::cout << std::endl;
			if (inp == "cancel")
				break;
			try {
				moveFrom = thisMap->getCountry(inp);
				//check if player owns the country
				if (!thisPlayer->ownsCountry(moveFrom)) {
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
				cout << e.what();
			}
		}
		//If player canceled before moveFrom could be set, restart
		if (moveFrom == NULL)
			continue;

		cout << "You may fortify " << moveFrom->getName() << "'s neighboring countries.\n";
		moveFrom->display();
		Country* moveTo = NULL;
		/*GET VALID MOVE TO COUNTRY*/
		while (moveTo == NULL) {
			string inp = string();
			cout << std::endl << thisPlayer->getName() << ": please select a country to move armies to (cancel to cancel): ";
			std::getline(std::cin, inp); std::cout << std::endl;
			try {
				if (inp == "cancel")
					break;
				moveTo = thisMap->getCountry(inp);
				//moveFrom must be a neighbor to moveTo
				if (!moveTo->isNeighbor(moveFrom)) {
					moveTo = NULL;
					throw std::invalid_argument("Country must be a neighbor.");
				}
				//Player must own destination
				if (!thisPlayer->ownsCountry(moveTo)) {
					moveTo = NULL;
					throw std::invalid_argument("You do not own this country.");
				}
			}
			catch (std::invalid_argument e) {
				cout << e.what();
			}
		}
		if (moveTo == NULL)
			continue;

		/*QUERY FOR NUMBER OF TROOPS TO MOVE*/
		string moveNumTroopsString;
		int moveNumTroops = NULL;
		while (moveNumTroops == NULL) {
			cout << thisPlayer->getName() << ": how many troops would you like to move from " << moveFrom->getName() << " to " << moveTo->getName() << " ? [1 - " << (moveFrom->getTroops() - 1) << "] (cancel to cancel): ";
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
		thisPlayer->fortify(moveFrom, moveTo, moveNumTroops);
		cout << thisPlayer->getName() << ": successfully moved " << moveNumTroops << " troop(s) from " << moveFrom->getName() << " to " << moveTo->getName() << ".\n";
		break;
	}

	//Display map
	std::cout << std::endl;
	thisMap->display();

	delete thisMap;
	delete thisPlayer;
	delete defenderPlayer;
	delete deck;

	thisMap = NULL;
	thisPlayer = NULL;
	defenderPlayer = NULL;
	deck = NULL;
}