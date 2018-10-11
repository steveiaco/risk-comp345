#include "Continent.h"
#include "Country.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <set>
using namespace std;

Continent::Continent(string name, int value) {
	this->name = name;
	this->value = value;
	this->occupant = 0;
}

void Continent::addCountry(Country* country) {
	if (country->getContinent() != NULL)
		throw invalid_argument(country->getName() + " is already a part of " + country->getContinent()->getName() + "\n" + country->getName() + " can not be added to " + name + ".");
	else
		countryList.insert(country);
}

void Continent::addNeighbor(Continent* neighbor) {
	//Add neighbor only if neighbor is not already in set
	if (neighborList.find(neighbor) == neighborList.end()) {
		neighborList.insert(neighbor);
		neighbor->addNeighbor(this);
	}
}

void Continent::update() {
	//Keep track of previous occupant
	Player* prevOccupant = occupant;

	//If occupancy has changed, find new occupant
	set<Country*>::iterator i = countryList.begin();
	occupant = (*i)->getOccupant();
	//Iff an element in country list has an occupant different from the first element, continent is not occupied by any one player
	//Otherwise, continent is occupied by player who occupies first country
	for (; i != countryList.end(); i++)
		if ((*i)->getOccupant() != occupant)
			occupant = NULL;

	//Remove/add continents from player posession
	if (prevOccupant != NULL)
		prevOccupant->removeContinent(this);
	if (occupant != NULL)
		occupant->addContinent(this);
}

void Continent::display(string lspace) const {
	//Display continent name and occupant
	cout << lspace + name + " (" + ((occupant == NULL) ? "NA" : "oi"/*occupant->getName()*/) + "): \n";

	//Display continent neighbors
	cout << lspace + "  " + "Neighbors: ";
	for (Continent* neighbor : neighborList) {
		cout << neighbor->getName() << ", ";
	}
	cout << endl;

	//Display continent countries
	cout << lspace + "  " + "Countries: \n";
	for (Country* country : countryList) {
		country->display(lspace + "  ");
	}
	cout << endl;
}

string Continent::getName() const{
	return name;
}

int Continent::getValue() const
{
	return value;
}

set<Continent*> Continent::getReachable(set<Continent*> reachableList) const {
	for (Continent* neighbor : neighborList)
		if (reachableList.insert(neighbor).second)
			reachableList = neighbor->getReachable(reachableList);
	return reachableList;
}
