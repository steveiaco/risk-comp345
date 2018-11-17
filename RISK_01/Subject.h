#ifndef SUBJECT
#define SUBJECT

class Subject;

#include "Observer.h"
#include <list>

class Subject {

private:
	/**List of observers observing the subject*/
	std::list<Observer*> observers;

protected:
	//CONSTRUCTORS
	/**Default Subject constructor*/
	Subject();

public:
	//DESTRUCTOR
	/**Observer destructor*/
	virtual ~Subject();

	//UTILITY
	/**Attach new observers to the subject*/
	virtual void attach(Observer* observer);
	/**Detach an observer from the subject*/
	virtual void detach(Observer* observer);
	/**Notify the attached Observers of updates from the subject*/
	virtual void notify();
};

#endif