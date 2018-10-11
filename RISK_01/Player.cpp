#include "Player.h"

#include <iostream>
#include <string>
#include <set>
using namespace std;

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

void Player::reinforce() //count number of countries player owns, divide by 3 + value of all continents player owns
{
	//count countries, we'll assume the number of countries owned will never surpass the int limit
	int troopsFromCountries = countriesOwned.size / 3;
	int troopsFromContinents = 0;

	for (Continent* continent : continentsOwned) {
		troopsFromContinents += continent->getValue();
	}

	int troopsAvailable = troopsFromContinents + troopsFromCountries;

	if (troopsAvailable == 0) {
		std::cerr << "Error: Player does not own any countries";
		return;
	}
	else {

		std::cout << "Time to place troops... here are the countries " << getName() << "owns." << endl;

		//iterate through all countries and print their name
		for (Country* country : countriesOwned) {
			std:cout << country->getName() << endl;
		}

		while (troopsAvailable > 0) {

			std::cout << "You currently have " << troopsAvailable << " troops available." << endl;
			Country* returnedCountry;
			bool inputValid = false;
			do {

				std::cout << "Enter the name of the country you would like to select: ";

				//get country name from user
				string selectedCountry;
				std:cin >> selectedCountry;

				//validate the input
				try { 
					returnedCountry = countryExists(selectedCountry); 
				}
				catch (std::invalid_argument e) {
					inputValid = false;
				}

				inputValid = true; //if we get here, means no exception was thrown, therefore a match was found

			} while (!inputValid);

			int inputNumberOfTroops = -1;
			do {
				//if we're here, it means we found a valid country, we can ask the user for a number of troops
				cout << "How many troops would you like to place on " << returnedCountry->getName << ": ";
				cin >> 
			} while (inputNumberOfTroops >= 0 && inputNumberOfTroops <= troopsAvailable);

		}
	}


}

void Player::attack()
{
	//unimplemented
}

void Player::fortify()
{
	//unimplemented
}

Country* Player::countryExists(string input)
{
	return Map::contains(input, countriesOwned);
}
