#include "pch.h"
#include <iostream>
#include <vector>
#include "Card.cpp"

class Deck {

private:
	std::vector<Card> cards;

	void removeCard(int index) {//using index, remove card from deck

	}

public:

	Deck() { //default constructor, does not populate cards vector
		//does nothing... empty deck
	}

	Deck(std::vector<Card> inCards) { //constructor in which takes a vector of cards and copies it to "cards"
		for (Card c : inCards) {
			cards.push_back(c);
		}
	}

	void addCard(Card card) { //append 1 card to the deck
		cards.push_back(card);
	}

	void addCardList(std::vector<Card> inCards) { //append card list to deck
		for (Card c : inCards) {
			cards.push_back(c);
		}
	}

	Card* draw() {//returns a random Card object from the deck, and removes said card from the deck

		//first, lets get the size of the deck
		int size = cards.size();

		if (size == 0) {
			std::cerr << "Error: Deck has no cards or has not been initialized.";
			Card* placeholder = new Card();
			return placeholder; //must return something
		}

		//we must generate a random number between [0,size-1]
		int randomIndex = rand() * size;
		Card* toReturn = &cards[randomIndex];
		
		return toReturn;
	}


};