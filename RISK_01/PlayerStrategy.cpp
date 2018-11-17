#include "PlayerStrategy.h"

bool PlayerStrategy::promptAttack()
{
	//main loop used for attack phase
	bool attacking = true;
	bool firstSuccess = true; //We want to give player a card for first victory
	while (attacking) {

		//prompt the player if they would like to attack
		if (!askAttack())
			break;

		//Show player their options. Break if no options exist.
		if (!thisPlayer->displayAttackable()) {
			std::cout << std::endl;
			break;
		}
		std::cout << std::endl;

		//get a valid attacking country and store it in attackingCountry
		Country* attackingCountry = chooseAttackFrom();

		if (attackingCountry == NULL)
			continue;

		//get a valid defending country and store it in defendingCountry
		Country* defendingCountry = chooseAttackTo(attackingCountry);

		if (defendingCountry == NULL)
			continue;

		//query attacker for number of dice
		int attackerRoll = chooseAttackerRoll(attackingCountry);

		//query defender for number of dice
		int defenderRoll = defendingCountry->getOccupant()->getStrategy()->chooseDefenderRoll(defendingCountry);


		//if we get here, then we have successfully selected an attacker and attackee, move on to calling the attack function.
		bool attackSuccessful = false; //stores whether attacker has taken over defending country
		try {
			attackSuccessful = thisPlayer->attack(attackingCountry, defendingCountry, attackerRoll, defenderRoll);
		}
		catch (std::invalid_argument e) {
			std::cout << e.what();
			exit(1);
		}

		if (attackSuccessful) {
			std::cout << thisPlayer->getName() << " has successfully invaded " << defendingCountry->getName() << std::endl;
			if (firstSuccess) {
				firstSuccess = false;
				thisPlayer->addCard(thisGame->getDeck()->draw());
				std::cout << thisPlayer->getName() << " has received a card for their first victory this round." << std::endl;
			}

			std::cout << thisPlayer->getName() << ": " << attackerRoll << " troop(s) automatically moved into " << defendingCountry->getName() << ", how many additional troops would you like to move into " << defendingCountry->getName() << "? [0-" << attackingCountry->getTroops() - 1 << "] ";
			int numTroopsToMove = moveTroopsAfterWin(attackingCountry, defendingCountry);


			defendingCountry->addTroops(numTroopsToMove);
			attackingCountry->addTroops(-numTroopsToMove);
			return true;//return true if attack is successful
		}

		return false;//return false if attack is not successful
	}
}