#ifndef OBSERVER_PLAYER_PHASES
#define OBSERVER_PLAYER_PHASES

#include "Observer.h"
#include "Game.h"
#include <string>

class ObserverPlayerPhase: public Observer {
    private:
		/**Game being observed*/
		Game* game;

		//UTILITY
		/**Display header for current game state*/
		void diplayHeader();

    public:
		//CONSTRUCTOR
		/**ObserverPlayerPhase constructor. Constructs an observer for the game passed as an argument.*/
        ObserverPlayerPhase(Game* game);

		//DESTRUCTOR
		/**ObserverPlayerPhase destructor.*/
		~ObserverPlayerPhase();

		//UTILITY
        /**Update the message (header) displayed to the screen*/
        void update();
};

#endif