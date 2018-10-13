#include "Card.h"


Card::Card() { //default constructor
	type = Infantry;
}

Card::Card(TroopType newType) {
	type = newType;
}

void Card::display() {
	std::string toRet;
	switch (type) {
	case 0: toRet = "Infantry";
		break;
	case 1: toRet = "Artillery";
		break;
	case 2: toRet = "Cavalry";
		break;
	}

	std::cout << toRet;
}

