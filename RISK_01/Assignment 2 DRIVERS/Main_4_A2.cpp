#include "Map.h"
#include "Player.h"
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::cin;

int main() {
	
	//this main class code will have variables and objects will be incorporated in the main game loop at a future date
	//objects such as the player will not be specific to one player in the real implementation, this is just to showcase.

	Player* thisPlayer = new Player("datguy");
	Player* playerB = new Player("disguy");

	//map setup
	Map* thisMap = new Map();

	//give countries to A
	thisMap->getCountry("a")->changeOccupant(thisPlayer);
	thisMap->getCountry("c")->changeOccupant(thisPlayer);

	//give countries to B
	thisMap->getCountry("b")->changeOccupant(playerB);
	thisMap->getCountry("d")->changeOccupant(playerB);
	thisMap->getCountry("e")->changeOccupant(playerB);
	thisMap->getCountry("f")->changeOccupant(playerB);

	//populate with troops
	thisMap->getCountry("a")->addTroops(3);
	thisMap->getCountry("b")->addTroops(2);
	thisMap->getCountry("c")->addTroops(1);
	thisMap->getCountry("e")->addTroops(4);
	thisMap->getCountry("f")->addTroops(6);
	thisMap->getCountry("d")->addTroops(6);

	//Display map
	thisMap->display();

	//Give player 6 cards
	Deck* deck = new Deck(thisMap);
	for (int i = 0; i < 6; i++)
		thisPlayer->addCard(deck->draw());

	int troopsAvailable = 0;

	//get the number of troops available from the countries the player owns and the contienent values
	troopsAvailable += thisPlayer->calculateTroopsAwarded();

	//Show player their cards
	thisPlayer->displayHand();

	//check whether the player must exchange cards (has more than 6 cards)
	while (thisPlayer->mustExchange()) {
		std::cout << "You have " << thisPlayer->getNumCards() << ", cards. You can hold no more than 5 at a time. Here is an automatic exchange.\n";
		troopsAvailable += thisPlayer->exchange();
	}

	//now we will check whether the player can exchange, if they can then we will ask if they want to exchange
	while (thisPlayer->canExchange()) {
		std::string input;
		std::cout << "You currently have " << thisPlayer->getNumCards() << " cards and can exchange, would you like to do so? (Y/N) ";
		std::getline(std::cin, input); std::cout << std::endl;
		if (input == "Y" || input == "y")
			troopsAvailable += thisPlayer->exchange();
		else if (input == "N" || input == "n")
			break;
	}

	std::cout << "You have a total of " << troopsAvailable << " troops available to place.\n";

	//now we can ask the player to start placing their troops

	std::cout << "You can now start placing troops on the countries you own.\nHere is a list of countries in your possession:\n";

	thisPlayer->printCountriesOwned();

	while (troopsAvailable != 0) {
		std::string countrySelectedString;
		std::cout << "You have " << troopsAvailable << " troops lefts to place, which country would you like to add troops to? ";
		std::getline(std::cin, countrySelectedString); std::cout << std::endl;

		Country* countrySelected;
		try {
			countrySelected = thisMap->getCountry(countrySelectedString);
		}
		catch (std::invalid_argument e) {
			std::cout << "Country does not exist, try again.\n";
			continue;
		} if (!thisPlayer->ownsCountry(countrySelected)) {
			std::cout << "You do not own this country, try again.\n";
			continue;
		}

		std::string numTroopsToPlaceString;
		int numTroopsToPlace;
		do {
			std::cout << "You have selected " << countrySelected->getName() << ". How many troops would you like to place on this country? (Max: " << troopsAvailable << ") : ";
			std::getline(std::cin, numTroopsToPlaceString); std::cout << std::endl;
			try { numTroopsToPlace = std::stoi(numTroopsToPlaceString); }
			catch (std::invalid_argument& e) {
				std::cout << "Invalid input. Input must be a valid integer value.\n";
				continue;
			}
		} while (numTroopsToPlace > troopsAvailable || numTroopsToPlace < 0);
		thisPlayer->reinforce(countrySelected, numTroopsToPlace);
		std::cout << "You have placed " << numTroopsToPlace << " troops on " << countrySelected->getName() << " giving it " << countrySelected->getTroops() << " total members.\n";
		troopsAvailable -= numTroopsToPlace;
	}

	//Display map
	std::cout << std::endl;
	thisMap->display();

	delete thisMap;
	delete thisPlayer;
	delete playerB;
	delete deck;

	thisMap = NULL;
	thisPlayer = NULL;
	playerB = NULL;
	deck = NULL;
}