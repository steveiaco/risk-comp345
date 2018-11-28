#include "RandomAI.h"

//CONSTRUCTOR
/*Constructor for RadnomAI*/
RandomAI::RandomAI() {
	//srand(time(NULL));
}

//DESTRUCTOR
/*Destructor for RadnomAI*/
RandomAI::~RandomAI() {}

//UTILITY
/*Chose a random country owned by passed player*/
Country * RandomAI::randomOwnedCountry(Player * player)
{
	//get list of countries owned
	std::unordered_set<Country*> ownedCountries = player->getCountriesOwned();
	std::unordered_set<Country*>::iterator iter = ownedCountries.begin();

	//choose the index of the country to return
	//srand(time(NULL));
	int randomIndex = std::rand() % player->getCountriesOwned().size();

	//get that index from the list by iterating
	advance(iter, randomIndex);

	return *iter;
}

//ATTACK
/*Get whether or not player would like to attack*/
bool RandomAI::askAttack(Player * player)
{
	//srand(time(NULL)); //initialize the random seed
	if (std::rand() % 2) {
		std::cout << "y" << std::endl;
		return true;
	}
	else {
		std::cout << "n" << std::endl;
		return false;
	}
}

/*Get country to place startup troop on*/
Country * RandomAI::askSetup(Player * player)
{
	Country* c = randomOwnedCountry(player);

	//display what happened
	std::cout << c->getName() << std::endl;
	return c;
}

/*Get country to reinforce*/
Country * RandomAI::chooseReinforceCountry(Player * player)
{
	Country* c = randomOwnedCountry(player);

	//display what happened
	std::cout << c->getName() << std::endl;
	return c;
}

/*Get number of troops to reinforce to country*/
int RandomAI::chooseNumberOfTroopsToReinforce(Country * reinforcedCountry, int troopsAvailable)
{
	//srand(time(NULL)); //initialize the random seed
	int num = ((std::rand() % troopsAvailable) + 1);

	//display what happened
	std::cout << num << std::endl;
	return num;
}

/*Get whether or not player would like to exchange cards*/
bool RandomAI::askExchange()
{
	//srand(time(NULL)); //initialize the random seed
	if (std::rand() % 2) {
		std::cout << "y" << std::endl;
		return true;
	}
	else {
		std::cout << "n" << std::endl;
		return false;
	}
}

/*Get number of dice to roll on defense*/
int RandomAI::chooseDefenderRoll(Country * defendingCountry)
{
	//srand(time(NULL)); //initialize the random seed

	if (defendingCountry->getTroops() == 1) {
		std::cout << "1" << std::endl;
		return 1;
	}
	else {
		int roll = (std::rand() % 2 + 1);
		std::cout << roll << std::endl;
		return roll;
	}
}

/*Get number of dice to roll on attack*/
int RandomAI::chooseAttackerRoll(Country * attackingCountry)
{
	int roll;

	//srand(time(NULL)); //initialize the random seed
	if (attackingCountry->getTroops() == 2)
		roll = 1;
	else if (attackingCountry->getTroops() == 3)
		roll = std::rand() % 2 + 1;
	else if (attackingCountry->getTroops() > 3)
		roll = std::rand() % 3 + 1;	

	//show what happened
	std::cout << roll << std::endl;

	return roll;
}

/*Get country to attack from*/
Country * RandomAI::chooseAttackFrom(Player * player)
{
	std::unordered_set<Country*> listAttack;
	for (Country* add : player->getCountriesOwned())
		if (add->canAttack())
			listAttack.insert(add);
	std::unordered_set<Country*>::iterator iter = listAttack.begin();

	//srand(time(NULL));
	int randIndex = std::rand() % listAttack.size();

	advance(iter, randIndex);
	//display what happened
	std::cout << (*iter)->getName() << std::endl;
	return *iter;

	Country* toReturn = randomOwnedCountry(player);
	while (!toReturn->canAttack())
		toReturn = randomOwnedCountry(player);
	//display what happened
	std::cout << toReturn->getName() << std::endl;
	return toReturn;
}

/*Get country to attack to*/
Country * RandomAI::chooseAttackTo(Country * attackFrom)
{
	std::unordered_set<Country*> listAttackable;
	for (Country* add : attackFrom->getNeighbors())
		if (!attackFrom->getOccupant()->ownsCountry(add))
			listAttackable.insert(add);
	std::unordered_set<Country*>::iterator iter = listAttackable.begin();

	//srand(time(NULL));
	int randIndex = std::rand() % listAttackable.size();

	advance(iter, randIndex);
	//display what happened
	std::cout << (*iter)->getName() << std::endl;
	return *iter;
}

/*Get number of troops to move between countries after successful attack*/
int RandomAI::chooseMoveTroops(Country * attackingCountry, Country * defendingCountry)
{
	int num;
	//srand(time(NULL));
	if (attackingCountry->getTroops() == 1)
		num = 0;
	else
	    num = std::rand() % (attackingCountry->getTroops() - 1) + 1;

	//display what happened
	std::cout << num << std::endl;

	return num;
}

/*Get whether or not player would like to fortify*/
bool RandomAI::askFortify(Player * player)
{
	//srand(time(NULL)); //initialize the random seed
	if (std::rand() % 2) {
		std::cout << "y" << std::endl;
		return true;
	}
	else {
		std::cout << "n" << std::endl;
		return false;
	}
}

/*Get country to fortify from*/
Country * RandomAI::chooseOriginCountryFortify(Player * player)
{
	std::unordered_set<Country*> listFortify;
	for (Country* add : player->getCountriesOwned())
		if (add->getTroops() > 1)
			listFortify.insert(add);
	std::unordered_set<Country*>::iterator iter = listFortify.begin();

	//srand(time(NULL));
	if (listFortify.size() == 0)
		return NULL;
	int randIndex = std::rand() % listFortify.size();

	advance(iter, randIndex);
	//display what happened
	std::cout << (*iter)->getName() << std::endl;
	return *iter;
}

/*Get country to fortify to*/
Country * RandomAI::chooseDestinationCountryFortify(Country * originCountry)
{
	std::unordered_set<Country*> listFortify;
	for (Country* add : originCountry->getNeighbors())
		if (originCountry->getOccupant()->ownsCountry(add))
			listFortify.insert(add);
	std::unordered_set<Country*>::iterator iter = listFortify.begin();

	//srand(time(NULL));
	if (listFortify.size() == 0)
		return NULL;
	int randIndex = std::rand() % listFortify.size();

	advance(iter, randIndex);
	//display what happened
	std::cout << (*iter)->getName() << std::endl;
	return *iter;
}
