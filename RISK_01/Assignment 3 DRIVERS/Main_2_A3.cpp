#include "../Player.h"
#include "../Map.h"
#include "../Deck.h"
#include "../Game.h"
#include <string>
#include <vector>

int main(){

    Player* thisPlayer = new Player("datguy"); //it is this player's turn
	Player* defenderPlayer = new Player("disguy");
    Player* thisPlayer2 = new Player("datguy2"); //it is this player's turn
	Player* defenderPlayer2 = new Player("disguy2");

    std::vector<Player*> allPlayers {thisPlayer, defenderPlayer, thisPlayer2, defenderPlayer2}; 

	//map setup
	Map* thisMap = new Map();

	//give countries to attacker
	thisMap->getCountry("a")->changeOccupant(thisPlayer);
	thisMap->getCountry("c")->changeOccupant(thisPlayer);

	//give countries to defender
	thisMap->getCountry("b")->changeOccupant(defenderPlayer);
	thisMap->getCountry("d")->changeOccupant(defenderPlayer);
	thisMap->getCountry("e")->changeOccupant(defenderPlayer);
	thisMap->getCountry("f")->changeOccupant(defenderPlayer);

	thisMap->getCountry("a")->addTroops(10);
	thisMap->getCountry("b")->addTroops(2);
	thisMap->getCountry("c")->addTroops(1);
	thisMap->getCountry("e")->addTroops(1);
	thisMap->getCountry("f")->addTroops(6);

	//Display map
	thisMap->display();

	//Create deck
	Deck* deck = new Deck(thisMap);

    //create observer
    ObserverPlayerPhases* a = new ObserverPlayerPhases();


    Game* someGame = new Game(allPlayers, thisMap, deck);

    someGame->attach(a);
    someGame->runGameLoop();

    return 0;
}