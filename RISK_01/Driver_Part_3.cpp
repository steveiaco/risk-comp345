#include <iostream>
#include "Dice.h"


int main() {
	
	Dice dice1;
	Dice dice2;
	int nbRolls;

	//Dice 1
	std::cout << "How many dices do you want to roll for dice1? (1,2 or 3)";
	std::cin >> nbRolls;
	std::list<int> rollsDice1 = dice1.roll(nbRolls);

	for (auto x : rollsDice1)
		std::cout << x;

	dice1.printPercentages();

	//Dice 2
	std::cout << "How many dices do you want to roll for dice2? (1,2 or 3)";
	std::cin >> nbRolls;
	std::list<int> rollsDice2 = dice2.roll(nbRolls);

	for (auto x : rollsDice2)
		std::cout << x;

	dice2.printPercentages();
	return 0;
}
