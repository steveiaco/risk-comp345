#ifndef PLAYER
#define PLAYER

class Player;

#include "Country.h"
#include "Continent.h"
#include <string>
#include <set>
using namespace std;

class Player {

private:
	string name;
	set<Country*> countriesOwned;
	set<Continent*> continentsOwned;

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
};

#endif