#include <string.h>
#include "Country.h"

Country::Country(char *nameOfCountry){
            isTaken = false;//not assigned to continent
            troops = 0;
            numberOfOwnerPlayer = 0; //0 is not assigned to a player!!
            int len = strlen(nameOfCountry);
            name = new char[len];
            strncpy(name, nameOfCountry,len); //to refer to this country, name applied (must be less than 20 char).
            //https://www.ibm.com/support/knowledgecenter/en/SS2LWA_12.1.0/com.ibm.xlcpp121.bg.doc/language_ref/cplr035.html
}

bool Country::getIsTaken() const{
    return this->isTaken;
}

void Country::setIsTaken(){
    this->isTaken = true;
}

int Country::getTroops() const{
    return this->troops;
}

void Country::addTroops(int numberAdded){
    this->troops+=numberAdded;
}

void Country::removeTroops(int numberRemoved){
    this->troops-=numberRemoved;
}

int Country::getOwner() const{
    return this->numberOfOwnerPlayer;
}

void Country::changeOwner(int numberOfOwner){
    this->numberOfOwnerPlayer=numberOfOwner;
}

char* Country::getName() const{
    return this->name;
}

std::vector<Country*> Country::getNeighborCountries() const{
    return this->neighborCountries;
}

void Country::setNeighborCountry(Country* country){
    neighborCountries.push_back(country);
}