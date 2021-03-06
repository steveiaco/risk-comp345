#ifndef DECK
#define DECK

class Deck;

#include "Card.h"
#include "Deck.h"
#include "Map.h"
#include <iostream>
#include <unordered_set>
#include <stdlib.h>
#include <time.h>

class Deck {

private:
	/**Set of cards in deck**/
	std::unordered_set<Card*> cards;

public:
	//Constructors
	/**Create a deck for a given map (a card will be added for each country in map, cards troop types will be evenly distributed)**/
	Deck(Map* map);
	/**Default constructor. Creates an empty deck for testing.**/
	Deck();

	//Destructor
	/**Deck destructor*/
	~Deck();

	//Mutators
	/**Add card to deck. Returns exception if card is already in deck.**/
	void addCard(Card* card);

	//Utility
	/**Draw a card from the deck. Remove it from set of cards and return it.**/
	Card* draw();
	/**Display contents of deck.**/
	void display() const;
};

#endif
