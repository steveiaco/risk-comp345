#include "Card.h"

Card::~Card(){
	std::cout<<"Object Card has been deleted"<<std::endl;
}

//Constructor
//Construct a card for country country with troop type troopType.
Card::Card(Country* country, TroopType troopType) {
	this->country = country;
	this->type = troopType;
}

TroopType Card::getType()
{
	return type;
}


//Utility
//Display card details.
void Card::display(std::string lspace) const {
	//Translate enum type
	std::string toRet;
	switch (type) {
	case 0: toRet = "Infantry";
		break;
	case 1: toRet = "Artillery";
		break;
	case 2: toRet = "Cavalry";
		break;
	}
	//Display card
	std::cout << lspace << "Card for " << country->getName() << " of " << toRet << " type." << std::endl;
}

