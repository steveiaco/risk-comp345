#include "PlayerStrategy.h"

bool PlayerStrategy::attack(Player* player)
{
	//We will put this inside of a loop so that we can easily restart the prompts if the user so chooses
	while(true) {
		//main loop used for attack phase
		bool firstSuccess = false; //We want to give player a card for first victory

		//Show player their options. Break if no options exist.
		if (!player->displayAttackable())
			return false;

		//get a valid attacking country and store it in attackingCountry
		Country* attackingCountry = chooseAttackFrom(player);
		if (attackingCountry == NULL)
			continue;
		//get a valid defending country and store it in defendingCountry
		Country* defendingCountry = chooseAttackTo(attackingCountry);
		if (defendingCountry == NULL)
			continue;

		//get a number of attacking die
		int attackerRoll = chooseAttackerRoll(attackingCountry);
		//get a number of defending die
		int defenderRoll = defendingCountry->getOccupant()->getStrategy()->chooseDefenderRoll(defendingCountry);

		//if we get here, then we have successfully selected an attacker and attackee, move on to calling the attack function.
		bool attackSuccessful = false; //stores whether attacker has taken over defending country
		try { attackSuccessful = player->attack(attackingCountry, defendingCountry, attackerRoll, defenderRoll); }
		catch (std::invalid_argument e) {
			std::cout << e.what();
			exit(1);
		}

		if (attackSuccessful) {
			//Display a message
			std::cout << player->getName() << " has successfully invaded " << defendingCountry->getName() << std::endl;
			//Prompt for number of troops to move
			std::cout << player->getName() << ": " << attackerRoll << " troop(s) automatically moved into " << defendingCountry->getName() << ", how many additional troops would you like to move into " << defendingCountry->getName() << "? [0-" << attackingCountry->getTroops() - 1 << "] ";
			int numTroopsToMove = moveTroopsAfterWin(attackingCountry, defendingCountry);
			//Make the move
			defendingCountry->addTroops(numTroopsToMove);
			attackingCountry->addTroops(-numTroopsToMove);
			return true;//Return true (attack was successful)
		}
		return false;//return false (attack was not successful)
	}
}