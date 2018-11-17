#include "Subject.h"

//CONSTRUCTORS
/**Default Subject constructor*/
Subject::Subject() {
	observers = std::list<Observer*>();
}

//DESTRUCTOR
/**Subject destructor*/
Subject::~Subject() {
}

//UTILITY
/**Attach new observers to the subject*/
void Subject::attach(Observer* observer) {
	observers.push_back(observer);
}
/**Detach an observer from the subject*/
void Subject::detach(Observer* observer) {
	observers.remove(observer);
}
/**Notify the attached Observers of updates from the subject*/
void Subject::notify() {
	for (Observer* o : observers)
		o->update();
}