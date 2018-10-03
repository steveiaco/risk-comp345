#ifndef Map_H
#define Map_H

#include "Continent.h"
#include <vector>

class Map{
    private:
        std::vector<Country*> countries;
        std::vector<Continent*> continents;

    public:
        Map();
        void addCountry(char* name);
        void addNeighbor(Country* country, Country* neighbor);
        void addContinent(char* name);
        void addCountryToContinent(char* nameContinent, Country* country);
        std::vector<Continent*> getContinents() const;
        std::vector<Country*> getCountriesOwnedBy(short playerNumber);
        std::vector<Country*> getCountries();
        static Map* createDefaultMap();

};

#endif