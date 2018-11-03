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
		/**Set up game (assign countries, randomize play order)*/
		void setup();
		/**Randomizes order of play (shuffles list of players)*/
		void randomizeOrderOfPlay();
		/**Assign all countries to players*/
		void assignCountries();
		/**Prompt players to assign starting armies to countries owned*/
		void assignArmies();

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