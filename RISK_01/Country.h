#ifndef COUNTRY
#define COUNTRY

class Country;

#include "Continent.h"
#include "Player.h"
#include <string>
#include <set>
using namespace std;

class Country {

private:
	string name;
	Continent* continent;
	Player* occupant;
	int troopCount;
	set<Country*> neighborList;

public:
	//Constructors
	Country(string name, Continent* continent);

	//Mutators
	int addTroops(int troopsToAdd);
	void addNeighbor(Country* neighbor);
	string getName() const;

	//Accessors
	int getTroops() const;
	Player* getOccupant() const;
	Continent* getContinent() const;

	//Utility
	void display(string lspace) const;
	set<Country*> getReachable(set<Country*> reachableList) const;
};

#endif