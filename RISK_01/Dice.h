#ifndef DICE_H
#define DICE_H

#include <list>
#include <array>
#include <iostream>
#include <cstdlib>
class Dice
{
public:
        std::list<int> roll(int NumRolls);
        void printPercentages();
private:
		int totalRolls;
        int randomDice();
		int stats[6] = { 0,0,0,0,0,0 };

};

#endif
