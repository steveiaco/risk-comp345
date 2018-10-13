#include "Player.h"
#include "Deck.h"
#include "Map.h"

int main()
{
	std::cout << "=======================================\n";
	std::cout << "				 RISK MAIN 5             \n";
	std::cout << "=======================================\n";

	//Create default map
	Map* map = new Map();
	map->display();

	//Create deck from map
	std::cout << "****SETTING UP DECK****";
	Deck* manualDeck = new Deck(map);
	//manualDeck->display();

	//Create hand object
	std::cout << "****SETTING UP HAND****";
	Hand* hand = new Hand();
	hand->giveCard(manualDeck->draw());
	hand->giveCard(manualDeck->draw());
	hand->giveCard(manualDeck->draw());


	

		


	Player player1("Player 1");
	for (int i = 0; i < 10; i++) {
		std::cout << player1.exchange();
	}

}
