#ifndef OBSERVER
#define OBSERVER

class Observer;

#include "Subject.h"

class Observer {

protected:
	//CONSTRUCTORS
	/**Default Observer constructor*/
	Observer();
public:
	//DESTRUCTOR
	/**Observer destructor*/
	virtual ~Observer();
	//UTILITY
	/**Update the Observer with updates from the subject (most often, this means updating the visuals displayed)*/
	virtual void update() = 0;
};

#endif