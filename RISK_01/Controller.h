#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Player.h"

class Controller{
    private:
        int troopsExchanged;
        int turn;
        Player** allPlayers;//array of Player*, which needs a pointer to point to that array
        int sizeAllPlayers;
        int exchanges;
        bool startOfGame; //at the start of game, assign countries to players.

    public:
        Controller(Player** players, int sizePlayers);
        void orderOfPlay(); //randomly assigns an order of play, then sorts array in this order
        void assignArmies(); //start of game: gives armies to each player
        void endOfTurn(); //increments turn by 1
};

#endif