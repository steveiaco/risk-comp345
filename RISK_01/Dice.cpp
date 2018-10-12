#include "Dice.h"

std::list<int> Dice::roll(int nbRolls)
{
	int totalOfDices = 0; // Necessary if we want to display total of the Roll
	std::list<int> rolls;
	for (int x = 0; x < nbRolls; x++)
	{
		int generated = randomDice();
		rolls.push_back(generated);
		stats[generated-1]++;
		totalRolls++;
		totalOfDices += nbRolls;
	}
	rolls.sort();
}

void Dice::printPercentages()
{
	for (int x = 0; x <= 5; x++)
	{
		std::cout << "You have rolled the value " << (x + 1) << ": " << stats[x] << " times. This represents " << ((double)stats[x] / totalRolls * 100) << "% of all your rolls.";
	}
}

int Dice::randomDice()
{
	return ((rand() % 6) + 1);
}

