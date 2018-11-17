#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(Game* passedGame, Player* passedPlayer)
{
	thisGame = passedGame;
	thisPlayer = passedPlayer;
}

bool HumanPlayer::attack()
{
	//main loop used for attack phase
	bool attacking = true;
	bool firstSuccess = true; //We want to give player a card for first victory
	while (attacking) {

		/**
		//if there is a winner, then we skip the attack phase completely
		if (map->getWinner())
			break;
		*/
		std::cout << thisPlayer->getName() << ", would you like to attack? (y/n) ";
		std::string input;
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
			std::string inp;
			std::cout << thisPlayer->getName() << ": please select a country to attack from (cancel to cancel): ";
			std::getline(std::cin, inp); std::cout << std::endl;
			if (inp == "cancel")
				break;
			//Make sure country is valid
			try {
				attackingCountry = thisGame->map->getCountry(inp);
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
				if (!attackingCountry->canAttack()) {
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

		//get a valid defending country and store it in defendingCountry
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

void HumanPlayer::reinforce()
{

	int troopsAvailable = 0;

	//get the number of troops available from the countries the player owns and the contienent values
	troopsAvailable += thisPlayer->calculateTroopsAwarded();

	//Show player their cards
	thisPlayer->displayHand();

	//check whether the player must exchange cards (has more than 6 cards)
	while (thisPlayer->mustExchange()) {
		std::cout << "You have " << thisPlayer->getNumCards() << ", cards. You can hold no more than 5 at a time. Here is an automatic exchange.\n";
		troopsAvailable += thisPlayer->exchange();
	}

	//now we will check whether the player can exchange, if they can then we will ask if they want to exchange
	while (thisPlayer->canExchange()) {
		std::string input;
		std::cout << "You currently have " << thisPlayer->getNumCards() << " cards and can exchange, would you like to do so? (Y/N) ";
		std::getline(std::cin, input); std::cout << std::endl;
		if (input == "Y" || input == "y")
			troopsAvailable += thisPlayer->exchange();
		else if (input == "N" || input == "n")
			break;
	}

	//now we can ask the player to start placing their troops
	std::cout << "You have a total of " << troopsAvailable << " troops available to place.\n";
	std::cout << "You can now start placing troops on the countries you own.\nHere is a list of countries in your possession:\n";
	thisPlayer->printCountriesOwned();

	while (troopsAvailable != 0) {
		std::string countrySelectedString;
		std::cout << "You have " << troopsAvailable << " troops lefts to place, which country would you like to add troops to? ";
		std::getline(std::cin, countrySelectedString); std::cout << std::endl;

		Country* countrySelected;
		try {
			countrySelected = thisGame->map->getCountry(countrySelectedString);
		}
		catch (std::invalid_argument e) {
			std::cout << "Country does not exist, try again.\n";
			continue;
		} if (!thisPlayer->ownsCountry(countrySelected)) {
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
		thisPlayer->reinforce(countrySelected, numTroopsToPlace);
		std::cout << "You have placed " << numTroopsToPlace << " troops on " << countrySelected->getName() << " giving it " << countrySelected->getTroops() << " total members.\n";
		troopsAvailable -= numTroopsToPlace;
	}
}

void HumanPlayer::fortify()
{

	while (true) {

		//Ask if player would like to fortify
		std::cout << thisPlayer->getName() << ": would you like to fortify? (y/n) ";
		std::string input;
		std::getline(std::cin, input); std::cout << std::endl;
		if (input == "N" || input == "n")
			break;

		//Display owned countries
		std::cout << thisPlayer->getName() << ": you may fortify from/to the following countries.\n";
		thisPlayer->printCountriesOwned();

		/*GET VALID MOVE FROM COUNTRY*/
		Country* moveFrom = NULL;
		while (moveFrom == NULL) {
			std::string inp;
			std::cout << std::endl << thisPlayer->getName() << ": please select a country to move players from (cancel to cancel): ";
			std::getline(std::cin, inp); std::cout << std::endl;
			if (inp == "cancel")
				break;
			try {
				moveFrom = thisGame->map->getCountry(inp);
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
			std::cout << std::endl << thisPlayer->getName() << ": please select a country to move armies to (cancel to cancel): ";
			std::getline(std::cin, inp); std::cout << std::endl;
			try {
				if (inp == "cancel")
					break;
				moveTo = thisGame->map->getCountry(inp);
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
				std::cout << e.what();
			}
		}
		if (moveTo == NULL)
			continue;

		/*QUERY FOR NUMBER OF TROOPS TO MOVE*/
		std::string moveNumTroopsString;
		int moveNumTroops = NULL;
		while (moveNumTroops == NULL) {
			std::cout << thisPlayer->getName() << ": how many troops would you like to move from " << moveFrom->getName() << " to " << moveTo->getName() << " ? [1 - " << (moveFrom->getTroops() - 1) << "] (cancel to cancel): ";
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
		std::cout << thisPlayer->getName() << ": successfully moved " << moveNumTroops << " troop(s) from " << moveFrom->getName() << " to " << moveTo->getName() << ".\n";
		break;
	}
}
