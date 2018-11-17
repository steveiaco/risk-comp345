#ifndef PLAYERSTRATEGY_H
#define PLAYERSTRATEGY_H

#include "Player.h"
#include "Game.h"

class PlayerStrategy {
public:
	virtual bool attack() = 0;//returns true if the attack was successful
	virtual void enforce() = 0;
	virtual void fortify() = 0;

protected:
	Player* thisPlayer;
	Game* thisGame;
};

#endif