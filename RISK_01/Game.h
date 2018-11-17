#ifndef CONTROLLER
#define CONTROLLER

class Game;

#include "Player.h"
#include "Map.h"
#include <vector>
#include <random>
#include <algorithm>
#include "ObserverPlayerPhase.h"
#include "Subject.h"

/**Possible game states**/
enum GameState { SETUP = 0, REINFORCE = 1, ATTACK = 2, FORTIFY = 3, END = 4 };

class Game: public Subject {
    private:
		/**Current turn*/
        int turn;
		/**Current player*/
		Player* currentPlayer;
		/**Current game state*/
		GameState currentState;

		/**List of players*/
        std::vector<Player*> players;
<<<<<<< HEAD
=======

		/**The list of observers of the class**/
		std::vector<ObserverPlayerPhases*> observers {}; 
>>>>>>> 1711f791a64474f51a5262d7170f64797f95b62a
		/**Map played on*/
		Map* map;
		/**Deck of cards used in game*/
		Deck* deck;
<<<<<<< HEAD

=======
>>>>>>> 1711f791a64474f51a5262d7170f64797f95b62a
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
<<<<<<< HEAD
=======



>>>>>>> 1711f791a64474f51a5262d7170f64797f95b62a
		//CONSTRUCTORS
		/**Constructs a controller from a list of players on a given map*/
		Game(std::vector<Player*> players, Map* theControllerMap, Deck* theDeck);

		//DESTRUCTOR
		/**Controller destructor*/
        ~Game();

		//ACCESSORS
		/**Get current turn (good for attached observers)*/
		inline int getCurrentTurn() { return turn; };
		/**Get current player (good for attached observers)*/
		inline Player* getCurrentPlayer() { return currentPlayer; };
		/**Get current game state (good for attached observers)*/
		inline GameState getCurrentState() { return currentState; };

		//UTILITIES
		/**Start game (run main loop until game over)*/
		void start();
<<<<<<< HEAD
=======

		/**Attaching other observers to the class*/
		void attach(ObserverPlayerPhases* a);

		/**Detaching observers from the class*/
		void detach(ObserverPlayerPhases* a);

		/*Return current map*/
		Map* getMap();
		/*Return current deck*/
		Deck* getDeck();
>>>>>>> 1711f791a64474f51a5262d7170f64797f95b62a
};

#endif