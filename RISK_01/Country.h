#ifndef COUNTRY
#define COUNTRY

class Country;

#include "Continent.h"
#include "Player.h"
#include <string>
#include <set>

class Country {

private:
	std::string name;
	Continent* continent;
	Player* occupant;
	int troopCount;
	std::set<Country*> neighborList;

public:
	//Constructors
	Country(std::string name, Continent* continent);

	//Mutators
	int addTroops(int troopsToAdd);
	void addNeighbor(Country* neighbor);
	std::string getName() const;

	//Accessors
	int getTroops() const;
	Player* getOccupant() const;
	Continent* getContinent() const;

	//Utility
	void display(std::string lspace) const;
	std::set<Country*> getReachable(std::set<Country*> reachableList) const;
	std::set<Country*> getReachableForPlayer(std::set<Country*> reachableList) const;
};

#endif