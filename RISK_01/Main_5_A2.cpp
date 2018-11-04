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
	thisMap->getValidMap();

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

	bool attacking = true;

	//main loop used for attack phase
	while (attacking) {

		cout << thisPlayer->getName() << ", would you like to attack? (y/n) ";
		string input;
		std::getline(std::cin, input); std::cout << std::endl;
		//ask if player would like to continue attacking
		if (input == "N" || input == "n")
			break;

		//if player is attacking, asks player for which country he would like to attack from
		cout << thisPlayer->getName() << " owns: \n";
		thisPlayer->printCountriesOwned();
		cout << std::endl;
		if (!thisPlayer->displayAttackable())
			break;

		//get a valid attacking country and store it in attackingCountry
		Country* attackingCountry = NULL;
		do {
			string inp;
			cout << "\nPlease select a country to attack from (cancel to cancel): ";
			std::getline(std::cin, inp); std::cout << std::endl;
			if (inp == "cancel")
				break;

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

				bool listValid = attackingCountry->canAttack();

				//if the country has no attackable neighbors, then continue and ask user to input another country to attack from
				if (!listValid) {
					attackingCountry = NULL;
					throw std::invalid_argument("This country has no attackable neighbors.");
				}
			}
			catch (std::invalid_argument e) {
				cout << e.what();
			}
		} while (attackingCountry == NULL);

		Country* defendingCountry = NULL;

		//get a valid attacking country and store it in defendingCountry
		do {
			string inp = string();
			cout << "\nPlease select a country to attack (cancel to cancel): ";
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
				cout << e.what();
			}
		} while (defendingCountry == NULL);


		//query attacker for number of dice
		string attackerRollString;
		int attackerRoll;
		do {
			cout << thisPlayer->getName() << ": how many dice would you like to use to attack? [1-" << ((attackingCountry->getTroops() - 1 > 3) ? 3 : (attackingCountry->getTroops() - 1)) << "] ";
			std::getline(std::cin, attackerRollString); std::cout << std::endl;
			attackerRoll = std::stoi(attackerRollString);
		} while (attackerRoll <= 0 || attackerRoll >= attackingCountry->getTroops() || attackerRoll > 3);

		//query defender for number of dice
		string defenderRollString;
		int defenderRoll;
		do {
			cout << defendingCountry->getOccupant()->getName() << ": how many dice would you like to use to defend? [1-" << ((defendingCountry->getTroops() > 2) ? 2 : (defendingCountry->getTroops())) << "] ";
			std::getline(std::cin, defenderRollString); std::cout << std::endl;
			defenderRoll = std::stoi(defenderRollString);
		} while (defenderRoll <= 0 || defenderRoll > defendingCountry->getTroops() || defenderRoll > 2);

		//if we get here, then we have successfully selected an attacker and attackee, move on to calling the attack function.
		bool attackSuccessful; //stores whether attacker has taken over defending country
		try {
			attackSuccessful = thisPlayer->attack(attackingCountry, defendingCountry, attackerRoll, defenderRoll);
		}
		catch (std::invalid_argument e) {
			cout << e.what();
		}

		if (attackSuccessful) {
			int numTroopsToMove;
			string numTroopsToMoveString;
			cout << thisPlayer->getName() << " has successfully invaded " << defendingCountry->getName() << std::endl;
			do {
				cout << thisPlayer->getName() << ": 1 troop automatically moved into " << defendingCountry->getName() << ", how many additional troops would you like to move into " << defendingCountry->getName() << "? [0-" << attackingCountry->getTroops() - 1 << "] ";
				std::getline(std::cin, numTroopsToMoveString); std::cout << std::endl;
				numTroopsToMove = std::stoi(numTroopsToMoveString);
			} while (numTroopsToMove >= attackingCountry->getTroops() || numTroopsToMove < 0);

			defendingCountry->addTroops(numTroopsToMove);
			attackingCountry->addTroops(-numTroopsToMove);
		}


	}

}