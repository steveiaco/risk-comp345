#ifndef HAND_H
#define HAND_H

#include "Card.h"
#include <iostream>
#include <unordered_set>


class Hand {

private:
	/**Cards in hand**/
	std::vector<Card*> hand;
	/**Number of times a player has exchanged cards**/
	static int timesExchanged;

public:
	//Constructor
	/**Default constructor. Creates an empty hand.**/
	Hand();
	/**Add card to hand.**/
	void addCard(Card* card);
	int exchange();
	void display();
};

#endif
