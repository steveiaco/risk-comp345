#ifndef OBSERVER_STATS
#define OBSERVER_STATS

class ObserverStats;

#include "Observer.h"
#include "Game.h"
#include <string>
#include <iostream>

class ObserverStats : public Observer {
private:
	/**Game being observed*/
	Game* game;
	/**Map that game is played on*/
	Map* map;
	/**Players playing game*/
	std::vector<Player*> players;

	//UTILITY
	/**Display current game stats*/
	void displayStats();
	/**Display congratulations to victor and display dice stats (might as well since we have them)*/
	void displayVictory();

public:
	//CONSTRUCTOR
	/**ObserverStats constructor. Constructs an observer for the game passed as an argument.*/
	ObserverStats(Game* game);

	//DESTRUCTOR
	/**ObserverStats destructor.*/
	~ObserverStats();

	//UTILITY
	/**Update the message displayed to the screen*/
	void update();
};

#endif