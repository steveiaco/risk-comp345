#include "HumanPlayer.h"

HumanPlayer::HumanPlayer()
{

}

bool HumanPlayer::askAttack(Player* thisPlayer) {
	std::cout << thisPlayer->getName() << ", would you like to attack? (y/n) ";
	std::string input;
	std::getline(std::cin, input); std::cout << std::endl;
	//ask if player would like to continue attacking
	if (input == "N" || input == "n")
		return false;
	else
		return true;
}

int HumanPlayer::chooseDefenderRoll(Country * defendingCountry) {
	int defenderRoll = NULL;
	std::string defenderRollString;

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

	return defenderRoll;
}

int HumanPlayer::chooseAttackerRoll(Country * attackingCountry)
{
	Player* thisPlayer = attackingCountry->getOccupant();
	int attackerRoll = NULL;
	std::string attackerRollString;

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

	return attackerRoll;
}

Country * HumanPlayer::chooseAttackFrom(Player* thisPlayer)
{
	Country* attackingCountry = NULL;
	while (attackingCountry == NULL) {
		std::string inp;
		std::cout << thisPlayer->getName() << ": please select a country to attack from (cancel to cancel): ";
		std::getline(std::cin, inp); std::cout << std::endl;
		if (inp == "cancel")
			return NULL;
		//Make sure country is valid
		try {
			
			attackingCountry = Country::getCountryFromSet(inp, thisPlayer->getCountriesOwned());

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
}

Country * HumanPlayer::chooseAttackTo(Country* attackingCountry) {

	Player* thisPlayer = attackingCountry->getOccupant();

	Country* defendingCountry = NULL;
	while (defendingCountry == NULL) {
		std::string inp = std::string();
		std::cout << thisPlayer->getName() << ": please select a country to attack (cancel to cancel): ";
		std::getline(std::cin, inp); std::cout << std::endl;

		try {
			if (inp == "cancel")
				break;
			else {
				defendingCountry = Country::getCountryFromSet(inp,thisPlayer->getCountriesOwned);

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
}

int HumanPlayer::moveTroops(Country* attackingCountry, Country* defendingCountry)
{
	std::string numTroopsToMoveString;
	int numTroopsToMove = NULL;
	std::cout << std::endl;
	while (numTroopsToMove == NULL) {
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
}


bool HumanPlayer::askFortify(Player * thisPlayer)
{
	//Ask if player would like to fortify
	std::cout << thisPlayer->getName() << ": would you like to fortify? (y/n) ";
	std::string input;
	std::getline(std::cin, input); std::cout << std::endl;
	if (input == "N" || input == "n")
		return false;
	return true;
}

Country * HumanPlayer::chooseOriginCountryFortify(Player * thisPlayer)
{
	Country* moveFrom = NULL;
	while (moveFrom == NULL) {
		std::string inp;
		std::cout << std::endl << thisPlayer->getName() << ": please select a country to move players from (cancel to cancel): ";
		std::getline(std::cin, inp); std::cout << std::endl;
		if (inp == "cancel")
			break;
		try {
			moveFrom = Country::getCountryFromSet(inp, thisPlayer->getCountriesOwned());
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

	return moveFrom;
}

Country * HumanPlayer::chooseDestinationCountryFortify(Country * originCountry)
{

	Player* thisPlayer = originCountry->getOccupant();

	Country* moveTo = NULL;
	/*GET VALID MOVE TO COUNTRY*/
	while (moveTo == NULL) {
		std::string inp = std::string();
		std::cout << std::endl << thisPlayer->getName() << ": please select a country to move armies to (cancel to cancel): ";
		std::getline(std::cin, inp); std::cout << std::endl;
		try {
			if (inp == "cancel")
				break;
			moveTo = Country::getCountryFromSet(inp, thisPlayer->getCountriesOwned());
			//moveFrom must be a neighbor to moveTo
			if (!moveTo->isNeighbor(originCountry)) {
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
}

Country * HumanPlayer::chooseReinforceCountry(Player * thisPlayer)
{
	std::string countrySelectedString;
	std::getline(std::cin, countrySelectedString); std::cout << std::endl;

	Country* countrySelected = NULL;
	while (countrySelected == NULL) {
		try {
			countrySelected = Country::getCountryFromSet(countrySelectedString, thisPlayer->getCountriesOwned());
		}
		catch (std::invalid_argument e) {
			std::cout << thisPlayer->getName() << ": you do not own this country or it does not exist, try again.\n";
			return NULL;
		}
	}
}

