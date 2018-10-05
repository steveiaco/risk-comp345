#include "pch.h"
#include <string>
#include <iostream>

class Card {

public:
	enum TroopType { Infantry, Artillery, Cavalry }; //0=infantry, 1=artillery, 2=cavalry

private:

	TroopType type;
	bool isSpecial;
	std::string country; //not yet implemented

public:

	Card() { //default constructor
		type = Infantry;
	}

	Card(TroopType newType) {
		type = newType;
	}



	void toString() { //just testing
		std::string toRet;
		switch (type) {
		case 0: toRet = "Infantry";
			break;
		case 1: toRet = "Artillery";
			break;
		case 2: toRet = "Cavalry";
			break;
		}

		std::cout << "I am " << toRet << std::endl;
	}

};