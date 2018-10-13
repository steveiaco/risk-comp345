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

	//check if the players either has a minimum of 3 identical cards, or 3 unique cards
	if (!(countInfantry() >= 3 || countArtillery() >= 3 || countCavalry() >= 3) || !(countInfantry() >= 1 && countArtillery() >= 1 && countCavalry() >= 1))
		throw std::invalid_argument("You do not have three identical cards or three cards from differents sets.");

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
		std::cout << std::endl;
		index++;
	}
}
