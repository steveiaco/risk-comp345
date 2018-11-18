#ifndef PLAYERSTRATEGY_H
#define PLAYERSTRATEGY_H

#include "Player.h"
#include "Game.h"

class PlayerStrategy {
public:
	//HIGH LEVEL UTILITIES
	/**Prompt for an attack. Returns true if attack was successful. Determines attack for passed player.*/
	bool attack(Player* player);
	/**Prompt for reinforcements. Determines reinforcement for passed player.*/
	void reinforce(Player* player);
	/**Prompt for fortifications. Determines fortification for passed player.*/
	void fortify(Player* player);

protected:
	//CONSTRUCTORS
	/**PlayerStrategy constructor (doesn't do anything special)*/
	PlayerStrategy();

	//DESTRUCTORS
	/**Player Strategy destructor*/
	virtual ~PlayerStrategy();

	//LOW LEVEL UTILITIES

	//REINFORCE
	/**Choose a country to reinforce*/
	virtual Country* chooseReinforceCountry() = 0;

	//ATTACK
	/**Returns true if player wants to attack, false otherwise*/
	virtual bool askAttack(Player* player) = 0;
	/**Get number of dice player would like to defend with (given defending country)*/
	virtual int chooseDefenderRoll(Country* defendingCountry) = 0;
	/**Get number of dice player would like to attack with (given attacking country)*/
	virtual int chooseAttackerRoll(Country* attackingCountry) = 0;
	/**Chose country to attack from*/
	virtual Country* chooseAttackFrom(Player* player) = 0;
	/**Chose country to attack (given origin)*/
	virtual Country* chooseAttackTo(Country* attackFrom) = 0;
	/**Chose number of troops to move from one country to another after a victory*/
	virtual int moveTroopsAfterWin(Country* attackingCountry, Country* defendingCountry) = 0;

	//FORTIFY
	/**Returns true if player wants to fortify, false otherwise*/
	virtual bool askFortify(Player* player) = 0;
	/**Chose country to fortify from*/
	virtual Country* chooseOriginCountry(Player* player) = 0;
	/**Chose country to fortify to (guven origin)*/
	virtual Country* chooseDestinationCountry(Country* originCountry) = 0;
};

#endif