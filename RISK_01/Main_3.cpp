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
			std::vector<int> rollsDice = dice1.roll(nbRolls);
			rollSuccessful = true;
		}
		catch (std::invalid_argument& e) {
			std::cout << e.what() << "\nTry again.\n\n";
		}

	std::cout << "Values rolled: \n";
	for (int x : rollsDice)
		std::cout << "hi" << std::endl;

	dice1.display();
	rollSuccessful = false;

	//Dice 2
	while (rollSuccessful == false)
		try {
		std::cout << "How many dice do you want to roll for dice1? (Try a value out of range if you want to test that feature)\n";
		std::cin >> nbRolls;
		std::vector<int> rollsDice = dice2.roll(nbRolls);
		rollSuccessful = true;
	}
	catch (std::invalid_argument& e) {
		std::cout << e.what() << "\nTry again.\n\n";
	}

	std::cout << "\nValues rolled: \n";
	for (int x : rollsDice)
		std::cout << x << std::endl;

	dice2.display();

	return 0;
}
