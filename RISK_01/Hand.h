#ifndef HAND
#define HAND

class Hand;

#include "Card.h"
#include <iostream>
#include <unordered_set>

class Hand {

private:
	/**Cards in hand**/
	std::unordered_set<Card*> hand;
	/**Number of times a player has exchanged cards**/
	static int timesExchanged;

public:
	//Constructor
	/**Default constructor. Creates an empty hand.**/
	Hand();

	//Destructor
	/**Hand destructor*/
	~Hand();

	//Mutators
	/**Add card to hand.**/
	void addCard(Card* card);

	//Accessors
	/**Get hand size.**/
	inline int getSize() const { return hand.size(); }
	
	//Utility
	/**Display contents of a hand.**/
	void display() const;
	/**Check if player has the right combinations of cards to exchange. Return those cards.**/
	std::unordered_set<Card*> canExchange() const;
	/**Remove cards in toExchange from player's hand. Return the number of troops that the cards were excahnged for. Check that the set of cards is valid for exchange.**/
	int exchange();
	/**Transfoer cards from one hand to another. Useful for moving cards when player is eliminated.**/
	void giveHandTo(Hand* hand);

};

#endif
