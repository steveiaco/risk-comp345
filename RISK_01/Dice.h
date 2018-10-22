#ifndef DICE_H
#define DICE_H

class Dice;

#include <vector>
#include <array>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

class Dice {

private:
	/**Keep count of total number of rolls made (for use in statistics)**/
	int totalRolls = 0;
	/**Keep count of total number of rolls made (for use in statistics)**/
	int stats[6] = {0,0,0,0,0,0};

public:
	//Constructors
	/**Create a standard set of dice**/
	Dice();
	~Dice();
	//Utility
	/**Return a sorted vector of nbRolls random numbers between 1 and 6. Update the stats for this set of dice. Check that numRolls is not less than 1 or greater than 3.**/
    std::vector<int> roll(int numRolls);
	/**Display stats regarding numbers rolled.**/
    void display() const;
};

#endif
