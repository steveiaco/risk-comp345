#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>

class Card {

private:

	bool isSpecial;
	std::string country; //not yet implemented

public:

	enum TroopType { Infantry, Artillery, Cavalry }; //0=infantry, 1=artillery, 2=cavalry
	TroopType type;
	Card();
	Card(TroopType newType);
	void display();

};
#endif
