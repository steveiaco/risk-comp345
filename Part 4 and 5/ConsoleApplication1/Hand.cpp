#include "pch.h"
#include "Card.cpp"
#include <vector>

class Hand {

	//we will use an array list to make the size of the hand expandable and reducable
private:
	
	std::vector<Card> hand;
	int* timesExchanged;

public:

	Hand(int* t) { 
		timesExchanged = t;
	}

	void giveCard(Card card) {
		hand.push_back(card);
	}

	int exchange() {
		int armies;

		//must implement the checks for number of cards, returning cards to the deck.. etc...

		switch (*timesExchanged) {
		case 0: armies = 4; //first set traded
			break;
		case 1: armies = 6; //second set
			break;
		case 2: armies = 8; //third set
			break;
		case 3: armies = 10; //fourth set
			break;
		case 4: armies = 12; //fifth set
			break;
		case 5: armies = 15; //sixth set
			break;
		default: 
			if (*timesExchanged >= 6) {
				armies = 15 + ((*timesExchanged - 5) * 5);
			}
			else {
				std::cerr << "This shouldn't happen...";
				armies = 0;
			}
			break;
		}

		return armies;
	}
};