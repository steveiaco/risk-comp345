#include "Hand.h"

int Hand::timesExchanged = 0;

/**Default constructor. Creates an empty hand.**/
Hand::Hand() {
	hand = std::unordered_set<Card*>();
}

//Destructor
/**Hand destructor. Deletes hand and cards in hand.*/
Hand::~Hand(){
	//Delete cards in hand
	hand.clear();
}

//Mutators
/**Add a card to the player's hand.**/
void Hand::addCard(Card* card) {
	if (!hand.insert(card).second)
		throw std::invalid_argument("This card is already in the player's hand.");
}

//Utility
/**Check if player has the right combinations of cards to exchange. Return those cards if so, return NULL otherwise.**/
std::unordered_set<Card*> Hand::canExchange() const {
	//Create an empty set of cards for returning
	std::unordered_set<Card*> toRet;
	//If player has less than 3 cards, they will not have anough to form a set, return the empty set
	if (hand.size() < 3)
		return toRet;
	//Get set of cards of different types. Check for sets of 3 at the same time.
	std::unordered_set<Card*> infantry = std::unordered_set<Card*>();
	std::unordered_set<Card*> cavalry = std::unordered_set<Card*>();
	std::unordered_set<Card*> artillery = std::unordered_set<Card*>();
	for (Card* card: hand)
		switch (card->getType()) {
			case 0:
				infantry.insert(card);
				if (infantry.size() > 2) //If we find more than two infantry cards, return them
					return infantry;
				break;
			case 1:
				cavalry.insert(card);
				if (cavalry.size() > 2) //If we find more than two cavalry cards, return them
					return cavalry;
				break;
			case 2:
				artillery.insert(card);
				if (artillery.size() > 2) //If we find more than two artillery cards, return them
					return artillery;
				break;
		}
	//Add the first element of every set to toRet. If toRet ends up with 3 elements, it contains one of each type.
	if (infantry.size() != 0)
		toRet.insert(*infantry.begin());
	if (cavalry.size() != 0)
		toRet.insert(*cavalry.begin());
	if (artillery.size() != 0)
		toRet.insert(*artillery.begin());

	if (toRet.size() == 3)
		return toRet;
	else
		return std::unordered_set<Card*>();
}
/**Remove cards in toExchange from player's hand. Return the number of troops that the cards were excahnged for. Check that the set of cards is valid for exchange.**/
int Hand::exchange() {
	//Get cards to exchange
	std::unordered_set<Card*> toExchange = canExchange();
	//Check if the players either has a minimum of 3 identical cards, or 3 unique cards
	if (toExchange.size() != 3)
		throw std::invalid_argument("You can not exchange your cards.\nYou need three cards of different or identical troop type to exchange.");
	for (auto it = toExchange.begin(); it != toExchange.end(); it++)
			returnCardToDeck(*it);
	//Add one to times excahnged and return the appropriate number of armies. Armies recieved should be 5 for the first exchange and 5 more for each additional exchange.
	return (++timesExchanged * 5);
}
/**Transfer cards from one hand to another. Useful for moving cards when player is eliminated.**/
void Hand::giveHandTo(Hand* otherHand) {
	for (auto it = hand.begin(); it != hand.end();) {
		Card* lastCard = *it;
		it++;
		otherHand->addCard(lastCard);
		hand.erase(lastCard);
	}
}
/**Display contents of a hand.**/
void Hand::display() const {
	std::cout << "Cards in hand: \n";
	int index = 1;
	for (Card* card : hand) {
		std::cout << "  Card " << index << ": ";
		card->display();
		index++;
	}
}
/**Return a card to the deck that it came from*/
void Hand::returnCardToDeck(Card* card) {
	if (!hand.count(card))
		throw std::invalid_argument("This should never happen.");
	hand.erase(card);
	card->returnToDeck();
}
/**Return all cards in hand to deck*/
void Hand::returnToDeck() {
	for (auto it = hand.begin(); it != hand.end();) {
		Card* lastCard = *it;
		it++;
		returnCardToDeck(lastCard);
	}
}
