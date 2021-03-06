#include "Map.h"

//Constructors
/**Constructs a map with the name name. Continent and Country graph start empty. We will fill them up later as the continents/countries are created and linked together. Good for loading a map from a file.*/
Map::Map(std::string name) {
	this->name = name;
}

/**Default constructor. Creates an empty map with name "Default".*/
Map::Map() : Map("Default") { }

//Destructor
/**Map destructor (deletes all countries and continents)*/
Map::~Map() {
	//Delete all countries
	for (Country* country : countryList)
		delete country;
	//Delete all continents
	for (Continent* continent : continentList)
		delete continent;
}

//Mutators
/**Add a country to the map. Note that duplicate countries can not be added because list of countries is a set, however, countries of the same name can be added. To make the user interface easier on the user, we will throw an exception if a country being added has the same name as a country already in the map.*/
void Map::addCountry(Country* country) {
	for (Country* otherCountry : countryList) //Make sure that there are no other countries by the same name.
		if (otherCountry->getName().compare(country->getName()) == 0)
			throw std::invalid_argument("A country by the name of " + country->getName() + " already exists in " + name + ".\nDefining multiple countries of the same name within a single map is not allowed.");
	countryList.insert(country);
}
/**Add a continent to the map. Note that duplicate continents can not be added because list of continents is a set, however, continents of the same name can be added. To make the user interface easier on the user, we will throw an exception if a continent being added has the same name as a continent already in the map.*/
void Map::addContinent(Continent* continent) {
	for (Continent* otherContinent : continentList) //Make sure that there are no other continents by the same name.
		if (otherContinent->getName().compare(continent->getName()) == 0)
			throw std::invalid_argument("A continent by the name of " + continent->getName() + " already exists in " + name + ".\nDefining multiple continents of the same name within a single map is not allowed.");
	continentList.insert(continent);
}

//Accessors
/**Get a country from the list of countries in the map by name. Return an exception if the country does not exist within the map.**/
Country* Map::getCountry(std::string name) const {
	for (Country* country : countryList)
		if (country->getName().compare(name) == 0)
			return country;
	throw std::invalid_argument("Country " + name + " is undefined.");
}
/**Get a continnt from the list of continents in the map by name. Return an exception if the continent does not exist within the map.**/
Continent* Map::getContinent(std::string name) const {
	for (Continent* continent : continentList)
		if (continent->getName().compare(name) == 0)
			return continent;
	throw std::invalid_argument("Continent " + name + " is undefined.");
}

//Utility
/**Display the name of the map and a list of its continents (with their included countries) to the user.**/
void Map::display() const {
	//Display map's name
	std::cout << name + ": \n";
	//Display continents in country
	for (Continent* continent : continentList)
		continent->display("  ");
}
/**Validate a map. This means checking if the map's countries are fully connected (ie checking if there is a path from each country to the rest of the countries). We do not need to check for things like whether or not each country belongs to one continent and whether or not country neighbors exist because this sort of thing is already checked elsewhere in the code.**/
bool Map::validate() const{
	//Return true if map is empty
	if (countryList.empty() && continentList.empty())
		return true;
	//Return false if there are no countries, yet there are continents and vice-versa
	if (countryList.empty() || continentList.empty())
		return false;

	//Check if all countries are reachable from one country. If so, all countries are connected. Do same for continents. Return false otherwise.
	Country* rootCountry = *countryList.begin();
	std::unordered_set<Country*> connectedCountries = std::unordered_set<Country*> ();
	connectedCountries.insert(rootCountry);
	if (countryList != rootCountry->getReachable(connectedCountries))
		return false;
	Continent* rootContinent = *continentList.begin();
	std::unordered_set<Continent*> connectedContinents = std::unordered_set<Continent*>();
	connectedContinents.insert(rootContinent);
	if (continentList != rootContinent->getReachable(connectedContinents))
		return false;

	//Check if each continent forms a fully connected subgraph
	for (Continent* continent : continentList)
		if (!continent->validate())
			return false;

	//If you have not yet returned false, return true.
	return true;
}
/**Populate a deck of cards using countries from map.**/
void Map::populateDeck(Deck* deck) const {
	//We will keep count of every card added. For every card added, we will iterate between TroopTypes such that the three types are evenly distributed.
	int keepCount = 0;
	//Troop types must be evenly distributed abong cards
	for (Country* country : countryList)
		deck->addCard(new Card(country, static_cast<TroopType>(keepCount++%3), deck));
}
/**Assign equal number of countries to players randomly*/
void Map::assignCountries(std::vector<Player*>& players) {
	std::vector<Player*>::iterator crrtPlayer = players.begin();
	for (Country* country : countryList) {
		country->changeOccupant(*crrtPlayer++);
		country->addTroops(1);
		if (crrtPlayer == players.end())
			crrtPlayer = players.begin();
	}
}
/**Return winner if one person owns all countries. Return null otherwise.*/
Player* Map::getWinner() const {
	Player* potentialWinner = (*countryList.begin())->getOccupant();
	for (Country* country : countryList)
		//If a country in the list is not owned by the same player as another, there is no winner yet, return null
		if (country->getOccupant() != potentialWinner)
			return NULL;
	//If all countreis are owned by the same person, return the person who owns the first one
	return potentialWinner;
}
/**Resets map so that countries are unnocupied and troopless*/
void Map::reset() {
	for (Country* country : countryList)
		country->reset();
}