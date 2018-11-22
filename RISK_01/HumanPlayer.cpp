#include "HumanPlayer.h"

HumanPlayer::HumanPlayer() { }

/*Asks player whether they would like to attack*/
bool HumanPlayer::askAttack(Player* thisPlayer) {
	std::string input;
	std::getline(std::cin, input);
	//ask if player would like to continue attacking
	if (input == "N" || input == "n")
		return false;
	else
		return true;
}
/**Get number of dice player would like to defend with (given defending country)*/
int HumanPlayer::chooseDefenderRoll(Country * defendingCountry) {
	int defenderRoll = NULL;
	std::string defenderRollString;
	while (defenderRoll == NULL) {
		std::getline(std::cin, defenderRollString);
		try {
			defenderRoll = std::stoi(defenderRollString);
		}
		catch (std::invalid_argument& e) {
			std::cout << "Input must be a valid integer value, how many dice would you like to use to defend ? [1 - " << ((defendingCountry->getTroops() > 2) ? 2 : (defendingCountry->getTroops())) << "] ";
			defenderRoll = NULL;
			continue;
		}
		if (defenderRoll < 1 || defenderRoll > defendingCountry->getTroops() || defenderRoll > 2) {
			std::cout << "Input must be a valid integer value, how many dice would you like to use to defend ? [1 - " << ((defendingCountry->getTroops() > 2) ? 2 : (defendingCountry->getTroops())) << "] ";
			defenderRoll = NULL;
			continue;
		}
	}
	return defenderRoll;
}
/**Get number of dice player would like to attack with (given attacking country)*/
int HumanPlayer::chooseAttackerRoll(Country * attackingCountry)
{
	Player* thisPlayer = attackingCountry->getOccupant();
	int attackerRoll = NULL;
	std::string attackerRollString;

	while (attackerRoll == NULL) {
		std::getline(std::cin, attackerRollString);
		try {
			attackerRoll = std::stoi(attackerRollString);
		}
		catch (std::invalid_argument& e) {
			std::cout << "Invalid input! Input must be a valid integer value, [1 - " << ((attackingCountry->getTroops() - 1 > 3) ? 3 : (attackingCountry->getTroops() - 1)) << "]: ";
			attackerRoll = NULL;
			continue;
		}
		if (attackerRoll <= 0 || attackerRoll >= attackingCountry->getTroops() || attackerRoll > 3) {
			std::cout << "Invalid input! Input must be [1," << ((attackingCountry->getTroops() - 1 > 3) ? 3 : (attackingCountry->getTroops() - 1)) << "]: ";
			attackerRoll = NULL;
			continue;
		}
	}
	return attackerRoll;
}
/**Chose country to attack from*/
Country * HumanPlayer::chooseAttackFrom(Player* thisPlayer)
{
	Country* attackingCountry = NULL;
	while (attackingCountry == NULL) {
		std::string inp;
		std::getline(std::cin, inp);
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
			std::cout << thisPlayer->getName() << ": Choose a country to attack from (cancel to cancel): ";
		}
	}
	return attackingCountry;
}
/**Chose country to attack (given origin)*/
Country * HumanPlayer::chooseAttackTo(Country* attackingCountry) {
	Player* thisPlayer = attackingCountry->getOccupant();
	Country* defendingCountry = NULL;
	while (defendingCountry == NULL) {
		std::string inp = std::string();
		std::getline(std::cin, inp);
		try {
			if (inp == "cancel")
				return NULL;
			else {
				defendingCountry = Country::getCountryFromSet(inp,attackingCountry->getNeighbors());
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
			std::cout << thisPlayer->getName() << ": Choose a country to attack to (cancel to cancel): ";
		}
	}

	return defendingCountry;
}
/**Chose number of troops to move from one country to another after a victory*/
int HumanPlayer::chooseMoveTroops(Country* attackingCountry, Country* defendingCountry)
{
	std::string numTroopsToMoveString;
	int numTroopsToMove = NULL;
	while (numTroopsToMove == NULL) {
		std::getline(std::cin, numTroopsToMoveString);
		try {
			numTroopsToMove = std::stoi(numTroopsToMoveString);
			if (numTroopsToMove >= attackingCountry->getTroops() || numTroopsToMove < 0) {
				std::cout << "Invalid input! Input must be at least 0 and less than " << attackingCountry->getTroops() << ". Try again: ";
				numTroopsToMove = NULL;
				continue;
			}
			break;
		}
		catch (std::invalid_argument& e) {
			std::cout << "Invalid input! Input must be a valid integer value. Try again: ";
			numTroopsToMove = NULL;
		}
	}
	return numTroopsToMove;
}

/**Returns true if player wants to fortify, false otherwise*/
bool HumanPlayer::askFortify(Player * thisPlayer)
{
	//Ask if player would like to fortify
	std::string input;
	std::getline(std::cin, input);
	if (input == "N" || input == "n")
		return false;
	return true;
}
/**Chose country to fortify from*/
Country * HumanPlayer::chooseOriginCountryFortify(Player * thisPlayer)
{
	Country* moveFrom = NULL;
	while (moveFrom == NULL) {
		std::string inp;
		std::getline(std::cin, inp);
		if (inp == "cancel")
			break;
		try {
			moveFrom = Country::getCountryFromSet(inp, thisPlayer->getCountriesOwned());
			//check if player owns the country
			if (!thisPlayer->ownsCountry(moveFrom)) {
				moveFrom = NULL;
				throw std::invalid_argument("You do not own this country. Try again: ");
			}
			//moveFrom must have enough armies
			if (moveFrom->getTroops() < 2) {
				moveFrom = NULL;
				throw std::invalid_argument("Country must have more than one army on it. Try again: ");
			}
		}
		catch (std::invalid_argument e) {
			std::cout << e.what() << " Try again: ";
		}
	}
	return moveFrom;
}
/**Chose country to fortify to (guven origin)*/
Country * HumanPlayer::chooseDestinationCountryFortify(Country * originCountry)
{
	Player* thisPlayer = originCountry->getOccupant();
	Country* moveTo = NULL;
	/*GET VALID MOVE TO COUNTRY*/
	while (moveTo == NULL) {
		std::string inp = std::string();
		std::getline(std::cin, inp); std::cout << std::endl;
		try {
			if (inp == "cancel")
				break;
			moveTo = Country::getCountryFromSet(inp, thisPlayer->getCountriesOwned());
			//moveFrom must be a neighbor to moveTo
			if (!moveTo->isNeighbor(originCountry)) {
				moveTo = NULL;
				throw std::invalid_argument("Country must be a neighbor. Try again: ");
			}
			//Player must own destination
			if (!thisPlayer->ownsCountry(moveTo)) {
				moveTo = NULL;
				throw std::invalid_argument("You do not own this country. Try again: ");
			}
		}
		catch (std::invalid_argument e) {
			std::cout << e.what() << " Try again: ";
		}
	}
	return moveTo;
}

Country * HumanPlayer::chooseReinforceCountry(Player* thisPlayer)
{
	std::string countrySelectedString;
	Country* countrySelected = NULL;
	while (countrySelected == NULL) {
		std::getline(std::cin, countrySelectedString);
		if (countrySelectedString == "cancel")
			break;
		try {
			countrySelected = Country::getCountryFromSet(countrySelectedString, thisPlayer->getCountriesOwned());
		}
		catch (std::invalid_argument e) {
			std::cout << thisPlayer->getName() << ": you do not own this country or it does not exist, try again : ";
		}
	}
	return countrySelected;
}

int HumanPlayer::chooseNumberOfTroopsToReinforce(Country * reinforcedCountry, int troopsAvailable) {
	std::string in;
	int numTroopsToReinforce = NULL;
	while (numTroopsToReinforce == NULL) {
		std::getline(std::cin, in);
		try {
			numTroopsToReinforce = std::stoi(in);
			if (numTroopsToReinforce > troopsAvailable || numTroopsToReinforce < 0) {
				std::cout << "Invalid input! Input must be at least 0 and less than " << troopsAvailable << ". Try again: ";
				numTroopsToReinforce = NULL;
				continue;
			}
			break;
		}
		catch (std::invalid_argument& e) {
			std::cout << "Invalid input! Input must be a valid integer value. Try again: ";
			numTroopsToReinforce = NULL;
		}
	}
	return numTroopsToReinforce;
}

bool HumanPlayer::askExchange() {
	//Ask if player would like to exchange
	std::string input;
	std::getline(std::cin, input);
	if (input == "N" || input == "n")
		return false;
	return true;
}

Country * HumanPlayer::askSetup(Player* player) {
	std::string countrySelectedString;
	Country* countrySelected = NULL;

	while (countrySelected == NULL) {
		std::getline(std::cin, countrySelectedString);
		if (countrySelectedString == "skip")
			return NULL;
		try {
			countrySelected = Country::getCountryFromSet(countrySelectedString, player->getCountriesOwned());
		}
		catch (std::invalid_argument e) {
			std::cout << player->getName() << ": you do not own this country or it does not exist, try again : ";
		}
	}
	return countrySelected;
}