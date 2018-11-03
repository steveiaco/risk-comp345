#ifndef CARD
#define CARD

class Card;

#include "Country.h"
#include <string>
#include <iostream>

/**Possible troop types**/
enum TroopType { Infantry = 0, Artillery = 1, Cavalry = 2 };  //0=infantry, 1=artillery, 2=cavalry

class Card {

private:
	/**Country associated to card**/
	Country* country;
	/**Troop type of card**/
	TroopType type;

public:
	//Constructor
	//Construct a card for country country with troop type troopType.
	Card(Country* country, TroopType troopType);

	//Destructor
	/**Card Destructor*/
	~Card();

	//Getter
	/**Returns type of card.*/
	inline TroopType getType() const { return type; }

	//Utility
	//Display card details.
	void display(std::string lspace = "") const;
};
#endif
