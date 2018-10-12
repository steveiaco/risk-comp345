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
	Map* map = &Map();

	Player* player1 = &Player("Player 1");
	Player* player2 = &Player("Player 2");

	player1->addCountry(map->getCountry("a"));
	player1->addCountry(map->getCountry("b"));
	player2->addCountry(map->getCountry("c"));
	player2->addCountry(map->getCountry("d"));
	player2->addCountry(map->getCountry("e"));

	std::cout << "Countries owned by " << player1->getName();
	player1->printCountriesOwned();

	std::cout << "Countries owned by " << player2->getName();
	player2->printCountriesOwned();

}

