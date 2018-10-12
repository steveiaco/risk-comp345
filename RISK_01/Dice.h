#ifndef DICE_H
#define DICE_H

#include <vector>
#include <array>
#include <iostream>
#include <cstdlib>

class Dice {

private:
	/****/
	void sortIntVector(std::vector<int>* toSort);
	int totalRolls = 0;
	int randomDice();
	int stats[6] = { 0,0,0,0,0,0 };

public:
    std::vector<int> roll(int NumRolls);
    void printPercentages();
};

#endif
