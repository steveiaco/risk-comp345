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
	thisMap->getCountry("d")->addTroops(2);

	//Display map
	thisMap->display();
	
	//Create deck
	Deck* deck = new Deck(thisMap);

	//main loop used for attack phase
	bool attacking = true;
	bool firstSuccess = true; //We want to give player a card for first victory
	while (attacking) {

		cout << thisPlayer->getName() << ", would you like to attack? (y/n) ";
		string input;
		std::getline(std::cin, input); std::cout << std::endl;
		//ask if player would like to continue attacking
		if (input == "N" || input == "n")
			break;

		//Show player their options. Break if no options exist.
		if (!thisPlayer->displayAttackable()) {
			std::cout << std::endl;
			break;
		}
		std::cout << std::endl;

		//get a valid attacking country and store it in attackingCountry
		Country* attackingCountry = NULL;
		while (attackingCountry == NULL) {
			string inp;
			cout << thisPlayer->getName() << ": please select a country to attack from (cancel to cancel): ";
			std::getline(std::cin, inp); std::cout << std::endl;
			if (inp == "cancel")
				break;
			//Make sure country is valid
			try {
				attackingCountry = thisMap->getCountry(inp);
				//check if player owns the attacking country
				if (!thisPlayer->ownsCountry(attackingCountry)) {
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
				cout << e.what() << std::endl;
			}
		}
		if (attackingCountry == NULL)
			continue;

		//get a valid attacking country and store it in defendingCountry
		Country* defendingCountry = NULL;
		while (defendingCountry == NULL) {
			string inp = string();
			cout << thisPlayer->getName() << ": please select a country to attack (cancel to cancel): ";
			std::getline(std::cin, inp); std::cout << std::endl;

			try {
				if (inp == "cancel")
					break;
				else {
					defendingCountry = thisMap->getCountry(inp);

					//if the attacking player owns the selected defending country, then it is an invalid selection
					if (thisPlayer->ownsCountry(defendingCountry)) {
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
				cout << e.what() << std::endl;
			}
		}
		if (defendingCountry == NULL)
			continue;

		//query attacker for number of dice
		string attackerRollString;
		int attackerRoll = NULL;
		while (attackerRoll == NULL) {
			cout << thisPlayer->getName() << ": how many dice would you like to use to attack? [1-" << ((attackingCountry->getTroops() - 1 > 3) ? 3 : (attackingCountry->getTroops() - 1)) << "] ";
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
		string defenderRollString;
		int defenderRoll = NULL;
		while (defenderRoll == NULL) {
			cout << defendingCountry->getOccupant()->getName() << ": how many dice would you like to use to defend? [1-" << ((defendingCountry->getTroops() > 2) ? 2 : (defendingCountry->getTroops())) << "] ";
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
			attackSuccessful = thisPlayer->attack(attackingCountry, defendingCountry, attackerRoll, defenderRoll);
		}
		catch (std::invalid_argument e) {
			std::cout << "FATAL ERROR\n";
			std::cout << e.what();
			exit(1);
		}

		if (attackSuccessful) {
			int numTroopsToMove = NULL;
			string numTroopsToMoveString;
			cout << thisPlayer->getName() << " has successfully invaded " << defendingCountry->getName() << std::endl;
			if (firstSuccess) {
				firstSuccess = false;
				thisPlayer->addCard(deck->draw());
				cout << thisPlayer->getName() << " has received a card for their first victory this round." << std::endl;
			}
			std::cout << std::endl;
			while (numTroopsToMove == NULL) {
				cout << thisPlayer->getName() << ": " << attackerRoll << " troop(s) automatically moved into " << defendingCountry->getName() << ", how many additional troops would you like to move into " << defendingCountry->getName() << "? [0-" << attackingCountry->getTroops() - 1 << "] ";
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

	//Display map
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