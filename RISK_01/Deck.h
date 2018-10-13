#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <iostream>
#include <unordered_set>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

class Deck {

private:
	/**Set of cards in deck**/
	std::unordered_set<Card*> cards;

public:
	//Constructors
	/**Create a deck for a given map (a card will be added for each country in map, cards troop types will be evenly distributed)**/
	Deck(Map* map);

	//Mutators
	/**Add card to deck. Returns exception if card is already in deck.**/
	void addCard(Card* card);

	//Utility
	/**Draw a card from the deck. Remove it from set of cards and return it.**/
	Card* draw();
};

#endif
