#ifndef DICE_H
#define DICE_H

#include <vector>
#include <array>
#include <iostream>
#include <cstdlib>

class Dice
{
public:
        std::vector<int> roll(int NumRolls);
        void printPercentages();
private:
	void sortIntVector(std::vector<int>* toSort);
		int totalRolls;
        int randomDice();
		int stats[6] = { 0,0,0,0,0,0 };

};

#endif
