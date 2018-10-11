#include <iostream>
#include <new>
using namespace std;

#include "Dice.h"


static int totalRolls;
int stats[6];

 Dice::Dice() {
	 Roll(3);
}

void Dice::Roll(int nbRolls)
{
	int totalOfDices = 0; // Necessary if we want to display total of the Roll



	for (int x = 0; x < nbRolls; x++)
	{
		int randomNum = RandomDice();


		lastRoll[x] = randomNum;
		cout << "You have rolled a " << randomNum << ".\n";


		stats[randomNum - 1]++;
		totalRolls++;
		totalOfDices += randomNum;
	}
}

void Dice::Stats()
{
	for (int x = 0; x <= 5; x++)
	{
		cout << "You have rolled the value " << (x + 1) << ": " << stats[x] << " times. This represents " << ((double)stats[x] / totalRolls * 100) << "% of all your rolls.";
	}
}


int* Dice::GetLastRoll()
{
	return lastRoll; // returns a pointer, right?
}


int Dice::RandomDice()
{
	const int n = 5;
	int remainder = RAND_MAX % n;
	int x;
	do {
		x = rand();
	} while (x >= RAND_MAX - remainder);


	return 1 + x % n;


}

