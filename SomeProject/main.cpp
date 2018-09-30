#include "Map.h"
#include <iostream>

int main(){
    Map* defaultMap = Map::createDefaultMap();

    std::vector<Country*> some = defaultMap->getCountriesOwnedBy(0);
    for(int i=0;i<some.size();i++){
        std::cout << some[i]->getName() <<std::endl;
        for(int j=0;j< some[i]->getNeighborCountries().size();j++){
            std::cout <<some[i]->getNeighborCountries()[j] << " ";
        }
        std::cout << std::endl;
    }
    

    return 0;
}