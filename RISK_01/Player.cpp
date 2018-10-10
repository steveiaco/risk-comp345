#include "Player.h"
#include "Country.h"
#include "Continent.h"
#include "Player.h"
#include "Hand.h"
//#include "Dice.h"
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

void Player::reinforce()
{
	//unimplemented
}

void Player::attack()
{
	//unimplemented
}

void Player::fortify()
{
	//unimplemented
}