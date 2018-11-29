#ifndef CARD
#define CARD

class Card;

#include "Country.h"
#include "Deck.h"
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
	/**Deck that card came from (good for returning card to deck)**/
	Deck* deck;

public:
	//Constructor
	//Construct a card for country country with troop type troopType that belongs to deck deck.
	Card(Country* country, TroopType troopType, Deck* deck);

	//Destructor
	/**Card Destructor*/
	~Card();

	//Getter
	/**Returns type of card.*/
	inline TroopType getType() const { return type; }

	//Utility
	//Display card details.
	void display(std::string lspace = "") const;
	/**Return card to deck that it came from*/
	void returnToDeck();
};
#endif
