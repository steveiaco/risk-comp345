#ifndef MAP
#define MAP

class Map;

#include "Continent.h"
#include "Country.h"
#include <string>
#include <set>
using namespace std;

class Map {

private:
	set<Continent*> continentList;
	set<Country*> countryList;
	string name;

public:
	//Constructors
	Map(string name);
	Map();

	//Mutators
	void addCountry(Country* country);
	void addContinent(Continent* continent);

	//Accessors
	Country* getCountry(string name);
	Continent* getContinent(string name);

	//Utility
	void display() const;
	bool validate() const;
};

#endif