#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "PlayerStrategy.h";
#include <string>



class HumanPlayer : public PlayerStrategy {
public:
	//constructor
	HumanPlayer(Game* passedGame, Player* passedPlayer);

	bool promptAttack() = 0; 
	void promptReinforce() = 0;
	void promptFortify() = 0;

protected:

	/*Helper methods for attack phase*/
	bool askAttack();
	int chooseDefenderRoll(Country* defendingCountry); //choose defender roll
	int chooseAttackerRoll(Country* attackingCountry); //choose attacker roll
	Country* chooseAttackFrom(); //choose country to attack from
	Country* chooseAttackTo(Country* attackFrom); //choose country to attack using attackFrom (passed object used for verification of chosen country, chosen country must not be owned and must be a neighbor)
	int moveTroopsAfterWin(Country* attackingCountry, Country* defendingCountry);

	/*Helper methods for reinforce, fortify phase*/
	bool askFortify();
	Country* chooseOriginCountry() = 0; //choose country to move troops from
	Country* chooseDestinationCountry(Country* originCountry) = 0; //choose a neighbor to the origin country
};	


#endif