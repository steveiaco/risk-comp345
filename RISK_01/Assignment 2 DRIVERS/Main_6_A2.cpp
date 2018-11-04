#include "Player.h"
#include "Map.h"
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::cin;

int main() {

	Player* thisPlayer = new Player("datguy"); //it is this player's turn
	Player* defenderPlayer = new Player("disguy");

	//map setup
	Map* thisMap = new Map();
	thisMap->getValidMap();

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

	bool fortifying = true;

	while (fortifying) {

		cout << thisPlayer->getName() << ": would you like to fortify? (y/n) ";
		string input;
		std::getline(std::cin, input); std::cout << std::endl;

		//ask if player would like to continue attacking
		if (input == "N" || input == "n")
			break;

		//display owned countries
		cout << thisPlayer->getName() << ": you may fortify the following countries.\n";
		thisPlayer->printCountriesOwned();


		/*GET VALID MOVE FROM COUNTRY*/
		Country* moveFrom = NULL;

		do {
			string inp;
			cout << std::endl << thisPlayer->getName() << ": please select a country to move players from (cancel to cancel): ";
			std::getline(std::cin, inp); std::cout << std::endl;
			if (inp == "cancel")
				break;

			try {
				moveFrom = thisMap->getCountry(inp);
				//check if player owns the country
				if (!thisPlayer->ownsCountry(moveFrom)) {
					moveFrom = NULL;
					throw std::invalid_argument("You do not own this country.\n");
				}

			}
			catch (std::invalid_argument e) {
				cout << e.what();
			}
		} while (moveFrom == NULL);

		if (moveFrom == NULL)
			continue;

		cout << "You may fortify " << moveFrom->getName() << "'s neighboring countries.\n";
		moveFrom->display();

		Country* moveTo = NULL;

		/*GET VALID MOVE TO COUNTRY*/
		do {
			string inp = string();
			cout << std::endl << thisPlayer->getName() << ": please select a country to move players to (cancel to cancel): ";
			std::getline(std::cin, inp); std::cout << std::endl;

			try {
				if (inp == "cancel")
					break;
				else {
					moveTo = thisMap->getCountry(inp);

					//if the attacking player owns the selected defending country, then it is an invalid selection
					if (!thisPlayer->ownsCountry(moveTo)) {
						moveTo = NULL;
						throw std::invalid_argument("You do not own this country.");
					}

					//moveFrom must be a neighbor to moveTo
					if (!moveTo->isNeighbor(moveFrom)) {
						moveTo = NULL;
						throw std::invalid_argument("Country must be a neighbor.");
					}

				}
			}
			catch (std::invalid_argument e) {
				cout << e.what();
			}
		} while (moveTo == NULL);

		if (moveTo == NULL)
			continue;

		/*QUERY FOR NUMBER OF TROOPS TO MOVE*/
		string moveNumTroopsString;
		int moveNumTroops;
		do {
			cout << thisPlayer->getName() << ": how many troops would you like to move from " << moveFrom->getName() << " to " << moveTo->getName() << " ? [1 - " << (moveFrom->getTroops() - 1) << "] ";
			std::getline(std::cin, moveNumTroopsString); std::cout << std::endl;
			moveNumTroops = std::stoi(moveNumTroopsString);
		} while (moveNumTroops <= 0 || moveNumTroops >= moveFrom->getTroops());

		thisPlayer->fortify(moveFrom, moveTo, moveNumTroops);
		cout << thisPlayer->getName() << ": successfully moved " << moveNumTroops << " troop(s) from " << moveFrom->getName() << " to " << moveTo->getName() << ".\n";


	}

	

}
