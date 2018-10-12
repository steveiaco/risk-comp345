﻿#include "Dice.h"

//Constructors
/**Create a standard set of dice**/
Dice::Dice() {
	srand(time(NULL));
}

//Utility
/**Return a sorted vector of nbRolls random numbers between 1 and 6. Update the stats for this set of dice. Check that numRolls is not less than 1 or greater than 3.**/
std::vector<int> Dice::roll(int nbRolls) {
	//This is where we will store the numbers rolled
	std::vector<int> rolls = *new std::vector<int>();
	//Generate a random number between 1 and 6, add it to the vector of numbers to return and increase the tally for that number in stats
	for (int x = 0; x < nbRolls; x++) {
		int generated = (rand() % 6) + 1; 
		rolls.push_back(generated);
		stats[generated-1]++;
	}
	//Sort numbers rolled
	std::sort(rolls.begin(), rolls.end(), [](const int a, const int b) -> bool { return a > b; });
	//Add to total rolls, used to calculate stats
	totalRolls+=nbRolls;				
	return rolls;
}
/**Display stats regarding numbers rolled.**/
void Dice::display() const {
	for (int x = 0; x <= 5; x++)
		std::cout << "You have rolled the value " << (x + 1) << ": " << stats[x] << " times. This represents " << ((double)stats[x] / totalRolls * 100) << "% of all your rolls.";
}