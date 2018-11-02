#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Player.h"
#include "Map.h"

class Controller{
    private:
        int troopsExchanged;
        int turn;
        Player** allPlayers;//array of Player*, which needs a pointer to point to that array
        int sizeAllPlayers;
        int exchanges;
        bool startOfGame; //at the start of game, assign countries to players.
        Map* theControllerMap;

        std::unordered_set<Country*> MapCountries;

    public:
        Controller(Player** players, int sizePlayers, Map* theControllerMap);
        ~Controller();

        //accessors
        Map* getControllerMap() const;
        int getTurn() const;
        int getSizeArrayPlayer() const;
        int getNumberExchanges() const;
        bool isStartOfGame() const;

        void orderOfPlay(); //randomly assigns an order of play, then sorts array in this order
        void assignArmies(); //start of game: gives armies to each player
        void endOfTurn(); //increments turn by 1
        void playerTurn(); //events happening during a player's turn
        void assignCountries();
        void organizeStartOfGame();//organizes the start of game setup
        void ownACountry(int indexPlayer, Country* country);//what happens when player owns a country


};

#endif