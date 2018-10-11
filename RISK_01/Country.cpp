#include "Country.h"
#include "Continent.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <set>
using namespace std;

Country::Country(string name, Continent* continent) {
	continent->addCountry(this);
	this->continent = continent;
	this->occupant = NULL;
	this->troopCount = 0;
	this->name = name;
}

void Country::display(string lspace) const {
	//Display country name and occupant
	cout << lspace + "  " + name + " (" << ((occupant == NULL) ? "NA" : occupant->getName()) + "): \n";

	//Display number of troops holding country and the continent where it is located
	cout << lspace + "    " + "Troops: " << troopCount << endl;
	cout << lspace + "    " + "Continent: " + continent->getName() << endl;

	//Display country's neighbors
	cout << lspace + "    " << "Neighbors: ";
	for (Country* neighbor : neighborList) {
		cout << neighbor->getName() << ", ";
	}
	cout << endl;
}

string Country::getName() const {
	return name;
}

Player* Country::getOccupant() const {
	return occupant;
}

Continent* Country::getContinent() const {
	return continent;
}

int Country::getTroops() const {
	return troopCount;
}

int Country::addTroops(int troopsToAdd) {
	troopCount += troopsToAdd;
	return troopCount;
}

void Country::addNeighbor(Country* neighbor) {
	//Add neighbor only if neighbor is not already in set
	if (neighborList.find(neighbor) == neighborList.end()) {
		neighborList.insert(neighbor);
		neighbor->addNeighbor(this);
		if (continent != neighbor->continent)
			continent->addNeighbor(neighbor->continent);
	}
}

set<Country*> Country::getReachable(set<Country*> reachableList) const{
	for (Country* neighbor : neighborList)
		if(reachableList.insert(neighbor).second)
			reachableList = neighbor->getReachable(reachableList);
	return reachableList;
}

set<Country*> Country::getReachableForPlayer(set<Country*> reachableList) const {
	for (Country* neighbor : neighborList)
		if (neighbor->getOccupant() == occupant && reachableList.insert(neighbor).second)
			reachableList = neighbor->getReachableForPlayer(reachableList);
	return reachableList;
}