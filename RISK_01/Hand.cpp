#include "Hand.h"


int Hand::timesExchanged;


int Hand::countInfantry()
{
	int count = 0;
	for (Card* card : hand)
		if (card->getType() == TroopType::Infantry)
			count++;
	return count;
}

int Hand::countArtillery()
{
	int count = 0;
	for (Card* card : hand)
		if (card->getType() == TroopType::Artillery)
			count++;
	return count;
}

int Hand::countCavalry()
{
	int count = 0;
	for (Card* card : hand)
		if (card->getType() == TroopType::Cavalry)
			count++;
	return count;
}

void Hand::giveHandTo(Hand * hand)
{
}

Hand::Hand() {
	timesExchanged = 0;
}

void Hand::giveCard(Card* card) {
	//>5 cards must call exchange
	hand.push_back(card);
}

int Hand::exchange() {

	int armies;
	int numInfantry = countInfantry();
	int numArtillery = countArtillery();
	int numCavalry = countCavalry();

	bool hasThreeIdenticalCards = (numInfantry >= 3 || numArtillery >= 3 || numCavalry >= 3);
	bool hasThreeDifferentCards = (numInfantry >= 1 && numArtillery >= 1 && numCavalry >= 1);

	//check if the players either has a minimum of 3 identical cards, or 3 unique cards
	if (!hasThreeIdenticalCards && !hasThreeDifferentCards)
		throw std::invalid_argument("You do not have three identical nor unique cards.");

	if (hasThreeIdenticalCards) { //this covers the case where there are both three identical cards and three unique cards, and where there are only three identical cards (hasThreeIdenticalCards && hasThreeDifferentCards) || hasThreeIdenticalCards
		//find the three identical card type
		TroopType toCompare;
		//if we must remove 3 identical infantry cards
		if (numInfantry >= 3) {
			toCompare = Infantry;
		}
		//if we must remove 3 identical artillery cards
		else if (numArtillery >= 3) {
			toCompare = Artillery;
		}
		//if we must remove 3 identical cavalry cards
		else if (numCavalry >= 3) {
			toCompare = Cavalry;
		}

		int count = 0; //number of cards removed
		for (int i = 0; i < hand.size() && count < 3; i++)
			if (hand[i]->getType() == toCompare) {
				hand.erase(hand.begin() + i);
				count++;
			}

	}

	if (hasThreeDifferentCards) {
		//we must iterate and remove one card of each type
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < hand.size(); j++)
				if (hand[j]->getType() == static_cast<TroopType>(i)) {
					hand.erase(hand.begin() + j);
					break;
				}
		}
	}


	switch (timesExchanged) {
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
		if (timesExchanged >= 6) {
			armies = 15 + ((timesExchanged - 5) * 5);
		}
		else {
			std::cerr << "This shouldn't happen...";
			armies = 0;
		}
		break;
	}

	timesExchanged++;
	return armies;
}

void Hand::display()
{
	int index = 1;
	for (Card* card : hand) {
		std::cout << "Card " << index << ": ";
		card->display();
		index++;
	}
}
