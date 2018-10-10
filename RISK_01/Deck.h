#ifndef DECK_H
#define DECK_H

#include <iostream>
#include <vector>
#include "Card.h"

class Deck {

private:
	std::vector<Card> cards;
	void removeCard(int index);

public:

	Deck();
	Deck(std::vector<Card> inCards);
	void addCard(Card card);
	void addCardList(std::vector<Card> inCards);
	Card* draw();

};

#endif
