#ifndef HAND_H
#define HAND_H

#include "Card.h"
#include <iostream>
#include <vector>


class Hand {

private:

	//we will use an array list to make the size of the hand expandable and reducable
	std::vector<Card*> hand;
	static int timesExchanged;
	int countInfantry();
	int countArtillery();
	int countCavalry();

public:

	//Constructor
	Hand();
	
	//Mutator
	void giveCard(Card* card);
	int exchange();
	
	//Utility
	void display();
	void giveHandTo(Hand* hand); //used when player dies, will give current hand to person to kills them.

};

#endif
