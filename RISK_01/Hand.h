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

public:

	Hand();
	void giveCard(Card* card);
	int exchange();
	void display();
};

#endif
