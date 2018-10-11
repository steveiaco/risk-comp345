#ifndef DICE_H
#define DICE_H
class Dice
{
public:
		std::array<int, 3> lastRoll = {0,0,0};
        void Roll(int NumRolls);
        void Stats();
		int* GetLastRoll();
private:
        int RandomDice();
};

#endif
