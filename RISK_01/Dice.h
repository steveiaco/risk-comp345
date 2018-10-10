#pragma once
class Dice
{
public:
        void Roll();
        void Stats();
int* GetLastRoll();
private:
        int RandomDice();
};