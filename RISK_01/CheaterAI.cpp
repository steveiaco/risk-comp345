#include "CheaterAI.h"

CheaterAI::CheaterAI() {}

CheaterAI::~CheaterAI() {}

//simply conquers all neighboring countries
bool CheaterAI::attack(Player* player) {

	//We will loop through all countries owned by the cheater player
	for (Country* attackingCountry : player->getCountriesOwned()) {
		//We will then loop through all neighbors of that country
		for (Country* defendingCountry : attackingCountry->getNeighbors()) {

			//check whether player owns the neighboring country
			if (player->ownsCountry(defendingCountry))
				continue;


			std::cout << player->getName() << ": Choose a country to attack from (cancel to cancel): " << attackingCountry->getName() << std::endl;
			std::cout << player->getName() << ": Choose a country to attack (cancel to cancel): " << defendingCountry->getName() << std::endl;

			//get a number of attacking die
			std::cout << player->getName() << ": Choose a number of dice to attack with [1," << ((attackingCountry->getTroops() > 3) ? 3 : attackingCountry->getTroops() - 1) << "] : ";
			int attackerRoll = chooseAttackerRoll(attackingCountry);

			//get a number of defending die
			std::cout << defendingCountry->getOccupant()->getName() << ": Choose a number of dice to defend with [1," << ((defendingCountry->getTroops() > 1) ? 2 : 1) << "] : ";
			int defenderRoll = defendingCountry->getOccupant()->getStrategy()->chooseDefenderRoll(defendingCountry);

			std::cout << "Attacker rolled: ";
			for (int i = 0; i < attackerRoll; i++)
				std::cout << "[7]";
			std::cout << std::endl;
			std::cout << "Defender rolled: ";
			for (int i = 0; i < attackerRoll; i++)
				std::cout << "[1]";
			std::cout << std::endl;

			std::cout << player->getName() << " has successfully invaded " << defendingCountry->getName() << " and managed to convince the invaded country's troops to pledge allegiance to " << player->getName() << "." << std::endl;
			defendingCountry->changeOccupant(player);


		}		
	}

	hasAttacked = true;
	return true;
}

//simply doubles all troops on each country
void CheaterAI::reinforce(Player * player)
{
	int troopsAvailable = 0;
	troopsAvailable += player->calculateTroopsAwarded();

	//Now we will check whether the player can exchange. If they can, we will ask if they want to exchange
	while (player->canExchange()) {
		std::cout << "You can exchange 3 of your cards. Would you like to do so? (y/n) ";
		if (askExchange())
			troopsAvailable += player->exchange();
	}

	for (Country* thisCountry : player->getCountriesOwned()) {
		std::cout << "You have " << troopsAvailable << " troops left to place, which country would you like to add troops to? " << thisCountry->getName() << std::endl;
		std::cout << "You have selected " << thisCountry->getName() << ". How many troops would you like to place on this country? (Max: " << troopsAvailable << ") : " << thisCountry->getTroops() << std::endl;
		thisCountry->addTroops(thisCountry->getTroops());
	}
}

//doubles number of troops of countries with neighboring enemy countries
void CheaterAI::fortify(Player* player) {

	std::unordered_set<Country*> countriesToFortify;

	//find all countries that are neighboring an enemy country
	for (Country* ownedCountry : player->getCountriesOwned())
		for (Country* neighCountry : ownedCountry->getNeighbors())
			if (!player->ownsCountry(neighCountry))
				countriesToFortify.insert(ownedCountry);

	//Ask if player would like to fortify
	std::cout << player->getName() << ": would you like to fortify? (y/n) y";

	for (Country* countryToFortify : countriesToFortify) {
		std::cout << player->getName() << ": successfully moved (spontaneously spawned) " << countryToFortify->getTroops() << " troop(s) from ThE mAgIcAl VoId to " << countryToFortify->getName() << ".\n";
		countryToFortify->addTroops(countryToFortify->getTroops());
	}

	return;

}

Country * CheaterAI::askSetup(Player * player)
{
	//get list of countries owned
	std::unordered_set<Country*> ownedCountries = player->getCountriesOwned();
	std::unordered_set<Country*>::iterator iter = ownedCountries.begin();

	//choose the index of the country to return
	srand(time(NULL));
	int randomIndex = std::rand() % player->getCountriesOwned().size();

	//get that index from the list by iterating
	advance(iter, randomIndex);
	//print what happened
	std::cout << (*iter)->getName() << std::endl;
	return *iter;
}



bool CheaterAI::askAttack(Player * player)
{
	if (!hasAttacked) {
		std::cout << "y" << std::endl;
		hasAttacked = true;
		return true;
	}
	else {
		std::cout << "n" << std::endl;
		return false;
	}
}



//always exchange
bool CheaterAI::askExchange()
{
	//Display a message indicating what happened
	std::cout << "yes\n";
	//Return answer
	return true;
}

int CheaterAI::chooseDefenderRoll(Country * defendingCountry)
{
	//AI will roll the maximum number of die possible
	int roll = 2;
	if (defendingCountry->getTroops() == 1)
		roll = 1;
	//Display a message indicating what happened
	std::cout << roll << "\n";
	//Return answer
	return roll;
}

int CheaterAI::chooseAttackerRoll(Country * attackingCountry)
{
	//AI will roll the maximum number of die possible
	int roll = 3;
	if (attackingCountry->getTroops() < 4)
		roll = attackingCountry->getTroops() - 1;
	//Display a message indicating what happened
	std::cout << roll << "\n";
	//Return answer
	return roll;
}

//unneeded for cheater, will remain unimplemented
Country * CheaterAI::chooseAttackFrom(Player * player)
{
	return nullptr;
}

//unneeded for cheater, will remain unimplemented
Country * CheaterAI::chooseAttackTo(Country * attackFrom)
{
	return nullptr;
}

//unneeded for cheater, will remain unimplemented
int CheaterAI::chooseMoveTroops(Country * attackingCountry, Country * defendingCountry)
{
	return 0;
}

//unneeded for cheater, will remain unimplemented

bool CheaterAI::askFortify(Player * player)
{
	return false;
}

//unneeded for cheater, will remain unimplemented
Country * CheaterAI::chooseOriginCountryFortify(Player * player)
{
	return nullptr;
}

//unneeded for cheater, will remain unimplemented
Country * CheaterAI::chooseReinforceCountry(Player * player)
{
	return nullptr;
}

//unneeded for cheater, will remain unimplemented
int CheaterAI::chooseNumberOfTroopsToReinforce(Country * reinforcedCountry, int troopsAvailable)
{
	return 0;
}

//unneeded for cheater, will remain unimplemented
Country * CheaterAI::chooseDestinationCountryFortify(Country * originCountry)
{
	return nullptr;
}
