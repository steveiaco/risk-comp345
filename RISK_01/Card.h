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
>>>>>>> 370d851e3d102637f68ee610c2a36b54a07c3d4a
};
#endif
