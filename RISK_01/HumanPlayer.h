#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "PlayerStrategy.h";


class HumanPlayer : public PlayerStrategy {
public:
	//constructor
	HumanPlayer(Game* passedGame, Player* passedPlayer);

	bool attack();
	void reinforce();
	void fortify();

};

#endif