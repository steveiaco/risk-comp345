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
#include <set>
using namespace std;

class Player {

private:
	string name;
	set<Country*> countriesOwned;
	set<Continent*> continentsOwned;
	Hand playerHand;

public:
	//Constructors
	Player(string name);

	//Accessors
	string getName() const;

	//Mutators
	void addCountry(Country* country);
	void addContinent(Continent* continent);
	bool removeCountry(Country* country);
	bool removeContinent(Continent* continent);

	//Utility
	void reinforce(); //count number of countries / 3, count how many continents owned
	void attack();
	void fortify();
	Country* countryExists(string input); //checks a string against a list of countries, attempts to find the country who's name is equal to that string and returns it
	int exchange();
};

#endif
