#include "Card.h"

//Constructor
//Construct a card for country country with troop type troopType.
Card::Card(Country* country, TroopType troopType) {
	this->country = country;
	this->type = troopType;
}

//Utility
//Display card details.
void Card::display(std::string lspace) const {
	std::string toRet;
	switch (type) {
	case 0: toRet = "Infantry";
		break;
	case 1: toRet = "Artillery";
		break;
	case 2: toRet = "Cavalry";
		break;
	}

	std::cout << lspace << "Card for " << country->getName() << " of " << toRet << " type." << std::endl;
}

