#include <vector>
class Country{
    private:
        int troops;
        int numberOfOwnerPlayer;
        char *name;
        std::vector<Country*> neighborCountries;

    public:
        Country(char *nameOfCountry);
        int getTroops() const{ return troops;};//inline?
        int getOwner() const{ return numberOfOwnerPlayer;};//inline?
        char * getName() const{ return name;};//inline?
        std::vector<Country*> getNeighborCountries() const;//good for attacking to know neighbors
        void setNeighborCountry(Country* nameCountry);
};
