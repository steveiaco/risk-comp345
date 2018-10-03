#include "Continent.h"
#include <string.h>

Continent::Continent(char* nameContinent){
    int len = strlen(nameContinent);
    name = new char[len];
    strncpy(name, nameContinent,len);
}

std::vector<Country*> Continent::getCountries() const{
    return listCountries;
}

char* Continent::getContinentName() const{
    return name;
}

Country* Continent::getCountry(char *nameCountry){ //returns null if no result
    if (!listCountries.empty()){
        return NULL;
    }

    for(int i=0;i<listCountries.size();i++){
        if(strcmp(nameCountry, listCountries[i]->getName())==0){
            return listCountries[i];
        }//if you need to dereference listCountries use (*listCountries)[index]
    }
    return NULL;
}

//only used when developping the map
void Continent::addCountry(Country* country){
    listCountries.push_back(country);
}