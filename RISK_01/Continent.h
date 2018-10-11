#ifndef CONTINENT
#define CONTINENT

class Continent;

#include "Country.h"
#include "Player.h"
#include <string>
#include <set>

class Continent {

private:
	std::string name;
	Player* occupant;
	int value;
	std::set<Country*> countryList;
	std::set<Continent*> neighborList;

public:
	//Constructors
	Continent(std::string name, int value);

	//Mutators
	void addCountry(Country* country);
	void addNeighbor(Continent* neighbor);

	//Accssors
	std::string getName() const;
	int getValue() const;

	//Utility
	void display(std::string lspace) const;
	std::set<Continent*> getReachable(std::set<Continent*> reachableList) const;
	void update();
};

#endif