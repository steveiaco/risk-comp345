#ifndef MAP
#define MAP

class Map;

#include "Country.h"
#include "Continent.h"
#include "Deck.h"
#include "Card.h"
#include <iostream>
#include <string>
#include <unordered_set>
#include <iterator>
#include <vector>

/**Defines a map. Maps will be stored as two undirected graphs. One graph will be made up of countries connected according to whether or not they are neighbors. The other graph will be comprised of continents. Continents will be connected if their countries are connected.**/
class Map {

private:
	/**Stores the list of continents in the continent graph. Connections between continents are stored within the continent class as a list of neighbors. Could be empty if map has no continents (despite being very boring).**/
	std::unordered_set<Continent*> continentList;
	/**Stores the list of countries in the country graph. Connections between countries are stored within the country class as a list of neighbors. Could be empty if map has no countries (despite being very boring).**/
	std::unordered_set<Country*> countryList;
	/**Name of the map. Map will usually share the name of the file from which it was loaded (if it is loaded from a file).**/
	std::string name;

public:
	//Constructors
	/**Constructs a map with the name name. Continent and Country graph start empty. We will fill them up later as the continents/countries are created and linked together. Good for loading a map from a file.*/
	Map(std::string name);
	/**Constructs a default diamond-shaped map. Good for testing purposes.**/
	Map();
	
	//Destructor
	/**Map destructor*/
	~Map();

	//Mutators
	/**Add a country to the map. Note that duplicate countries can not be added because list of countries is a set, however, countries of the same name can be added. To make the user interface easier on the user, we will throw an exception if a country being added has the same name as a country already in the map.*/
	void addCountry(Country* country);
	/**Add a continent to the map. Note that duplicate continents can not be added because list of continents is a set, however, continents of the same name can be added. To make the user interface easier on the user, we will throw an exception if a continent being added has the same name as a continent already in the map.*/
	void addContinent(Continent* continent);

	//Accessors
	/**Get a country from the list of countries in the map by name. Return an exception if the country does not exist within the map.**/
	Country* getCountry(std::string name) const;
	/**Get a continnt from the list of continents in the map by name. Return an exception if the continent does not exist within the map.**/
	Continent* getContinent(std::string name) const;
	/**Get number of countries in map.**/
	inline int getNumberOfCountries() const { return countryList.size(); }
	/**Get number of continents in map.**/
	inline int getNumberOfContinents() const { return continentList.size(); }
	/**Get name of map.**/
	inline std::string getName() const { return name; }

	//Utility
	/**Display the name of the map and a list of its continents (with their included countries) to the user.**/
	void display() const;
	/**Validate a map. This means checking if the map's countries are fully connected (ie checking if there is a path from each country to the rest of the countries). We do not need to check for things like whether or not each country belongs to one continent and whether or not country neighbors exist because this sort of thing is already checked elsewhere in the code.**/
	bool validate() const;
	/**Populate a deck of cards using countries from map.**/
	void populateDeck(Deck* deck) const;
	/**Assign equal number of countries to players randomly*/
	void assignCountries(std::vector<Player*>& players);
	/**Return winner if one person owns all countries. Return null otherwise.*/
	Player* getWinner() const;
	/**Resets map so that countries are troopless and unoccupied.*/
	void reset();
};

#endif