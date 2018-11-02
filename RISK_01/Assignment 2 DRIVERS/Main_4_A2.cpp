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
	thisMap->getValidMap();

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


	int troopsAvailable = 0;

	//get the number of troops available from the countries the player owns and the contienent values
	troopsAvailable += thisPlayer->calculateTroopsAwarded();

	//check whether the player must exchange cards (has more than 6 cards)
	while (thisPlayer->mustExchange()) {
		cout << "You have " << thisPlayer->getNumCards() << ", a number which is greater than 5, therefore here is an automatic exchange.\n";
		troopsAvailable += thisPlayer->exchange();
	}

	//now we will check whether the player can exchange, if they can then we will ask if they want to exchange
	while (thisPlayer->canExchange()) {
		char input;
		cout << "You currently have " << thisPlayer->getNumCards() << " cards and can exchange, would you like to do so? (Y/N) ";
		cin >> input;
		if (input == 'Y' || input == 'y')
			troopsAvailable += thisPlayer->exchange();
		else if (input == 'N' || input == 'n')
			break;
	}

	cout << "You have a total of " << troopsAvailable << " troops available to place.\n";

	//now we can ask the player to start placing their troops

	cout << "You can now start placing troops on the countries you own.\nHere is a list of countries in your possession:\n";

	thisPlayer->printCountriesOwned();

	while (troopsAvailable != 0) {
		string countrySelectedString;
		cout << "You have " << troopsAvailable << " troops lefts to place, which country would you like to add troops to? ";
		cin >> countrySelectedString;

		Country* countrySelected;
		try {
			countrySelected = thisMap->getCountry(countrySelectedString);
		}
		catch (std::invalid_argument e) {
			cout << "Country does not exist, try again.\n";
			continue;
		}

		if (!thisPlayer->ownsCountry(countrySelected)) {
			cout << "You do not own this country, try again.\n";
			continue;
		}


		int numTroopsToPlace;

		do {
			cout << "You have selected " << countrySelected->getName() << ". How many troops would you like to place on this country? (Max: " << troopsAvailable << ") : ";
			cin >> numTroopsToPlace;
		} while (numTroopsToPlace > troopsAvailable || numTroopsToPlace < 0);

		thisPlayer->reinforce(countrySelected, numTroopsToPlace);
		cout << "You have placed " << numTroopsToPlace << " troops on " << countrySelected->getName() << " giving it " << countrySelected->getTroops() << " total members.\n";

		troopsAvailable -= numTroopsToPlace;
	
	}
}