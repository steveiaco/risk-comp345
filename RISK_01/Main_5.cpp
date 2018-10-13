#include "Player.h"
#include "Deck.h"
#include "Map.h"
#include "Card.h"

int main()
{
	std::cout << "=======================================\n";
	std::cout << "				 RISK MAIN 5             \n";
	std::cout << "=======================================\n";


	//Create deck from map
	std::cout << "****SETTING UP DECK****\n";
	Country* countryA = new Country("Country A");
	
	Deck* manualDeck = new Deck();
	
	for (int i = 0; i < 3; i++)
		for(int j = 0; j < 10; j++)
		manualDeck->addCard(new Card(countryA, (TroopType)i));
	

	manualDeck->display();

	//Create hand object
	std::cout << "\n****SETTING UP HAND****\n";
	Hand* hand1 = new Hand();
	Hand* hand2 = new Hand();
	Hand* hand3 = new Hand();
	Hand* hand4 = new Hand();

	try {
		for (int i = 0; i < 2; i++)
			hand1->giveCard(manualDeck->draw());
		for (int i = 0; i < 3; i++)
			hand2->giveCard(manualDeck->draw());
		for (int i = 0; i < 6; i++)
			hand3->giveCard(manualDeck->draw());
		for (int i = 0; i < 19; i++)
			hand4->giveCard(manualDeck->draw());

	}
	catch (std::invalid_argument e) {
		std::cout << e.what();
	}
	std::cout << "Hand 1:" << std::endl;
	hand1->display();
	std::cout << "Hand 2:" << std::endl;
	hand2->display();
	std::cout << "Hand 3:" << std::endl;
	hand3->display();
	std::cout << "Hand 4:" << std::endl;
	hand4->display();

	std::cout << "\n\nAttempting to exchange:\n\n";

	//Exchange hand 1, not enough cards so guaranteed fail
	std::cout << "Hand 1 Exchange...\n";
	try {
		std::cout << "Received " << hand1->exchange() << " troops.\n";
	}
	catch(std::invalid_argument e){
		std::cout << e.what() << std::endl;
	}
	//Exchange hand 2, may or may not succeed depending on card draw
	std::cout << "\nHand 2 Exchange...\n";
	try {
		std::cout << "Received " << hand2->exchange() << " troops.\n";
	}
	catch (std::invalid_argument e) {
		std::cout << e.what() << std::endl;
	}
	//Exchange hand 3, will always succeed
	std::cout << "\nHand 3 Exchange...\n";
	bool handEmpty = false;
	while (!handEmpty) {
		try {
			std::cout << "Received " << hand3->exchange() << " troops.\n";
		}
		catch (std::invalid_argument e) {
			handEmpty = true;
			std::cout << e.what() << std::endl;
		}
	}
	//Exchange hand 4, has 19 cards therefore will succeed multiple times, just to showcase the differing number of troops returned
	std::cout << "\nHand 4 Exchange...\n";
	handEmpty = false;
	while (!handEmpty) {
		try {
			std::cout << "Received " << hand4->exchange() << " troops.\n";
		}
		catch (std::invalid_argument e) {
			handEmpty = true;
			std::cout << e.what() << std::endl;
		}
	}
	
	std::cout << "\n\n";
	std::cout << "Hand 1:" << std::endl;
	hand1->display();
	std::cout << "\nHand 2:" << std::endl;
	hand2->display();
	std::cout << "\nHand 3:" << std::endl;
	hand3->display();
	std::cout << "\nHand 4:" << std::endl;
	hand4->display();

		

	/**
	Player player1("Player 1");
	for (int i = 0; i < 10; i++) {
		std::cout << player1.exchange();
	}
	**/
}
