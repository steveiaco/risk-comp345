#ifndef PLAYER
#define PLAYER

class Player;

#include "Country.h"
#include "Continent.h"
#include "Hand.h"
#include "Dice.h"
#include "Map.h"
#include "Card.h"
#include <string>
#include <vector>
#include <unordered_set>

class Player {

private:
	/**Name of player*/
	std::string name;
	/**Countries owned by player*/
	std::unordered_set<Country*> countriesOwned;
	/**Continents owned by player*/
	std::unordered_set<Continent*> continentsOwned;
	/**Player hand*/
	Hand* hand;
	/**Player dice*/
	Dice* dice;

public:

	//CONSTRUCTORS
	/**Standard player constructor. Constructs a player with a given name and a new hand/set of dice.*/
	Player(std::string name);

	//DESTRUCTOR
	/**Player Destructor. Deletes players hand and dice.*/
	~Player();

	//ACCESSORS
	/**Get player's name*/
	inline std::string getName() const { return name; }
	/**Get number of cards in player's hand*/
	int getNumCards() const;

	//MUTATORS
	/**Add a given card to the player's hand*/
	inline void addCard(Card* card);
	/**Add a country to the list of countries owned by player*/
	inline bool addCountry(Country* country) { return countriesOwned.insert(country).second; }
	/**Add a continent to the list of continents owned by player*/
	inline bool addContinent(Continent* continent) { return continentsOwned.insert(continent).second; }
	/**Remove a country from the list of countries owned by player*/
	inline void removeCountry(Country* country) { countriesOwned.erase(country); }
	/**Remove a continent from the list of continents owned by player*/
	inline void removeContinent(Continent* continent) { continentsOwned.erase(continent); }

	//UTILITY
	/**Display player's hand*/
	void displayHand() const;
	/**Display player's dice and their statistsics*/
	void displayDice() const;

	/**Allows player to add troops to country if country is owned by player. Thorws an exception if country is not owned*/
	void reinforce(Country* toReinforce, int numTroops);
	/**Attack from a country owned by player to a neighboring country owned by another player (throws an exception otherwise). Attack with a certain number of attacker and defender dice (must be a valid number, otherwise, will throw excpetion). Removes the appropriate number of troops from both participating countries. If defending country runs out of troops, attacker wins. An change of posession takes place, attacking troops are moved to new country and true is returned (driver can then prompt user to select a number of troops to move). If attacker loses, returns false. Driver can then prompt attacker to chose what to do next.*/
	bool attack(Country* attackFrom, Country* attackTo, int numAttackerDice, int numDefenderDice);
	/**Fortify from one country to another (rules regarding how this should be done are contradictory, in this implementation, we allow player to move troops between neighboring countries)*/
	void fortify(Country* moveFrom, Country* moveTo, int numberOfTroops);

	/*Rolls the dice object, [1-3] dice*/
	inline std::vector<int> getRoll(int numRolls);
	/**Calculate troops awarded to player during reinforce phase*/
	int calculateTroopsAwarded() const;
	/**Display countries owned by player*/
	void printCountriesOwned() const;
	/**Check if player owns country*/
	bool ownsCountry(Country* country) const;
	/**Exchange cards in hand for troops (exchanges first set of three valid cards)*/
	int	exchange();
	/**Check if player can exchange their cards*/
	bool canExchange() const;
	/**Check if player must exchange thier cards (player must exchange cards if they have more than 5)*/
	bool mustExchange() const;

};

#endif
