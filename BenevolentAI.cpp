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
	Country* weakest = *countriesOwned.begin();
	for (Country* country : countriesOwned)
		if (country->getTroops() < weakest->getTroops())
			weakest = country;
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
	//Player will attack if strongest country is capable of attacking
	if (getStrongest(player)->canAttack()) {
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
/**Get number of dice player would like to defend with (given defending country)*/
int BenevolentAI::chooseDefenderRoll(Country* defendingCountry) {
	//AI will roll the maximum number of die possible
	int roll = 2;
	if (defendingCountry->getTroops() == 1)
		roll = 1;
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
	//Chose strongest country (we already know that it is capable of attacking if we got here because player's troops will only be concentrated on strongest country)
	Country* toRet = getStrongest(player);
	//Display a message indicating what happened
	std::cout << toRet->getName() << "\n";
	//Return answer
	return toRet;
}
/**Chose country to attack (given origin)*/
Country* BenevolentAI::chooseAttackTo(Country* attackFrom) {
	//Find the weakest attackable neighbor
	std::unordered_set<Country*> neighbors = attackFrom->getNeighbors();
	Country* weakest = NULL;
	//Begin by setting weakest to some country that is not owned
	for (Country* country : neighbors)
		if (country->getOccupant() != attackFrom->getOccupant())
			weakest = country;
	//Now change weakest country to weakest country
	for (Country* country : neighbors)
		if ((country->getOccupant() != attackFrom->getOccupant()) && (country->getTroops() < weakest->getTroops()))
			weakest = country;
	//Display a message indicating what happened
	std::cout << weakest->getName() << "\n";
	//Return answer
	return weakest;
}
/**Chose number of troops to move from one country to another after a victory*/
int BenevolentAI::chooseMoveTroops(Country* attackingCountry, Country* defendingCountry) {
	//Move the maximum number of troops
	int toRet = attackingCountry->getTroops() - 1;
	//Display a message indicating what happened
	std::cout << toRet << "\n";
	//Return answer
	return toRet;
}

//FORTIFY
/**Returns true if player wants to fortify, false otherwise*/
bool BenevolentAI::askFortify(Player* player) {
	//Players troops should always be concentrated in one country, player should only fortify if they can not attack
	if (getStrongest(player)->canAttack()) {
		//Display a message indicating what happened
		std::cout << "no\n";
		//Return answer
		return false;
	}
	else {
		//Display a message indicating what happened
		std::cout << "yes\n";
		//Return answer
		return true;
	}
}
/**Chose country to fortify from*/
Country* BenevolentAI::chooseOriginCountryFortify(Player* player) {
	//Player can only fortify from strongest country
	Country* toRet = getStrongest(player);
	//Display a message indicating what happened
	std::cout << toRet->getName() << "\n";
	//Return answer
	return toRet;
}
/**Chose country to fortify to (guven origin)*/
Country* BenevolentAI::chooseDestinationCountryFortify(Country* originCountry) {
	//Though we could move the troops to a country from which the player can attack more efficiently via pathfinding, we will opt for instructing the player to make random moves instead (over time, this will put the player into an attackable position)
	std::unordered_set<Country*> neighbors = originCountry->getNeighbors();
	srand(time(NULL)); //initialize the random seed
	int randIndex = std::rand() % neighbors.size(); //Country will always have at least one neighbor (graph is fully connected)
	std::unordered_set<Country*>::const_iterator it(neighbors.begin());
	advance(it, randIndex);
	Country* destination = *it;
	//Display a message indicating what happened
	std::cout << destination->getName() << "\n";
	//Return answer
	return destination;
}