#ifndef Country_H
#define Country_H
//make sure your preprocessor variable is different from the class name!
#include <vector>

//class Country;
class Country{
    private:
        int troops;
        int numberOfOwnerPlayer;
        char *name;
        std::vector<Country*> neighborCountries;

    public:
        Country(char *nameOfCountry);
        int getTroops() const;//inline?
        int getOwner() const;//inline?
        char * getName() const;//inline?
        std::vector<Country*> getNeighborCountries() const;//good for attacking to know neighbors
        void setNeighborCountry(Country* nameCountry);
};

#endif