#ifndef CONTROLLER
#define CONTROLLER

class Game;

#include "Player.h"
#include "Map.h"
#include <vector>
#include <random>
#include <algorithm>

class Game {
    private:
		/**Current turn*/
        int turn;
		/**List of players*/
        std::vector<Player*> players;
		/**Map played on*/
        Map* map;
		/**Deck of cards used in game*/
		Deck* deck;

		//UTILITIES
		/**Randomizes order of play (shuffles list of players)*/
		void randomizeOrderOfPlay();
		/**Prompt players to assign starting armies to countries owned*/
		void assignArmies();
		/**Runs main game loop until game is over*/
		void runGameLoop();
		/**Allows player passed as argument to reinforce*/
		void reinforce(Player* player);
		/**Allows player passed as argument to attack*/
		void attack(Player* player);
		/**Allows player passed as argument to fortify*/
		void fortify(Player* player);

    public:
		//CONSTRUCTORS
		/**Constructs a controller from a list of players on a given map*/
		Game(std::vector<Player*> players, Map* theControllerMap, Deck* theDeck);

		//DESTRUCTOR
		/**Controller destructor*/
        ~Game();

		//UTILITIES
		/**Start game (run main loop until game over)*/
		void start();

};

#endif