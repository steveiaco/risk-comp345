#ifndef CONTROLLER
#define CONTROLLER

class Game;

#include "Subject.h"
#include "Player.h"
#include "Deck.h"
#include "Map.h"
#include "Deck.h"
#include "AggressiveAI.h"
#include "BenevolentAI.h"
#include "CheaterAI.h"
#include "RandomAI.h"
#include "HumanPlayer.h"
#include <vector>
#include <random>
#include <algorithm>
#include <string>

/**Possible game states**/
enum GameState { SETUP = 0, REINFORCE = 1, ATTACK = 2, FORTIFY = 3, END = 4 };

class Game: public Subject {
    private:
		/**Current turn*/
        int turn;
		/**Max number of turns*/
		int maxTurns;
		/**Current player*/
		Player* currentPlayer;
		/**Current game state*/
		GameState currentState;

		/**List of players*/
        std::vector<Player*> players;
		/**Map played on*/
		Map* map;
		/**Deck of cards used in game*/
		Deck* deck;

		/**Set to true if you want to be able to swap player strategies for testing*/
		bool swapType;
		/**Set to true if you want the game to pause between rounds so that a human player can read what is going on*/
		bool pauseToRead;

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
		/**Pause the output and wait for user to read*/
		void pause();
		/**Prompts the user to swap strategy employed by a player for another*/
		void swapStrategy(Player* player);

    public:
		//CONSTRUCTORS
		/**Constructs a game for a given list of players on a given map. Game lasts at most maxTurns. Set max turns to null for game to last until one player wins.*/
		Game(std::vector<Player*> players, Map* theControllerMap, Deck* theDeck, int maxTurns);

		//DESTRUCTOR
		/**Controller destructor*/
        ~Game();

		//MUTATORS
		/**Set swapType (for testing)*/
		inline void setSwapType(bool in) { swapType = in; }
		/**Set pauseToRead (this should be turned off to speed up tournament mode)*/
		inline void setPauseToRead(bool in) { pauseToRead = in; }

		//ACCESSORS
		/**Get map (good for attached observers)*/
		inline Map* getMap() { return map; };
		/**Get players (good for attached observers)*/
		inline std::vector<Player*> getPlayers() { return players; };
		/**Get current turn (good for attached observers)*/
		inline int getCurrentTurn() { return turn; };
		/**Get max number of turns (good for attached observers)*/
		inline int getMaxTurns() { return maxTurns; };
		/**Get current player (good for attached observers)*/
		inline Player* getCurrentPlayer() { return currentPlayer; };
		/**Get current game state (good for attached observers)*/
		inline GameState getCurrentState() { return currentState; };

		//UTILITIES
		/**Start game (run main loop until game over)*/
		Player* start();
};

#endif
