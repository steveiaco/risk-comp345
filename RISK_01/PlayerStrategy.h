#ifndef PLAYERSTRATEGY_H
#define PLAYERSTRATEGY_H

#include "Player.h"
#include "Game.h"

class PlayerStrategy {
public:
	/*Highest level functions*/
	virtual bool promptAttack() = 0;//returns true if the attack was successful
	virtual void promptReinforce() = 0;
	virtual void promptFortify() = 0;

/*Apparently these methods need to be public in order for sibling objects to access them.. i thought protected attributes allowed this behavior..*/
//protected:

	/*Strategy methods for attack phase*/
	virtual bool askAttack() = 0;
	virtual int chooseDefenderRoll(Country* defendingCountry) = 0; //choose defender roll, pass the defending country in order to verify the input
	virtual int chooseAttackerRoll(Country* attackingCountry) = 0; //choose attacker roll, pass the attacking country in order to verify the input
	virtual Country* chooseAttackFrom() = 0; //choose country to attack from
	virtual Country* chooseAttackTo(Country* attackFrom) = 0; //choose country to attack using attackFrom (passed object used for verification of chosen country, chosen country must not be owned and must be a neighbor)
	virtual int moveTroopsAfterWin(Country* attackingCountry, Country* defendingCountry) = 0;
	/*Helper methods for reinforce, fortify phase*/
	virtual bool askFortify() = 0;
	virtual Country* chooseOriginCountry() = 0; //choose country to move troops from
	virtual Country* chooseDestinationCountry(Country* originCountry) = 0; //choose a neighbor to the origin country


	Game* thisGame;
	Player* thisPlayer;
};

#endif