#include <iostream>
#include <new>
using namespace std;

#include "Dice.h"


static int totalRolls;
int stats[6];
int lastRoll[] = { 0,0,0 };

void Roll()
{
	lastRoll = { 0,0,0 };
	int nbRolls;
	int totalOfDices = 0; // Necessary if we want to display total of the Roll


	cout << "How many dices do you wish to roll (1, 2 or 3)?\n";
	cin >> nbRolls;


	//int *lastRoll = new int[nbRolls];  // REALLY NOT SURE HERE NEED HELP


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

void Stats()
{
	for (int x = 0; x <= 5; x++)
	{
		cout << "You have rolled the value " << (x + 1) << ": " << stats[x] << " times. This represents " << ((double)stats[x] / totalRolls * 100) << "% of all your rolls.";
	}
}


int* GetLastRoll()
{
	return lastRoll; // returns a pointer, right?
}


int RandomDice()
{
	const int n = 5;
	int remainder = RAND_MAX % n;
	int x;
	do {
		x = rand();
	} while (x >= RAND_MAX - remainder);


	return 1 + x % n;


}

