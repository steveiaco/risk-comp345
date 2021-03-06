#ifndef PLAYERSTRATEGY_H
#define PLAYERSTRATEGY_H

class PlayerStrategy;

#include "Player.h"

class PlayerStrategy {
public:
	//HIGH LEVEL UTILITIES
	/**Prompt for an attack. Returns true if attack was successful. Determines attack for passed player.*/
	virtual bool attack(Player*);
	/**Prompt for reinforcements. Determines reinforcement for passed player.*/
	virtual void reinforce(Player*);
	/**Prompt for fortifications. Determines fortification for passed player.*/
	virtual void fortify(Player*);
	/**Returns true if player wants to attack, false otherwise*/
	virtual bool askAttack(Player*) = 0;
	/**Prompt for where to place setup troop.*/
	virtual Country* askSetup(Player*) = 0;

	//DESTRUCTORS
	/**Player Strategy destructor*/
	virtual ~PlayerStrategy();

protected:
	//CONSTRUCTORS
	/**PlayerStrategy constructor (doesn't do anything special)*/
	PlayerStrategy();

	//LOW LEVEL UTILITIES

	//REINFORCE
	/**Choose a country to reinforce*/
	virtual Country* chooseReinforceCountry(Player*) = 0;
	/**Choose number of troops to reinforce with*/
	virtual int chooseNumberOfTroopsToReinforce(Country* reinforcedCountry, int troopsAvailable) = 0;
	/**Ask if player wants to exchange cards for troops*/
	virtual bool askExchange() = 0;

	//ATTACK
	/**Get number of dice player would like to defend with (given defending country)*/
	virtual int chooseDefenderRoll(Country* defendingCountry) = 0;
	/**Get number of dice player would like to attack with (given attacking country)*/
	virtual int chooseAttackerRoll(Country* attackingCountry) = 0;
	/**Chose country to attack from*/
	virtual Country* chooseAttackFrom(Player*) = 0;
	/**Chose country to attack (given origin)*/
	virtual Country* chooseAttackTo(Country* attackFrom) = 0;
	/**Chose number of troops to move from one country to another after a victory*/
	virtual int chooseMoveTroops(Country* attackingCountry, Country* defendingCountry) = 0;

	//FORTIFY
	/**Returns true if player wants to fortify, false otherwise*/
	virtual bool askFortify(Player*) = 0;
	/**Chose country to fortify from*/
	virtual Country* chooseOriginCountryFortify(Player*) = 0;
	/**Chose country to fortify to (guven origin)*/
	virtual Country* chooseDestinationCountryFortify(Country* originCountry) = 0;
};

#endif