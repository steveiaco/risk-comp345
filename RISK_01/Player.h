#ifndef PLAYER
#define PLAYER

class Player;

#include "Country.h"
#include "Continent.h"
#include "Player.h"
#include "Hand.h"
#include "Dice.h"
#include "Map.h"
#include <string>
#include <vector>
#include <set>

class Player {

private:
	std::string name;
	std::set<Country*> countriesOwned;
	std::set<Continent*> continentsOwned;
	Hand* playerHand;
	Dice* dice;

	
	//Country* queryOwnedCountry(); //queries the user for a name, attempts to find the country who's name is equal to that string and returns it

public:

	//Attributes

	//Constructors
	Player(std::string name);

	//Accessors
	std::string getName() const;

	//Mutators
	void addCountry(Country* country);
	void addContinent(Continent* continent);
	bool removeCountry(Country* country);
	bool removeContinent(Continent* continent);

	//Utility
	void reinforce(Country* toReinforce, int numTroops); //count number of countries / 3, count how many continents owned
	bool attack(Country* attackFrom, Country* attackTo, int numAttackerDice, int numDefenderDice);
	void fortify(Country* moveFrom, Country* moveTo, int numberOfTroops);
	int	exchange();
	void printCountriesOwned();
	void printDiceStatistics();
	bool ownsCountry(Country* country);
	std::vector<int> getRoll(int NumRolls);

};

#endif
