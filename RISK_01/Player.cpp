#include "Player.h"
using std::string;

//Constructor
/**Standard player constructor. Constructs a player with a given name and a new hand/set of dice.*/
Player::Player(std::string name, PlayerStrategy* strategy) {
	this->name = name;
	this->dice = new Dice();
	this->hand = new Hand();
	this->strategy = strategy;
}

//Destructor
/**Player Destructor. Deletes players hand and dice.*/
Player::~Player() {
	delete dice;
	delete hand;
	delete strategy;
}

//Mutator
/**Add a given card to the player's hand*/
void Player::addCard(Card* card) { hand->addCard(card); }

//Utility
/**Allows player to add troops to country if country is owned by player. Thorws an exception if country is not owned*/
void Player::reinforce(Country* toReinforce, int numTroops) {
	//check whether the passed country is owned by current player
	if (!ownsCountry(toReinforce))
		throw std::invalid_argument(name + " does not own this country."); //throw an exception if trying to modify a country not owned by that player
	else
		toReinforce->addTroops(numTroops); //add troops
}
/**Method that handles attacking and defending mechanics, implementing dice rolls and their comparisons. Takes in the country to attack from, country to attack to, how many dice the attacker rolls [1,2]
and how many dice the defender rolls [1,3]. If the attacker wins the attack, 1 troop will be automatically moved into the defending country. Implementation of moving more troops than this
will be done within the driver.**/
bool Player::attack(Country* attackFrom, Country* attackTo, int numAttackerDice, int numDefenderDice) {
	//Player object for the defending country.
	Player* defender = attackTo->getOccupant();
	//Player object for the attacking country.
	Player* attacker = attackFrom->getOccupant();

	//we will check if attackFrom is owned by the calling object
	if (!ownsCountry(attackFrom))
		throw std::invalid_argument("Country is not owned.");

	//we will check if attackTo is owned by the calling object
	if (ownsCountry(attackTo))
		throw std::invalid_argument("Countries are owned by the same player.");

	//we will check if attackFrom is a neighbor of attackTo
	if (!(attackFrom->isNeighbor(attackTo)))
		throw std::invalid_argument("Countries are not neighbors.");

	//check whether dice input is valid
	if (numAttackerDice < 1 || numAttackerDice > 3)
		throw std::invalid_argument("Invalid number of attacker dice thrown.");

	if (numDefenderDice < 1 || numDefenderDice > 2)
		throw std::invalid_argument("Invalid number of defender dice thrown.");

	//check whether player has enough troops for the specific roll
	if (!(attackFrom->getTroops() + 1 >= numAttackerDice))
		throw std::invalid_argument("Attacker does not have enough troops for that number of dice.");

	if (!(attackTo->getTroops() >= numDefenderDice))
		throw std::invalid_argument("Defender does not have enough troops for that number of dice.");

	//roll the dice for the attacker
	std::vector<int> attackerRolled = this->getRoll(numAttackerDice);
	std::cout << "Attacker rolled: ";

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
	
	for (int i = 0; i < numDiceToCompare; i++)
		if (defenderRolled[i] >= attackerRolled[i])
			//defender wins the roll, meaning attacker loses 1 troop
			//the attacker cannot go under 1 troop therefore we will not check this condition as it was already checked above
			attackFrom->addTroops(-1);
		else
			//attacker wins the roll, meaning defender loses 1 troop
			if (attackTo->addTroops(-1) == 0) {
				//meaning the defender has lost their country
				attackTo->changeOccupant(attacker);
				//Check if defender has lost. Transfer cards in hand.
				if (defender->hasLost()) {
					std::cout << defender->getName() << " was eliminated by " << name << ". Their cards now belong to " << name << ".\n";
					defender->hand->giveHandTo(hand);
				}
				attackFrom->addTroops(-numAttackerDice);
				attackTo->addTroops(numAttackerDice);
				return true;
			}
			//else move on
	return false;
}
/**Fortify from one country to another (rules regarding how this should be done are contradictory, in this implementation, we allow player to move troops between neighboring countries)*/
void Player::fortify(Country* moveFrom, Country* moveTo, int numberOfTroops) {
	//first we check if this player owns both of these countries
	if (!(this->ownsCountry(moveFrom) && this->ownsCountry(moveTo)))
		throw std::invalid_argument("One of the countries are not owned by this player");

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
/*Returns true or false depending on if the player owns the passed country*/
bool Player::ownsCountry(Country * country) const {
	if (countriesOwned.count(country))
		return true;
	else
		return false;
}
/*Calculate the number of troops to be awarded at the beginning of the round from the number of countries and continents owned*/
int Player::calculateTroopsAwarded() const {
	int toReturn = 0;

	//first we start off with troops awarded for country ownership (minimum is 3)
	int countryTroops = this->countriesOwned.size() / 3;
	toReturn += (countryTroops >= 3) ? countryTroops : 3;

	//secondly, we calculate the number of troops awarded for contients owned
	for (Continent* cont : this->continentsOwned)
		toReturn += cont->getValue();

	//third would be troops awarded from card exchanges but we will handle that within our controller as it requires user interaction.
	return toReturn;
}
/**Display countries owned by player*/
void Player::printCountriesOwned(string lspace) const {
	//iterate through all countries and print their name along with troop number
	for (Country* country : countriesOwned)
		std::cout << lspace << country->getName() << " - " << country->getTroops() << " troops." << std::endl;
}
/**Display attack options (countries that can attack other countries). Return true if an option was found.*/
bool Player::displayAttackable() const {
	//Loop over countries, display attack options if any.
	bool hasAttackable = false;
	for (Country* country : countriesOwned)
		if (country->canAttack()) {
			hasAttackable = true;
			country->displayAttackableNeighbors();
		}
	//Print a message if no attackable neighbors
	if (!hasAttackable)
		std::cout << name << " has no options for attack." << std::endl;
	return hasAttackable;
}
/**Return whether or not player can attack.*/
bool Player::canAttack() const {
	bool hasAttackable = false;
	for (Country* country : countriesOwned)
		if (country->canAttack())
			hasAttackable = true;
	return hasAttackable;
}
/**Display player's hand*/
void Player::displayHand() const { hand->display(); }

/**Exchange cards in hand for troops (exchanges first set of three valid cards)*/
int	Player::exchange() { return hand->exchange(); }

/**Check if player can exchange thier cards*/
bool Player::canExchange() const { return (!hand->canExchange().empty()); }

/**Check if player must exchange thier cards (player must exchange cards if they have more than 5)*/
bool Player::mustExchange() const { return (hand->getSize() > 5); }

/*Rolls the dice object, [1-3] dice*/
std::vector<int> Player::getRoll(int numRolls) { return dice->roll(numRolls); }

/**Display player's dice and their statistsics*/
void Player::displayDice() const { dice->display(); }

/**Get number of cards in player's hand*/
int Player::getNumCards() const { return hand->getSize(); }

/**Prompt the player to reinforce*/
void Player::promptReinforce() { strategy->reinforce(this); };

/**Prompt the player to make an attack. Returns true if attack was successful*/
bool Player::promptAttack() { return strategy->attack(this); };

/**Prompt the player to fortify.*/
void Player::promptFortify() { strategy->fortify(this); };

/**Ask the player if they want to attack.*/
bool Player::askAttack() { return strategy->askAttack(this); };

/**Ask the player where they would like to place a troop for setup.*/
Country* Player::askSetup() { return strategy->askSetup(this); };

/**Reset the player. Map posession should already have been reset. We just need to ensure that cards in players hand are returned to deck. We will not reset dice statistics (though we could) as it makes more sense to keep them.*/
void Player::reset() {
	hand->returnToDeck();
}