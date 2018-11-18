#include "PlayerStrategy.h"

/**PlayerStrategy constructor*/
PlayerStrategy::PlayerStrategy() { }
/**PlayerStrategy destructor*/
PlayerStrategy::~PlayerStrategy() { }

/**Prompt for attacks. Determines attacks for passed player.*/
bool PlayerStrategy::attack(Player* player)
{
	//We will put this inside of a loop so that we can easily restart the prompts if the user so chooses
	while(true) {
		//main loop used for attack phase
		bool firstSuccess = false; //We want to give player a card for first victory
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
			int numTroopsToMove = moveTroops(attackingCountry, defendingCountry);
			//Make the move
			defendingCountry->addTroops(numTroopsToMove);
			attackingCountry->addTroops(-numTroopsToMove);
			return true;//Return true (attack was successful)
		}
		return false;//return false (attack was not successful)
	}
}

/**Prompt for reinforcements. Determines reinforcement for passed player.*/
void PlayerStrategy::reinforce(Player* player) {
	int troopsAvailable = 0;
	//Get the number of troops available from the countries the player owns and the continent values
	troopsAvailable += player->calculateTroopsAwarded();

	//Show player their cards
	player->displayHand();
	std::cout << std::endl;
	//Check whether the player must exchange cards (has more than 6 cards)
	while (player->mustExchange()) {
		std::cout << "You have " << player->getNumCards() << ", cards. You can hold no more than 5 at a time. Here is an automatic exchange.\n";
		troopsAvailable += player->exchange();
	}
	//Now we will check whether the player can exchange. If they can, we will ask if they want to exchange
	while (player->canExchange())
		std::cout << "You can exchange 3 of your cards. Would you like to do so? (y/n) ";
		if (askExchange())
			troopsAvailable += player->exchange();

	//Now we can ask the player to start placing their troops
	std::cout << "You have a total of " << troopsAvailable << " troops available to place.\n";
	std::cout << "You can now start placing troops on the countries you own.\nHere is a list of countries in your possession:\n";
	player->printCountriesOwned("\t");
	//Loop until player runs out of reinforcements
	while (troopsAvailable != 0) {
		//Get country to reinforce
		std::cout << "You have " << troopsAvailable << " troops left to place, which country would you like to add troops to? ";
		Country* countrySelected = chooseAttackFrom(player);
		//Get number of troops to reinforce with
		std::cout << "You have selected " << countrySelected->getName() << ". How many troops would you like to place on this country? (Max: " << troopsAvailable << ") : ";
		int numTroopsToPlace = chooseNumberOfTroopsToReinforce(countrySelected, troopsAvailable);
		//Display results
		std::cout << "You have placed " << numTroopsToPlace << " troops on " << countrySelected->getName() << " giving it " << countrySelected->getTroops() << " total members.\n";
		troopsAvailable -= numTroopsToPlace;
	}
}

/**Prompt for fortifications. Determines fortification for passed player.*/
void PlayerStrategy::fortify(Player* player) {
	//Put everything in a loop to simplify restarting
	while (true) {
		//Ask if player would like to fortify
		std::cout << player->getName() << ": would you like to fortify? (y/n) ";
		if (!askFortify(player))
			return;

		/*GET VALID MOVE FROM COUNTRY*/
		std::cout << std::endl << player->getName() << ": please select a country to move armies from (cancel to cancel): ";
		Country* moveFrom = chooseOriginCountryFortify(player);
		//We will return null if player cancels
		if (moveFrom == NULL)
			break;

		/*GET VALID MOVE TO COUNTRY*/
		std::cout << "You may fortify " << moveFrom->getName() << "'s neighboring countries: \n";
		moveFrom->displayNeighbors("/t");
		std::cout << std::endl << player->getName() << ": please select a country to move armies to (cancel to cancel): ";
		Country* moveTo = chooseDestinationCountryFortify(moveFrom);
		//We will return null if player cancels
		if (moveTo == NULL)
			continue;

		/*GET NUMBER OF TROOPS TO MOVE*/
		std::cout << player->getName() << ": how many troops would you like to move from " << moveFrom->getName() << " to " << moveTo->getName() << " ? [1 - " << (moveFrom->getTroops() - 1) << "] (cancel to cancel): ";
		int numTroops = moveTroops(moveFrom, moveTo);
		//We will return null if player cancels
		if (numTroops == NULL)
			continue;

		//Make the move
		player->fortify(moveFrom, moveTo, numTroops);
		std::cout << player->getName() << ": successfully moved " << numTroops << " troop(s) from " << moveFrom->getName() << " to " << moveTo->getName() << ".\n";
		break;
	}
}