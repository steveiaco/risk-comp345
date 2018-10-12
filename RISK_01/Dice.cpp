#include "Dice.h"

std::list<int> Dice::roll(int nbRolls)
{
	int totalOfDices = 0; // Necessary if we want to display total of the Roll

	std::list<int> rolls;

	for (int x = 0; x < nbRolls; x++)
	{
		int generated = randomDice();
		rolls.push_back(generated);		//Put the rolled value in the listt
		stats[generated-1]++;			//incrementing the stats value
		totalRolls++;					//Incrementing Totall rolls, used to calculate stats
		totalOfDices += nbRolls;
	}
	rolls.sort();

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

int main() {
	Dice* dicetest = &Dice();

	std::list<int> test = dicetest->roll(3);

	for (std::list<int>::iterator it = test.begin(); it != test.end(); ++it)
		std::cout << *it;
}