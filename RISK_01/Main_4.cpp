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
	Map* map = new Map();

	Player* player1 = new Player("Player 1");
	Player* player2 = new Player("Player 2");

	map->getCountry("a")->changeOccupant(player1);
	map->getCountry("b")->changeOccupant(player1);
	map->getCountry("c")->changeOccupant(player2);
	map->getCountry("d")->changeOccupant(player2);
	map->getCountry("e")->changeOccupant(player2);

	map->display();

	std::cout << std::endl << "Countries owned by " << player1->getName() << std::endl;
	player1->printCountriesOwned();

	std::cout << "Countries owned by " << player2->getName() << std::endl;
	player2->printCountriesOwned();

	
	delete map;
}

