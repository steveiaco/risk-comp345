#include "Map.h"
#include <string.h>
class Map{
    private:
        std::vector<Country*> countries;
        std::vector<Continent*> continents;

    public:
        Map();
        void addCountry(char* name);
        void addNeighbor(Country* country, Country* neighbor);//adds a neighbor to a country

        void addContinent(char* name);
        void addCountryToContinent(char* nameContinent, Country* country);
        std::vector<Continent*> getContinents() const;
        std::vector<Country*> getCountriesOwnedBy(short playerNumber);
        static Map* createDefaultMap();
};

Map::Map(){

}

void Map::addCountry(char* name){
    countries.push_back(new Country(name));//new operator creates pointer
}

void Map::addNeighbor(Country* country, Country* neighbor){
    country->setNeighborCountry(neighbor);
    neighbor->setNeighborCountry(country);
    //it is both from country POV and
    //from neighbor's POV that they are neighbors
}

void Map::addContinent(char* name){
    continents.push_back(new Continent(name));//new operator creates pointer
}

void Map::addCountryToContinent(char* nameContinent, Country* country){//return NULL if no result
    if(continents.empty()){
        return;
    }
    for(short i=0;i<continents.size();i++){
        if(strcmp(nameContinent, continents[i]->getContinentName())==0){
            continents[i]->addCountry(country);
            return;
        }
    }
}

std::vector<Continent*> Map::getContinents() const{
    return continents;
}

std::vector<Country*> Map::getCountriesOwnedBy(short playerNumber){
    
    std::vector<Country*> selectCountries;
    for(short i=0;i<countries.size();i++){
        if(countries[i]->getOwner()==playerNumber){
            selectCountries.push_back(countries[i]);
        }
    }
    return selectCountries;
}

Map* Map::createDefaultMap(){
    //basic test map
        //E
        //|
    //A---B---C
    //    |
    //    D

    Map* defaultMap = new Map();
    defaultMap->addCountry("A");
    defaultMap->addCountry("B");
    defaultMap->addCountry("C");
    defaultMap->addCountry("D");
    defaultMap->addCountry("E");
    
    //because we know the order in which they are pushed, we
    //know their indexes
    defaultMap->addNeighbor(defaultMap->countries[0], defaultMap->countries[1]);
    defaultMap->addNeighbor(defaultMap->countries[1], defaultMap->countries[2]);
    defaultMap->addNeighbor(defaultMap->countries[1], defaultMap->countries[3]);
    defaultMap->addNeighbor(defaultMap->countries[1], defaultMap->countries[4]);

    return defaultMap;
    

}