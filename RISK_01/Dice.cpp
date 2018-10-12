#include "Dice.h"

Dice::Dice() {
}

/**The roll method takes in a number between [1,3] and returns a list of dice roll results whose length is equal to said number.*/
std::vector<int> Dice::roll(int nbRolls)
{
	std::vector<int> rolls = *new std::vector<int>();
	
	for (int x = 0; x < nbRolls; x++)
	{
		int generated = randomDice();
		rolls.push_back(generated);		//Put the rolled value in the listt
		stats[generated-1]++;			//incrementing the stats value
		totalRolls++;					//Incrementing Totall rolls, used to calculate stats
	}
	std::sort(rolls.begin(), rolls.end());

	return rolls;
}

void Dice::printPercentages()			//Prints the percentage value of all 6 dice value rolles
{
	for (int x = 0; x <= 5; x++)
	{
		std::cout << "You have rolled the value " << (x + 1) << ": " << stats[x] << " times. This represents " << ((double)stats[x] / totalRolls * 100) << "% of all your rolls.";
	}
}

int Dice::randomDice() //Method to generate random value from 1 to 6
{
	return ((rand() % 6) + 1);
}

void Dice::sortIntVector(std::vector<int>* toSort)
{
	for(size_t i = 0; i < toSort->size(); i++)
		for(size_t j = i; j < toSort->size(); j++)
			if ((*toSort)[j] > (*toSort)[i]) { //then swap
				int temp = (*toSort)[i];
				(*toSort)[i] = (*toSort)[j];
				(*toSort)[j] = temp;
			}
}
