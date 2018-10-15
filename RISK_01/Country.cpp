#include "Country.h"

//Constructors
/**Parametrized constructor. Creates a country named name that belongs to continent pointed to by continent. Ensures that country is made a member of countryList for specified continent. This constructor is used in mapLoader. Neighbors to the country will be added once all countries have be created. Player occupying country will be determined at game start.**/
Country::Country(std::string name, Continent* continent) {
	continent->addCountry(this); //Add this country to the list of countries within its continent. This call must be made before the country attribute is changed from NULL or it will yield an exception.
	this->continent = continent;
	this->name = name;
}

/*Used for testing*/
Country::Country(std::string name)
{
	this->name = name;
}

//Accessors
/**Get name of country*/
std::string Country::getName() const {
	return name;
}
/**Get player occupying country*/
Player* Country::getOccupant() const {
	return occupant;
}
/**Get continent that country belongs to*/
Continent* Country::getContinent() const {
	return continent;
}
/**Get number of troops holding country*/
int Country::getTroops() const {
	return troopCount;
}

//Mutators
/**Add or remove (negative number) troopsToAdd troops to country. Return number of troops holding country.**/
int Country::addTroops(int troopsToAdd) {

	if (troopCount + troopsToAdd < 0)
		throw std::invalid_argument("Failed to remove troops, cannot have negative troops.");

	troopCount += troopsToAdd;
	return troopCount;
}

/**Changes the occupant**/
void Country::changeOccupant(Player * newOccupant)
{
	if (this->occupant != NULL) //If country had a previous occupant, remove this country from their posession
		this->occupant->removeCountry(this);
	this->occupant = newOccupant;
	newOccupant->addCountry(this); //Add country to player's posession
	this->continent->update(); //Update continent (check if posession has changed
}

/**Add a neighboring country to neighborList. Ensure that neighbor also has this country as its own neighbor (edges must all be bidirectional). If neighbor belongs to a different continent, link the continents by defining them as neighbors.**/
void Country::addNeighbor(Country* neighbor) {
	if (neighborList.insert(neighbor).second) { //Try adding neighbor to neighborList. If it is not already in the list, this country will not be in its list. Add this country to the neighboring country's list of neighbors.
		neighbor->addNeighbor(this);
		if (continent != neighbor->continent) //If the two countries belong to different continents, connect their continents.
			continent->addNeighbor(neighbor->continent);
	}
}

//Utility
/**Display details regarding country (occupant, neighbors, troops holding country, continent). Accepts a parameter for specifying left-space indentation (this is mainly used for displaying country within a list of countries).*/
void Country::display(std::string lspace) const {
	//Display country name and occupant
	std::cout << lspace + "  " + name + " (" << ((occupant == NULL) ? "NA" : occupant->getName()) + "): \n";

	//Display number of troops holding country and the continent where it is located
	std::cout << lspace + "    " + "Troops: " << troopCount << std::endl;
	std::cout << lspace + "    " + "Continent: " + continent->getName() << std::endl;

	//Display country's neighbors
	std::cout << lspace + "    " << "Neighbors: ";
	for (Country* neighbor : neighborList) std::cout << neighbor->getName() << ", ";
	std::cout << std::endl;
}

/**Get the countries reachable from this country. Does not check if neighboring countries are owned by the same player. Just checks for neighbors. Good for checking if maps are complete during validation.*/
std::unordered_set<Country*> Country::getReachable(std::unordered_set<Country*> reachableList) const{
	for (Country* neighbor : neighborList){ //Add the country's neighbors to the set of reachable countries
		if (reachableList.insert(neighbor).second){ //Check if the neighbor has already been added to the set of reachable countries (it might be the nieghbor of a previously added country too)
			reachableList = neighbor->getReachable(reachableList); //If country has not previously been added to list, add that country's neighbors to list using recursion. The base case is reached when all of a country's neighbors are already in the list.
		}
	}
	return reachableList;
}
/**Get the countries reachable from this country without crossing foreign borders. Checks if neighboring countries are occupied by the same player. Good for checking if occupant can fortify from this country to another and vice versa.**/
std::unordered_set<Country*> Country::getReachableForOccupant(std::unordered_set<Country*> reachableList) const {
	for (Country* neighbor : neighborList) //Add the country's neighbors to the set of reachable countries if they have the saem occupant.
		if (neighbor->getOccupant() == occupant && reachableList.insert(neighbor).second) //Check if the nieghboring country has the saem occupant. Check if the neighbor has already been added to the set of reachable countries (it might be the nieghbor of a previously added country too)
			reachableList = neighbor->getReachableForOccupant(reachableList); //If country has not previously been added to list, add that country's neighbors to list using recursion. The base case is reached when all of a country's neighbors are already in the list.
	return reachableList;
}
/**Check if country is neighbor of another country. Good for checking if attacks are valid.*/
bool Country::isNeighbor(Country * country) const {
	if (neighborList.count(country))
		return true;
	else
		return false;
}
/**Given a set of countries, get a country specified by name from the set (if it is a set member). Throw an exception otherwise.**/
Country* Country::getCountryFromSet(std::string countryName, std::unordered_set<Country*> countryList) {
	for (Country* country : countryList)
		if (countryName.compare(country->name) == 0)
			return country;
	throw std::invalid_argument(countryName + " is not a valid option.");
}
