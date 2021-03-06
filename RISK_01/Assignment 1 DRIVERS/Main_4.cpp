#include <iostream>
#include <vector>
#include "Deck.h"
#include "Player.h"
#include "Card.h"
#include "Hand.h"

/*
int main()
{
	std::cout << "=======================================\n";
	std::cout << "            RISK TEST PART 4           \n";
	std::cout << "=======================================\n";

	Map* map = new Map();

	//display whole map
	map->display();
	std::cout << "=======================================\n";


	Player* player1 = new Player("Player 1");
	Player* player2 = new Player("Player 2");

	map->getCountry("a")->changeOccupant(player1);
	map->getCountry("b")->changeOccupant(player1);
	map->getCountry("c")->changeOccupant(player1);
	map->getCountry("d")->changeOccupant(player2);
	map->getCountry("e")->changeOccupant(player1);

	//display countries owned by player 1 and 2
	std::cout << "Countries owned by " << player1->getName() << ": \n";
	player1->printCountriesOwned();

	std::cout << "\nCountries owned by " << player2->getName() << ": \n";
	player2->printCountriesOwned();
	std::cout << std::endl;

	std::cout << "\n****TESTING THE REINFORCE FUNCTION****\n\n";

	//TESTING REINFORCE FUNCTIONS
	std::cout << "Reinforcing a (2 troops).\n";
	player1->reinforce(map->getCountry("a"), 2); //continent A

	std::cout << "Reinforcing b (4 troops).\n";
	player1->reinforce(map->getCountry("b"), 4); //continent B

	std::cout << "Reinforcing c (4 troops).\n";
	player1->reinforce(map->getCountry("c"), 4); //continent B

	std::cout << "Reinforcing d (2 troops).\n";
	player2->reinforce(map->getCountry("d"), 2); //continent B

	std::cout << "Reinforcing e (6 troops).\n\n";
	player1->reinforce(map->getCountry("e"), 6); //continent B



	//display countries owned by player 1 and 2
	std::cout << "Countries owned by " << player1->getName() << ": \n";
	player1->printCountriesOwned();

	std::cout << "\nCountries owned by " << player2->getName() << ": \n";
	player2->printCountriesOwned();
	std::cout << std::endl;

	//TESTING THE ATTACK FUNCTION
	std::cout << "\n****TESTING THE ATTACK FUNCTION****\n\n";
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
	std::cout << "\n****TESTING THE FORTIFY FUNCTION****\n\n";
	std::cout << "Fortify - sending 2 troops from a to b\n";

	try {
		player1->fortify(map->getCountry("a"), map->getCountry("b"), 2); //Origin country does not have enough troops to do this, should error out.
		std::cout << "Success!";
	}
	catch (std::invalid_argument e) {
		std::cout << "Error: " << e.what() << std::endl;
	}

	std::cout << "Fortify - sending 2 troops from a to b\n";

	try {
		player1->fortify(map->getCountry("a"), map->getCountry("c"), 2); //Origin is not a neighbor of destination, should error out.
		std::cout << "Success!";
	}
	catch (std::invalid_argument e) {
		std::cout << "Error: " << e.what() << std::endl;
	}

	std::cout << "Fortify - sending 1 troop from c to b\n";

	try {
		player1->fortify(map->getCountry("c"), map->getCountry("b"), 1); //Will work properly.
		std::cout << "Success!";
	}
	catch (std::invalid_argument e) {
		std::cout << "Error: " << e.what() << std::endl;
	}

	std::cout << "\nCountries owned by " << player1->getName() << ": \n";
	player1->printCountriesOwned();

	std::cout << "\nCountries owned by " << player2->getName() << ": \n";
	player2->printCountriesOwned();

	//DISPLAY THE DICE STATISTICS
	std::cout << "\n****DISPLAY INDIVIDUAL PLAYER DICE STATISTICS****\n";
	std::cout << "\nStatistics for Player 1 \n\n";
	player1->printDiceStatistics();
	std::cout << "\nStatistics for Player 2 \n\n";
	player2->printDiceStatistics();

	//DISPLAY HAND
	std::cout << "\n****DISPLAY PLAYER HANDS STATISTICS****\n";
	player1->addCard(new Card(Card::Infantry));
	player1->addCard(new Card(Card::Artillery));
	player1->addCard(new Card(Card::Cavalry));
	player1->addCard(new Card(Card::Cavalry));

	player2->addCard(new Card(Card::Artillery));
	player2->addCard(new Card(Card::Artillery));
	player2->addCard(new Card(Card::Cavalry));

	std::cout << "Player 1 Cards:\n";
	player1->displayHand();
	std::cout << "Player 2 Cards:\n";
	player2->displayHand();

}*/
