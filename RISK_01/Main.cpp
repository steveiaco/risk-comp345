// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "Deck.h"
#include "Player.h"
#include "Card.h"
#include "Hand.h"


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

	Player player1;
	for (int i = 0; i < 10; i++) {
		std::cout << player1.exchange();
	}

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
