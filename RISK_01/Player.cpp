#include "Player.h"

#include <iostream>
#include <string> 
#include <set>

Player::Player(string name) {
	this->name = name;
}

string Player::getName() const {
	return name;
}

void Player::addCountry(Country* country) {
	countriesOwned.insert(country);
}

void Player::addContinent(Continent* continent) {
	continentsOwned.insert(continent);
}

bool Player::removeCountry(Country* country) {
	return countriesOwned.erase(country);
}

bool Player::removeContinent(Continent* continent) {
	return continentsOwned.erase(continent);
}

int Player::exchange() {
	return playerHand.exchange();
}

void Player::printCountriesOwned() //iterate through all countries and print their name along with troop number

{
	for (Country* country : countriesOwned) {
		std::cout << country->getName() << " - " << country->getTroops() << " troops" << endl;
	}
}

/**
Country* Player::queryOwnedCountry() //promts the user to select a country until they enter a valid input, finds that valid country and returns a pointer to it.
{

	Country* returnedCountry;
	bool inputValid = false;

	do {

		std::cout << "Enter the name of an owned country you would like to select: ";

		//get country name from user
		string selectedCountry;
		std::cin >> selectedCountry;

		//validate the input
		try {
			returnedCountry = Map::contains(selectedCountry, countriesOwned);
		}
		catch (std::invalid_argument e) {
			std::cout << e.what();
			inputValid = false;
		}

		inputValid = true; //if we get here, means no exception was thrown, therefore a match was found

	} while (!inputValid);

	return returnedCountry;
}
**/
/**
void Player::reinforce() //count number of countries player owns, divide by 3 + value of all continents player owns
{
	//count countries, we'll assume the number of countries owned will never surpass the int limit
	int troopsFromCountries = countriesOwned.size() / 3;
	int troopsFromContinents = 0;

	for (Continent* continent : continentsOwned) {
		troopsFromContinents += continent->getValue();
	}

	int troopsAvailable = troopsFromContinents + troopsFromCountries;

	if (troopsAvailable == 0) {
		std::cerr << "Error: Player does not own any countries.";
		return;
	}
	else {

		std::cout << "Time to place troops... here are the countries " << getName() << "owns." << endl;

		printCountriesOwned();

		while (troopsAvailable > 0) {

			std::cout << "You currently have " << troopsAvailable << " troop(s) available." << endl;
			
			Country* returnedCountry = queryOwnedCountry();

			int inputNumberOfTroops = -1;
			do {
				//if we're here, it means we found a valid country, we can ask the user for a number of troops
				cout << "How many troops would you like to place on " << returnedCountry->getName() << ": ";
				cin >> inputNumberOfTroops;
			} while (inputNumberOfTroops <= 0 && inputNumberOfTroops >= troopsAvailable);

			//decrement available troops by number of troops deployed
			troopsAvailable -= inputNumberOfTroops;

			//increment number of troops on specified country
			returnedCountry->addTroops(inputNumberOfTroops);

		}
	}


}
**/

void Player::reinforce(Country* toReinforce, int numTroops) {

	//check whether the passed country is owned by current player
	if (!ownsCountry(toReinforce))
		throw invalid_argument("The player does not own this country!"); //throw an exception if trying to modify a country not owned by that player
	else {
		toReinforce->addTroops(numTroops); //add troops
	}

}
void Player::attack(Country* attackFrom, Country* attackTo) //which country attack from and to.. 
{
	//we will check if attackFrom is a neighbor of attackTo
	if (!(attackFrom->isNeighbor(attackTo)))
		throw invalid_argument("Countries are not neighbors.");
	
	//
	
}

void Player::fortify(Country* moveFrom, Country* moveTo, int numberOfTroops) //move troops from one country to another
{
	
}

bool Player::ownsCountry(Country * country)
{
	if (countriesOwned.count(country))
		return true;
	else
		return false;
}

