#include "Player.h"


Player::Player(std::string name) {
	this->name = name;
	this->dice = new Dice();
	this->playerHand = new Hand();
}

std::string Player::getName() const {
	return name;
}

void Player::addCountry(Country* country) {
	countriesOwned.insert(country);
}

void Player::addContinent(Continent* continent) {
	continentsOwned.insert(continent);
}

bool Player::removeCountry(Country* country) {
	return countriesOwned.erase(country);
}

bool Player::removeContinent(Continent* continent) {
	return continentsOwned.erase(continent);
}

int Player::exchange() {
	return playerHand->exchange();
}

void Player::printCountriesOwned() //iterate through all countries and print their name along with troop number
{
	for (Country* country : countriesOwned) {
		std::cout << country->getName() << " - " << country->getTroops() << " troops." << std::endl;
	}
}

void Player::reinforce(Country* toReinforce, int numTroops) {

	//check whether the passed country is owned by current player
	if (!ownsCountry(toReinforce))
		throw std::invalid_argument("The player does not own this country!"); //throw an exception if trying to modify a country not owned by that player
	else {
		toReinforce->addTroops(numTroops); //add troops
	}

}

/**Method that handles attacking and defending mechanics, implementing dice rolls and their comparisons. Takes in the country to attack from, country to attack to, how many dice the attacker rolls [1,2]
and how many dice the defender rolls [1,3]. If the attacker wins the attack, numAttackerDice number of troops will be automatically moved into the defending country. Implementation of moving more troops than this
will be done within the driver.**/
bool Player::attack(Country* attackFrom, Country* attackTo, int numAttackerDice, int numDefenderDice)
{
	//Player object for the defending country.
	Player* defender = attackTo->getOccupant();
	//Player object for the attacking country.
	Player* attacker = attackFrom->getOccupant();

	//we will check if attackFrom is owned by the calling object
	if (!ownsCountry(attackFrom))
		throw std::invalid_argument("Country is not owned.");

	//we will check if attackTo is owned by the calling object
	if (ownsCountry(attackTo))
		throw std::invalid_argument("Country to attack is owned by the attacker.");

	//we will check if attackFrom is a neighbor of attackTo
	if (!(attackFrom->isNeighbor(attackTo)))
		throw std::invalid_argument("Countries are not neighbors.");

	//check whether dice input is valid
	if (numAttackerDice < 1 || numAttackerDice > 3)
		throw std::invalid_argument("Wrong number of attacker dice thrown.");

	if (numDefenderDice < 1 || numDefenderDice > 2)
		throw std::invalid_argument("Wrong number of defender dice thrown.");

	//check whether player has enough troops for the specific roll
	if (!(attackFrom->getTroops() + 1 >= numAttackerDice))
		throw std::invalid_argument("Attacker does not have enough troops for that number of dice.");

	if (!(attackTo->getTroops() >= numDefenderDice))
		throw std::invalid_argument("Defender does not have enough troops for that number of dice.");


	//roll the dice for the attacker
	std::vector<int> attackerRolled = this->getRoll(numAttackerDice);
	std::cout << std::endl << "Attacker rolled: ";

	for (int i : attackerRolled)
		std::cout << "[" << i << "]";

	//roll the dice for the defender
	std::vector<int> defenderRolled = defender->getRoll(numDefenderDice);
	std::cout << std::endl << "Defender rolled: ";

	for (int i : defenderRolled)
		std::cout << "[" << i << "]";
	
	std::cout << std::endl;

	//check how many dice we must compare (the smallest number between numAttackerDice and numDefenderDice)
	int numDiceToCompare = (numAttackerDice >= numDefenderDice) ? numDefenderDice : numAttackerDice;
	
	for (int i = 0; i < numDiceToCompare; i++) {
		if (defenderRolled[i] >= attackerRolled[i]) {
			//defender wins the roll, meaning attacker loses 1 troop
			//the attacker cannot go under 1 troop therefore we will not check this condition as it was already checked above
			attackFrom->addTroops(-1);
		}
		else {
			//attacker wins the roll, meaning defender loses 1 troop
			if (attackTo->addTroops(-1) == 0) {
				//meaning the defender has lost their country
				attackTo->changeOccupant(attacker);
				attackFrom->addTroops(-numAttackerDice);
				attackTo->addTroops(numAttackerDice);
				return 1;
			}
			//else move on

		}
			
	}

	return 0;

}

void Player::fortify(Country* moveFrom, Country* moveTo, int numberOfTroops) //move troops from one country to another
{
	//first we check if this player owns both of these countries
	if (!(this->ownsCountry(moveFrom) && this->ownsCountry(moveTo)))
		throw std::invalid_argument("Both countries are not owned by this player");

	//next condition to check is whether the countries are neighbors
	if (!(moveFrom->isNeighbor(moveTo)))
		throw std::invalid_argument("Selected countries are not neighbors.");

	//next condition to check is whether the origin country has enough troops for the action. keep in mind, a country must always have at least one army of troops on it at all times.
	if (moveFrom->getTroops() < numberOfTroops + 1)
		throw std::invalid_argument("The origin country does not have enough troops to perform this action.");

	//if these conditions are satisfied, then we can move onto the actual move operation
	moveFrom->addTroops(-numberOfTroops); //first we remove numberOfTroops from the origin country
	moveTo->addTroops(numberOfTroops); //then we add this number to the destination country


}

bool Player::ownsCountry(Country * country)
{
	if (countriesOwned.count(country))
		return true;
	else
		return false;
}

std::vector<int> Player::getRoll(int numRolls) {
	return dice->roll(numRolls);
}

void Player::printDiceStatistics()
{
	dice->display();
}

void Player::addCard(Card * card)
{
	playerHand->giveCard(card);
}

void Player::displayHand() {
	playerHand->display();
}