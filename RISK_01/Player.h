#ifndef PLAYER
#define PLAYER

class Player;

#include "Country.h"
#include "Continent.h"
#include "Player.h"
#include "Hand.h"
#include "Dice.h"
#include "Map.h"
#include "Card.h"
#include <string>
#include <vector>
#include <unordered_set>

class Player {

private:
	std::string name;
	std::unordered_set<Country*> countriesOwned;
	std::unordered_set<Continent*> continentsOwned;
	Hand* hand;
	Dice* dice;

public:

	//Constructors
	Player(std::string name);

	//Destructor
	~Player();

	//Accessors
	std::string getName() const;
	void displayHand();

	//Mutators
	void addCard(Card* card);
	void addCountry(Country* country);
	void addContinent(Continent* continent);
	bool removeCountry(Country* country);
	bool removeContinent(Continent* continent);

	//Utility
	void reinforce(Country* toReinforce, int numTroops); //count number of countries / 3, count how many continents owned
	bool attack(Country* attackFrom, Country* attackTo, int numAttackerDice, int numDefenderDice);
	void fortify(Country* moveFrom, Country* moveTo, int numberOfTroops);
	int	exchange();
	void printCountriesOwned();
	void printDiceStatistics();
	bool ownsCountry(Country* country);
	std::vector<int> getRoll(int NumRolls);

};

#endif
