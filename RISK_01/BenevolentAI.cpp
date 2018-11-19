#include "BenevolentAI.h"

//CONSTRUCTORS
/**AggrssiveAI constuctor*/
BenevolentAI::BenevolentAI() {}
//DESTRUCTOR
/**AggrssiveAI destructor*/
BenevolentAI::~BenevolentAI() {}

//UTILITY

//GENERAL
/**Get weakest country owned by player*/
Country* BenevolentAI::getWeakest(Player* player) {
	std::unordered_set<Country*> countriesOwned = player->getCountriesOwned();
	Country* weakest = NULL;
	for (Country* country : countriesOwned) {
		if (weakest == NULL)
			weakest = country;
		if (country->getTroops() < weakest->getTroops())
			weakest = country;
	}
	return weakest;
}
/**Prompt for where to place setup troop.*/
Country* BenevolentAI::askSetup(Player* player) {
	Country* toRet = getWeakest(player);
	//Display a message indicating what happened
	std::cout << toRet->getName() << "\n";
	//Return answer
	return toRet;
}

//REINFORCE
/**Choose a country to reinforce*/
Country* BenevolentAI::chooseReinforceCountry(Player* player) {
	//Chose strongest country
	Country* toRet = getWeakest(player);
	//Display a message indicating what happened
	std::cout << toRet->getName() << "\n";
	//Return answer
	return toRet;
}
/**Choose number of troops to reinforce with*/
int BenevolentAI::chooseNumberOfTroopsToReinforce(Country* reinforcedCountry, int troopsAvailable) {
	//Display a message indicating what happened
	std::cout << troopsAvailable << "\n";
	//Return answer
	return troopsAvailable;
}
/**Ask if player wants to exchange cards for troops*/
bool BenevolentAI::askExchange() {
	//Display a message indicating what happened
	std::cout << "yes\n";
	//Return answer
	return true;
}

//ATTACK
/**Returns true if player wants to attack, false otherwise*/
bool BenevolentAI::askAttack(Player* player) {
	//Player will never attack
	//Display a message indicating what happened
	std::cout << "no\n";
	//Return answer
	return false;
}
/**Get number of dice player would like to defend with (given defending country)*/
int BenevolentAI::chooseDefenderRoll(Country* defendingCountry) {
	//AI will roll the minimum number of die
	int roll = 1;
	//Display a message indicating what happened
	std::cout << roll << "\n";
	//Return answer
	return roll;
}
/**Get number of dice player would like to attack with (given attacking country)*/
int BenevolentAI::chooseAttackerRoll(Country* attackingCountry) {
	//AI will roll the maximum number of die possible
	int roll = 3;
	if (attackingCountry->getTroops() < 4)
		roll = attackingCountry->getTroops() - 1;
	//Display a message indicating what happened
	std::cout << roll << "\n";
	//Return answer
	return roll;
}
/**Chose country to attack from*/
Country* BenevolentAI::chooseAttackFrom(Player* player) {
	return NULL; //these methods will never be used as BenevolentAI never attacks
}
/**Chose country to attack (given origin)*/
Country* BenevolentAI::chooseAttackTo(Country* attackFrom) {
	return NULL; //these methods will never be used as BenevolentAI never attacks
}
/**Chose number of troops to move from one country, in this case, benevolent only uses this for fortify*/
int BenevolentAI::chooseMoveTroops(Country* attackingCountry, Country* defendingCountry) {
	
	int toRet = 0;

	if (attackingCountry->getTroops() < 5)
		toRet = (attackingCountry->getTroops() - 1);
	else
		toRet = (attackingCountry->getTroops() / 2);

	//Display a message indicating what happened
	std::cout << toRet << "\n";
	//Return answer
	return toRet;
}

//FORTIFY
/**Returns true if player wants to fortify, false otherwise*/

bool BenevolentAI::askFortify(Player* player) {
	bool fortify = false;
	//if the player owns a country that has a weaker owned neighboring country, then we can fortify
	for (Country* country : player->getCountriesOwned()) {
		for (Country* neighbor : country->getNeighbors())
			if ((country->getTroops() > neighbor->getTroops()) && player->ownsCountry(neighbor))
				fortify = true;
	}

		if (fortify) {
			//Display a message indicating what happened
			std::cout << "yes\n";
			//Return answer
			return true;
		}
		else {
			//Display a message indicating what happened
			std::cout << "no\n";
			//Return answer
			return false;
		}

}

	/**Chose country to fortify from*/
Country* BenevolentAI::chooseOriginCountryFortify(Player* player) {

	Country* toRet = NULL;

	for (Country* country : player->getCountriesOwned()) {
		for (Country* neighbor : country->getNeighbors())
			if ((country->getTroops() > neighbor->getTroops()) && player->ownsCountry(neighbor))
				toRet = country;
	}
	//Display a message indicating what happened
	std::cout << toRet->getName() << "\n";
	//Return answer
	return toRet;
}

/**Choose country to fortify to (guven origin)*/
Country* BenevolentAI::chooseDestinationCountryFortify(Country* originCountry) {
	//we will choose the weakest owned neighboring country
	Country* destination = NULL;
	for (Country* country : originCountry->getNeighbors()) {
		if (originCountry->getOccupant()->ownsCountry(country) && (country->getTroops() < originCountry->getTroops()))
			if (destination == NULL)
				destination = country;
			else if (destination->getTroops() > country->getTroops())
				destination = country;
	}
	return destination;
}