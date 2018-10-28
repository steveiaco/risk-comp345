#ifndef CONTINENT
#define CONTINENT

class Continent;

#include "Player.h"
#include "Country.h"
#include <iostream>
#include <string>
#include <unordered_set>

/**Defines a continent as per the rules of risk. Continents are collections of countries that players can hold for additional troops per turn.*/
class Continent {

private:
	/**Name of continent**/
	std::string name;
	/**Pointer to player occupying the continent (defaults to NULL)**/
	Player* occupant = NULL;
	/**Value of continent (number of troops player will receive per turn for holding continent)**/
	int value = 0;
	/**Set of countries in continent. We use sets because we should not have duplicates and order is not important (we simply want to know the set of countries that belong to continent).**/
	std::unordered_set<Country*> countryList;
	/**Set (justification for using set is the same as that for countryList) of neighbors to continent (continents are neighbors if they have countries that are neighbors between them)**/
	std::unordered_set<Continent*> neighborList;

public:
	//Constructors
	/**Define a continent with name name and value value. This is for use when first loading map. Country and neighbor lists will be filled out as countries are loaded in. Occupant will be updated when/if a player takes control of all countries in continent.*/
	Continent(std::string name, int value);
	~Continent();

	//Mutators
	/**Add a country to the continent. Checks that country being added is not already assigned to another continent.*/
	void addCountry(Country* country);
	/**Add a neighbor to the continent. Makes sure that neighboring continent also has this continent added as neighbor (all edges should be bidirectional).*/
	void addNeighbor(Continent* neighbor);

	//Accessors
	/**Get name of continent*/
	std::string getName() const;
	/**Get value of continent*/
	int getValue() const;

	std::unordered_set<Continent*> getNeighborList();
	std::unordered_set<Country*> getCountriesFromContinent();

	//Utility
	/**Display details regarding continent (occupant, countries, neighbors, value). Accepts a parameter for specifying left-space indentation (this is mainly used for displaying continent within a list of continents).*/
	void display(std::string lspace = "") const;
	/**Get continents reachable from a given continent. Used for validating that continent maps are fully connected.*/
	std::unordered_set<Continent*> getReachable(std::unordered_set<Continent*> reachableList) const;
	/**Most continent attributes will never change once map is loaded. However, player posessing the continent could change whenever posession of a country in the continent changes. This method is called when a country in the continent changes posession to calculate wheter or not the occupant has changed and make appropriate changes for the previous/new occupant and the continent itself.*/
	void update();
};

#endif