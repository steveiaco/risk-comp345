#ifndef CARD_H
#define CARD_H

#include "country.h"
#include <string>
#include <iostream>

class Card {
	
	/**Possible troop types**/
	enum TroopType { Infantry, Artillery, Cavalry };  //0=infantry, 1=artillery, 2=cavalry

private:
	/**Country associated to card**/
	Country* country;
	/**Troop type of card**/
	TroopType type;

public:
	//Constructor
	//Construct a card for country country with troop type troopType.
	Card(Country* country, TroopType troopType);

	//Utility
	//Display card details.
	void display(std::string lspace = "") const;
};
#endif
