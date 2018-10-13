#include "Player.h"
#include "Deck.h"
/**
int main()
{

	std::vector<int> test(5);

	Deck* manualDeck = new Deck();

	Card* card1 = new Card(Card::Infantry);
	Card* card2 = new Card(Card::Artillery);
	Card* card3 = new Card(Card::Cavalry);
	Card* card4 = new Card(Card::Infantry);

	card1->toString();
	card2->toString();
	card3->toString();
	card4->toString();

	manualDeck->addCard(*card1);
	manualDeck->addCard(*card2);
	manualDeck->addCard(*card3);
	manualDeck->addCard(*card4);

	Player player1("Hello");
	for (int i = 0; i < 10; i++) {
		std::cout << player1.exchange();
	}

}
**/