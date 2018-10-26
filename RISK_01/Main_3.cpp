#include <iostream>
#include "Dice.h"

int main() {
	
	Dice dice1;
	Dice dice2;
	int nbRolls;
	std::vector<int> rollsDice;
	bool rollSuccessful = false;

	//Dice 1
	while (rollSuccessful == false)
		try {
			std::cout << "How many dice do you want to roll for dice1? (Try a value out of range if you want to test that feature)\n";
			std::cin >> nbRolls;
			rollsDice = dice1.roll(nbRolls);
			rollSuccessful = true;
		}
		catch (std::invalid_argument& e) {
			std::cout << e.what() << "\nTry again.\n\n";
		}

	std::cout << "\nValues rolled: ";
	for (int i : rollsDice)
		std::cout << "[" << i << "]";
	std::cout << std::endl << std::endl;

	dice1.display();
	std::cout << std::endl << std::endl;
	rollSuccessful = false;

	//Dice 2
	while (rollSuccessful == false)
		try {
			std::cout << "How many dice do you want to roll for dice2? (Try a value out of range if you want to test that feature)\n";
			std::cin >> nbRolls;
			rollsDice = dice2.roll(nbRolls);
			rollSuccessful = true;
		}
		catch (std::invalid_argument& e) {
			std::cout << e.what() << "\nTry again.\n\n";
		}

	std::cout << "\nValues rolled: ";
	for (int i : rollsDice)
		std::cout << "[" << i << "]";
	std::cout << std::endl << std::endl;

	dice2.display();
	std::cout << std::endl << std::endl;

	//Show that dice are balanced
	Dice dice3;
	for (int i = 0; i < 10000; i++)
		rollsDice = dice3.roll(3);
	std::cout << "Rolling dice3 10000 * 3.\n";
	dice3.display();

	return 0;
}
