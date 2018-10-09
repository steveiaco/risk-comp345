#ifndef PLAYER_H
#define PLAYER_H

#include "Hand.h"

class Player {

private:

	//std::vector<Country> countryList;
	Hand playerHand;

public:

	int exchange() {
		return playerHand.exchange();
	}

	void reinforce() ; //count number of countries / 3, count how many continents owned

	void attack() ;

	void fortify() ;
};

#endif