#include "ArtificialPlayer.h"

bool AgressiveAI::promptAttack() {

	//main loop used for attack phase
	bool attacking = true;
	bool firstSuccess = true; //We want to give player a card for first victory

	//find the most powerful country in this player's possession
	Country* attackingCountry = *thisPlayer->getCountriesOwned.begin();

	for (std::unordered_set<Country*>::iterator it = thisPlayer->getCountriesOwned.begin(); it != thisPlayer->getCountriesOwned.end(); it++) {
		if (attackingCountry->getTroops() < (*it)->getTroops())
			attackingCountry = *it;
	}

	while (attacking) {

		//MUST MOVE THIS CODE INTO IT'S OWN METHOD selectDefending, SO AN AI MAY ALSO AUTOMATICALLY SELECT A DEFENDING 
		//prompt and get a valid country from the defending user
		Country* defendingCountry = NULL;
		while (defendingCountry == NULL) {
			std::string inp = std::string();
			std::cout << thisPlayer->getName() << ": please select a country to attack (cancel to cancel): ";
			std::getline(std::cin, inp); std::cout << std::endl;

			try {
				if (inp == "cancel")
					break;
				else {
					defendingCountry = thisGame->map->getCountry(inp);

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
				std::cout << e.what() << std::endl;
			}
		}
		if (defendingCountry == NULL)
			continue;

		//query attacker for number of dice
		std::string attackerRollString;
		int attackerRoll = NULL;
		while (attackerRoll == NULL) {
			std::cout << thisPlayer->getName() << ": how many dice would you like to use to attack? [1-" << ((attackingCountry->getTroops() - 1 > 3) ? 3 : (attackingCountry->getTroops() - 1)) << "] ";
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
			attackSuccessful = thisPlayer->attack(attackingCountry, defendingCountry, attackerRoll, defenderRoll);
		}
		catch (std::invalid_argument e) {
			std::cout << e.what();
			exit(1);
		}

		if (attackSuccessful) {
			int numTroopsToMove = NULL;
			std::string numTroopsToMoveString;
			std::cout << thisPlayer->getName() << " has successfully invaded " << defendingCountry->getName() << std::endl;
			if (firstSuccess) {
				firstSuccess = false;
				thisPlayer->addCard(thisGame->deck->draw());
				std::cout << thisPlayer->getName() << " has received a card for their first victory this round." << std::endl;
			}
			std::cout << std::endl;
			while (numTroopsToMove == NULL) {
				std::cout << thisPlayer->getName() << ": " << attackerRoll << " troop(s) automatically moved into " << defendingCountry->getName() << ", how many additional troops would you like to move into " << defendingCountry->getName() << "? [0-" << attackingCountry->getTroops() - 1 << "] ";
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
			return true;//return true if attack is successful
		}

		return false;//return false if attack is not successful
	}
}