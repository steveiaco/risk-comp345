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
	map->getCountry("c")->changeOccupant(player1);
	map->getCountry("d")->changeOccupant(player2);
	map->getCountry("e")->changeOccupant(player2);

	player1->reinforce(map->getCountry("a"), 2); //continent A
	player1->reinforce(map->getCountry("b"), 4); //continent B
	player1->reinforce(map->getCountry("c"), 4); //continent B
	player2->reinforce(map->getCountry("d"), 4); //continent B
	player2->reinforce(map->getCountry("e"), 6); //continent B

	map->display();

	std::cout << "Countries owned by " << player1->getName() << ": \n";
	player1->printCountriesOwned();

	std::cout << "\nCountries owned by " << player2->getName() << ": \n";
	player2->printCountriesOwned();


	std::cout << "Player 1 (a) attacking Player 2 (c): ";
	try {
		std::cout << player1->attack(map->getCountry("a"), map->getCountry("c"), 2, 1) << std::endl;
	}
	catch (std::invalid_argument e) {
		std::cout << "Error: " << e.what() << std::endl;
	}

	std::cout << "Player 1 (b) attacking Player 2 (c): ";
	try {
		std::cout << (player1->attack(map->getCountry("b"), map->getCountry("c"), 2, 1)) ? "Attack Complete, country is now owned by Player 1" : "Attack Complete.";
	}
	catch (std::invalid_argument e) {
		std::cout << "Error: " << e.what() << std::endl;
	}

	player1->printCountriesOwned();
	player2->printCountriesOwned();



}

