#ifndef Continent_H
#define Continent_H

#include "Country.h"
#include <vector>

class Continent{
    private:
        std::vector<Country*> listCountries;
        char *name;

    public:
        Continent(char *nameContinent);

        std::vector<Country*> getCountries() const;
        char* getContinentName() const;

        Country* getCountry(char *nameCountry);
        void addCountry(Country* country);
};

#endif