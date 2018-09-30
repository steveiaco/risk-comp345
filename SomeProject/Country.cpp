#include <string.h>
#include "Country.h"

Country::Country(char *nameOfCountry){
            troops = 0;
            numberOfOwnerPlayer = 0; //0 is not assigned to a player!!
            int len = strlen(nameOfCountry);
            name = new char[len];
            strncpy(name, nameOfCountry,len); //to refer to this country, name applied (must be less than 20 char).
            //https://www.ibm.com/support/knowledgecenter/en/SS2LWA_12.1.0/com.ibm.xlcpp121.bg.doc/language_ref/cplr035.html
}

inline int Country::getTroops() const{
    return troops;
}

inline int Country::getOwner() const{
    return numberOfOwnerPlayer;
}

inline char* Country::getName() const{
    return name;
}

std::vector<Country*> Country::getNeighborCountries() const{
    return neighborCountries;
}

void Country::setNeighborCountry(Country* country){
    neighborCountries.push_back(country);
}