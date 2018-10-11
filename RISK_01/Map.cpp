#include "Map.h"
#include "Country.h"
#include "Continent.h"
#include <iostream>
#include <string>
#include <set>
using namespace std;

Map::Map(string name) {
	this->name = name;
}

void Map::addCountry(Country* country) {
	countryList.insert(country);
}

void Map::addContinent(Continent* continent) {
	continentList.insert(continent);
}

Country* Map::getCountry(string name) {
	for (Country* country : countryList)
		if (country->getName().compare(name) == 0)
			return country;
	throw invalid_argument("Country " + name + " is undefined!");
}

Continent* Map::getContinent(string name) {
	for (Continent* continent : continentList)
		if (continent->getName().compare(name) == 0)
			return continent;
	throw invalid_argument("Continent " + name + " is undefined!");
}

void Map::display() const {
	//Display map's name
	cout << name + ": \n";
	//Display continents in country
	for (Continent* continent : continentList)
		continent->display("  ");
}

bool Map::validate() const{
	//Return true if map is empty
	if (countryList.empty() && continentList.empty())
		return true;

	//Check if all countries are reachable from one country. If so, all countries are connected. Do same for continents. Return false otherwise.
	Country* rootCountry = *countryList.begin();
	if (countryList != rootCountry->getReachable(*new set<Country*>))
		return false;
	Continent* rootContinent = *continentList.begin();
	if (continentList != rootContinent->getReachable(*new set<Continent*>))
		return false;

	//If you have not yet returned false, return true.
	return true;
}

Map::Map() : Map("Default Map"){
	Continent* contA = new Continent("Left", 1);
	Continent* contB = new Continent("Right", 4);

	Country* a = new Country("a", contA);
	Country* b = new Country("b", contB);
	Country* c = new Country("c", contB);
	Country* d = new Country("d", contB);
	Country* e = new Country("e", contB);

	a->addNeighbor(b);
	c->addNeighbor(b);
	d->addNeighbor(b);
	e->addNeighbor(b);

	addCountry(a);
	addCountry(b);
	addCountry(c);
	addCountry(d);
	addCountry(e);
	addContinent(contA);
	addContinent(contB);
}

Country* Map::contains(string countryName, set<Country*> countryList)
{
	for (Country* country : countryList) {
		if (country->getName() == countryName)
			return country;
	}
	throw std::invalid_argument("Name not found within country list.");
}