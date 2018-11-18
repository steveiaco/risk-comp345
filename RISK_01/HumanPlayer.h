#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "PlayerStrategy.h"
#include <string>



class HumanPlayer : public PlayerStrategy {
public:
	//constructor
	HumanPlayer();

	bool promptAttack(); 
	void promptReinforce();
	void promptFortify();

protected:

	//LOW LEVEL UTILITIES

	//REINFORCE
	/**Choose a country to reinforce*/
	 Country* chooseReinforceCountry(Player* thisPlayer);
	/**Choose number of troops to reinforce with*/
	int chooseNumberOfTroopsToReinforce(Country* reinforcedCountry, int troopsAvailable);
	/**Ask if player wants to exchange cards for troops*/
	bool askExchange();

	//ATTACK
	/*Asks player whether they would like to attack*/
	bool askAttack(Player* thisPlayer);
	/**Get number of dice player would like to defend with (given defending country)*/
	int chooseDefenderRoll(Country* defendingCountry);
	/**Get number of dice player would like to attack with (given attacking country)*/
	int chooseAttackerRoll(Country* attackingCountry);
	/**Chose country to attack from*/
	Country* chooseAttackFrom(Player* thisPlayer);
	/**Chose country to attack (given origin)*/
	Country* chooseAttackTo(Country* attackFrom);
	/**Chose number of troops to move from one country to another after a victory*/
	int moveTroops(Country* attackingCountry, Country* defendingCountry);

	//FORTIFY
	/**Returns true if player wants to fortify, false otherwise*/
	bool askFortify(Player* thisPlayer);
	/**Chose country to fortify from*/
	Country* chooseOriginCountryFortify(Player* thisPlayer);
	/**Chose country to fortify to (guven origin)*/
	Country* chooseDestinationCountryFortify(Country* originCountry);
};	


#endif