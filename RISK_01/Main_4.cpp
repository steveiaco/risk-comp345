#include <iostream>
#include <vector>
#include "Deck.h"
#include "Player.h"
#include "Card.h"
#include "Hand.h"


int main()
{
	std::cout << "=======================================\n";
	std::cout << "            RISK TEST PART 2           \n";
	std::cout << "=======================================\n";

	Map* map = new Map();

	Player* player1 = new Player("Player 1");
	Player* player2 = new Player("Player 2");

	map->getCountry("a")->changeOccupant(player1);
	map->getCountry("b")->changeOccupant(player1);
	map->getCountry("c")->changeOccupant(player1);
	map->getCountry("d")->changeOccupant(player2);
	map->getCountry("e")->changeOccupant(player2);

	//TESTING REINFORCE FUNCTIONS
	player1->reinforce(map->getCountry("a"), 2); //continent A
	player1->reinforce(map->getCountry("b"), 4); //continent B
	player1->reinforce(map->getCountry("c"), 4); //continent B
	player2->reinforce(map->getCountry("d"), 2); //continent B
	player2->reinforce(map->getCountry("e"), 6); //continent B

	//display whole map
	map->display();


	//display countries owned by player 1 and 2
	std::cout << "Countries owned by " << player1->getName() << ": \n";
	player1->printCountriesOwned();

	std::cout << "\nCountries owned by " << player2->getName() << ": \n";
	player2->printCountriesOwned();
	std::cout << std::endl;

	//TESTING THE ATTACK FUNCTION
	std::cout << "Player 1 (a) attacking Player 2 (d): "; //Player attacking a non-neighboring country, should return exception
	try {
		std::cout << player1->attack(map->getCountry("a"), map->getCountry("d"), 2, 1) << std::endl;
	}
	catch (std::invalid_argument e) {
		std::cout << "Error: " << e.what() << std::endl;
	}

	std::cout << "Player 1 (b) attacking Player 1 (c): "; //Player attacking their own country, should return an exception
	try {
		std::cout << ((player1->attack(map->getCountry("b"), map->getCountry("c"), 2, 1)) ? "Attack Complete, country is now owned by Player 1" : "Attack Complete.") << std::endl;
	}
	catch (std::invalid_argument e) {
		std::cout << "Error: " << e.what() << std::endl;
	}

	std::cout << "Player 1 (b) attacking Player 2 (d): "; //Valid attack, output depends on dice roll
	try {
		std::cout << ((player1->attack(map->getCountry("b"), map->getCountry("d"), 3, 2)) ? "Attack Complete, country is now owned by Player 1" : "Attack Complete.") << std::endl;
	}
	catch (std::invalid_argument e) {
		std::cout << "Error: " << e.what() << std::endl;
	}


	//display countries owned by player 1 and 2
	std::cout << "\nCountries owned by " << player1->getName() << ": \n";
	player1->printCountriesOwned();

	std::cout << "\nCountries owned by " << player2->getName() << ": \n";
	player2->printCountriesOwned();


	//TESTING FORTIFY FUNCTION
	std::cout << "\nFortify - sending 2 troops from a to b\n";
	
	try {
		player1->fortify(map->getCountry("a"), map->getCountry("b"), 2);
	}
	catch (std::invalid_argument e) {
		std::cout << "Error: " << e.what() << std::endl;
	}


	std::cout << "Fortify - sending 1 troop from c to b\n";

	try {
		player1->fortify(map->getCountry("c"), map->getCountry("b"), 1);
	}
	catch (std::invalid_argument e) {
		std::cout << "Error: " << e.what() << std::endl;
	}

	std::cout << "\nCountries owned by " << player1->getName() << ": \n";
	player1->printCountriesOwned();

	std::cout << "\nCountries owned by " << player2->getName() << ": \n";
	player2->printCountriesOwned();

}

