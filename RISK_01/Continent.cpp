#include "Continent.h"

//Constructors
/**Define a continent with name name and value value. This is for use when first loading map. Country and neighbor lists will be filled out as countries are loaded in. Occupant will be updated when/if a player takes control of all countries in continent.*/
Continent::Continent(std::string name, int value) {
	this->name = name;
	this->value = value;
	this->occupant = NULL;
}

//Destructor
/**Continent destructor*/
Continent::~Continent() {
	std::cout<<"Object continent has been deleted"<<std::endl;
}

//Mutators
/**Add a country to the continent. Checks that country being added is not already assigned to another continent.*/
void Continent::addCountry(Country* country) {
	if (country->getContinent() != NULL) //Check that country is not already assigned to a continent.
		throw std::invalid_argument(country->getName() + " is already a part of " + country->getContinent()->getName() + ".\n" + country->getName() + " can not be added to " + name + ".");
	else
		countryList.insert(country);
}
/**Add a neighbor to the continent. Makes sure that neighboring continent also has this continent added as neighbor (all edges should be bidirectional).*/
void Continent::addNeighbor(Continent* neighbor) {
	if (neighborList.insert(neighbor).second) {//Add neighbor only if neighbor is not already added.
		neighbor->addNeighbor(this); //Make sure that this country is a neighbor of the added neighbor (edges must be bidirectional)
	}
}

//Utility
/**Display details regarding continent (occupant, countries, neighbors, value). Accepts a parameter for specifying left-space indentation (this is mainly used for displaying continent within a list of continents).*/
void Continent::display(std::string lspace) const {
	//Display continent name and occupant
	std::cout << lspace + name + " (" + ((occupant == NULL) ? "NA" : occupant->getName()) + "): \n";

	//Display continent neighbors
	std::cout << lspace + "  " + "Neighbors: ";
	for (Continent* neighbor : neighborList) std::cout << neighbor->getName() << ", ";
	std::cout << std::endl;

	//Display continent countries
	std::cout << lspace + "  " + "Countries: \n";
	for (Country* country : countryList) country->display(lspace + "  ");
	std::cout << std::endl;
}
/**Most continent attributes will never change once map is loaded. However, player posessing the continent could change whenever posession of a country in the continent changes. This method is called when a country in the continent changes posession to calculate wheter or not the occupant has changed and make appropriate changes for the previous/new occupant and the continent itself.*/
void Continent::update() {
	//Keep track of previous occupant
	Player* prevOccupant = occupant;

	//If occupancy has changed, find new occupant
	std::unordered_set<Country*>::iterator i = countryList.begin();
	occupant = (*i)->getOccupant();
	//Iff an element in country list has an occupant different from the first element, continent is not occupied by any single player. Otherwise, continent is occupied by player who occupies first country (in addition to all others).
	for (; i != countryList.end(); i++)
		if ((*i)->getOccupant() != occupant) {
			occupant = NULL;
			break; //We have already proved that continent has no single occupant, we can stop checking occupant of other countries now.
		}

	//Remove/add continents from player posession
	if (prevOccupant != NULL)
		prevOccupant->removeContinent(this);
	if (occupant != NULL)
		occupant->addContinent(this);
}
/**Get continents reachable from a given continent. We will implement this method using recursion and a flood fill type of algorithm. Does not check that continents are occupied by th same player. Used for validating that continent maps are fully connected.*/
std::unordered_set<Continent*> Continent::getReachable(std::unordered_set<Continent*> reachableList) const {
	for (Continent* neighbor : neighborList) //Add the continent's neighbors to the set of reachable continent
		if (reachableList.insert(neighbor).second) //Check if the neighbor has already been added to the set of reachable continent (it might be the neighbor of a previously added continent too)
			reachableList = neighbor->getReachable(reachableList); //If continent has not previously been added to list, add that continent's neighbors to list using recursion. The base case is reached when all of a continent's neighbors are already in the list.
	return reachableList;
}
/**Make sure that continent forms a fully connected subgraph.*/
bool Continent::validate() const {
	//Return false if continent is empty (Empty continents are useless and unconnected)
	if (countryList.empty())
		return false;

	//Map graph is bidirectional. If all countries within continent can be reached from one country within continent (without leaving continent), then all countries can reach eachother (without leaving continent).
	Country* rootCountry = *countryList.begin();
	std::unordered_set<Country*> connectedCountries = std::unordered_set<Country*>();
	if (countryList != rootCountry->getReachable(connectedCountries))
		return false;

	//If have not yet returned false, return true.
	return true;
}

