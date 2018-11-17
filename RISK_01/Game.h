#ifndef CONTROLLER
#define CONTROLLER

class Game;

#include "Player.h"
#include "Map.h"
#include <vector>
#include <random>
#include <algorithm>
#include "ObserverPlayerPhases.h"

class Game {
    private:
		/**Current turn*/
        int turn;
		/**List of players*/
        std::vector<Player*> players;

		/**The list of observers of the class**/
		std::vector<ObserverPlayerPhases*> observers {}; 
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
		//void runGameLoop();
		/**Allows player passed as argument to reinforce*/
		void reinforce(Player* player);
		/**Allows player passed as argument to attack*/
		void attack(Player* player);
		/**Allows player passed as argument to fortify*/
		void fortify(Player* player);
		/**Updates the ObserverPlayerPhases message**/
		void notify(int phase, std::string name);

    public:



		//CONSTRUCTORS
		/**Constructs a controller from a list of players on a given map*/
		Game(std::vector<Player*> players, Map* theControllerMap, Deck* theDeck);

		//DESTRUCTOR
		/**Controller destructor*/
        ~Game();

		//For testing purposes only for part 2 of the assignment3
		void runGameLoop();

		//UTILITIES
		/**Start game (run main loop until game over)*/
		void start();

		/**Attaching other observers to the class*/
		void attach(ObserverPlayerPhases* a);

		/**Detaching observers from the class*/
		void detach(ObserverPlayerPhases* a);

		/*Return current map*/
		Map* getMap();
		/*Return current deck*/
		Deck* getDeck();
};

#endif