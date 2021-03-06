#ifndef COUNTRY
#define COUNTRY

class Country;

#include "Continent.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <unordered_set>

/**Defines a country as per the rules of risk. Countries are nodes on a map that players can take in their attempts to seize control of routes and continents. Moreover, every three countries owned yields 3 more troops per turn for the player.*/
class Country {

private:
	/**Name of country**/
	std::string name;
	/**Pointer to player occupying the country (defaults to NULL)**/
	Player* occupant = NULL;
	/**Pointer to continent to which the country belongs (country can only belong to one continent at a time). ANY FUNCTION THAT MODIFIES THIS VALUE SHOULD ALSO MAKE APPROPRIATE MODIFICATIONS TO THE INVOLVED CONTINENTS.**/
	Continent* continent = NULL;
	/**Number of troops holding country for occupant**/
	int troopCount = 0;
	/**Set of neighbors to country. We use set because we should not have duplicates and the order of the neighbors is of no significance.**/
	std::unordered_set<Country*> neighborList;

public:
	//Constructors
	/**Parametrized constructor. Creates a country named name that belongs to continent pointed to by continent. Ensures that country is made a member of countryList for specified continent. This constructor is used in mapLoader. Neighbors to the country will be added once all countries have be created. Player occupying country will be determined at game start.**/
	Country(std::string name, Continent* continent);

	//Destructor
	/**Country destructor*/
	~Country();
	
	//Mutators
	/**Add troopsToAdd troops to country**/
	int addTroops(int troopsToAdd);
	/**Add a neighboring country to neighborList. Ensure that neighbor also has this country as its own neighbor (edges must all be bidirectional). If neighbor belongs to a different continent, link the continents by defining them as neighbors.**/
	void addNeighbor(Country* neighbor);
	/**Changes the occupant**/
	void changeOccupant(Player* newOccupant);

	//Accessors
	/**Get name of country**/
	inline std::string getName() const { return name; }
	/**Get number of troops holding country**/
	inline int getTroops() const { return troopCount; }
	/**Get player occupying country**/
	inline Player* getOccupant() const { return occupant; }
	/**Get continent that country belongs to**/
	inline Continent* getContinent() const { return continent; }
	/**Get neighbors of country**/
	inline std::unordered_set<Country*> getNeighbors() const { return neighborList; }


	//Utility
	/**Display details regarding country (occupant, neighbors, troops holding country, continent). Accepts a parameter for specifying left-space indentation (this is mainly used for displaying country within a list of countries).**/
	void display(std::string lspace = "") const;
	/**Display neighbors of country.**/
	void displayNeighbors(std::string lspace = "") const;
	/**Returns true if country has attackable neighbors and more than one troop on it.**/
	bool canAttack() const;
	/**Display attackable neighbors.**/
	void displayAttackableNeighbors(std::string lspace = "") const;
	/**Get the countries reachable from this country. Does not check if neighboring countries are owned by the same player. Just checks for neighbors. Good for checking if maps are complete during validation.**/
	std::unordered_set<Country*> getReachable(std::unordered_set<Country*> reachableList) const;
	/**Get the countries reachable from this country without crossing foreign borders. Checks if neighboring countries are occupied by the same player. Good for checking if occupant can fortify from this country to another and vice versa.**/
	std::unordered_set<Country*> getReachableForOccupant(std::unordered_set<Country*> reachableList) const;
	/**Get the countries reachable from this country without crossing continent borders. Checks if neighboring countries belong to same continent. Good for checking if continents form connected subgraphs.**/
	std::unordered_set<Country*> getReachableWithinContinent(std::unordered_set<Country*> reachableList) const;
	/**Check if country is neighbor of another country. Good for checking if attacks are valid.**/
	bool isNeighbor(Country* country) const;
	/**Given a set of countries, get a country specified by name from the set (if it is a set member). Throw an exception otherwise.**/
	static Country* getCountryFromSet(std::string countryName, std::unordered_set<Country*> countryList);
	/**Resets country so that it is unnocupied and troopless*/
	void reset();
};

#endif