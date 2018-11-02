#include "Map.h"
#include "Controller.h"
#include "Player.h"

int main(){

    Map* validMap = new Map();
    validMap->getValidMap();

    Player* player1 = new Player("Player 1");
	Player* player2 = new Player("Player 2");

    Player* players[2];
    players[0]=player1;
    players[1]=player2;
    std::cout << "Players initiated"<<std::endl;

    Controller* control = new Controller(players, 2, validMap);

    validMap = NULL;
    player1 = NULL;
    player2 = NULL;


}