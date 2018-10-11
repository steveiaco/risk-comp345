#ifndef CONTINENT
#define CONTINENT

class Continent;

#include "Country.h"
#include "Player.h"
#include <string>
#include <set>
using namespace std;

class Continent {

private:
	string name;
	Player* occupant;
	int value;
	set<Country*> countryList;
	set<Continent*> neighborList;

public:
	//Constructors
	Continent(string name, int value);

	//Mutators
	void addCountry(Country* country);
	void addNeighbor(Continent* neighbor);

	//Accssors
	string getName() const;
	int getValue() const;

	//Utility
	void display(string lspace) const;
	set<Continent*> getReachable(set<Continent*> reachableList) const;
	void update();
	
};

#endif