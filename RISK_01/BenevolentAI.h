#ifndef BENEVOLENT_AI_H
#define BENEVOLENT_AI_H

class BenevolentAI;

#include "PlayerStrategy.h"

class BenevolentAI : public PlayerStrategy {
public:
	//CONSTRUCTORS
	/**BenevolentAI constuctor*/
	BenevolentAI();

	//DESTRUCTORS
	/**BenevolentAI destructor*/
	~BenevolentAI();

	//UTILITY
	/**Returns true if player wants to attack, false otherwise*/
	bool askAttack(Player* player);
	/**Prompt for where to place setup troop.*/
	Country* askSetup(Player* player);

private:
	//GENERAL
	/**Get weakest country owned by player*/
	Country* getWeakest(Player* player);

	//REINFORCE
	/**Choose a country to reinforce*/
	Country* chooseReinforceCountry(Player* player);
	/**Choose number of troops to reinforce with*/
	int chooseNumberOfTroopsToReinforce(Country* reinforcedCountry, int troopsAvailable);
	/**Ask if player wants to exchange cards for troops*/
	bool askExchange();

	//ATTACK
	/**Get number of dice player would like to defend with (given defending country)*/
	int chooseDefenderRoll(Country* defendingCountry);
	/**Get number of dice player would like to attack with (given attacking country)*/
	int chooseAttackerRoll(Country* attackingCountry);
	/**Chose country to attack from*/
	Country* chooseAttackFrom(Player* player);
	/**Chose country to attack (given origin)*/
	Country* chooseAttackTo(Country* attackFrom);
	/**Chose number of troops to move from one country to another after a victory*/
	int moveTroops(Country* attackingCountry, Country* defendingCountry);

	//FORTIFY
	/**Returns true if player wants to fortify, false otherwise*/
	bool askFortify(Player* player);
	/**Chose country to fortify from*/
	Country* chooseOriginCountryFortify(Player* player);
	/**Chose country to fortify to (guven origin)*/
	Country* chooseDestinationCountryFortify(Country* originCountry);
};

#endif