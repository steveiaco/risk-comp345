#include "Map.h"
#include "MapLoader.h"
#include <iostream>
#include <exception>
#include <string>

int main() {
	Map* validMap = new Map();
	validMap->getValidMap();

	std::cout<<"A valid map"<<std::endl;

	bool isCountries1 = validMap->isCountriesAssignedToContinent();
	std::cout<<"Are all countries assigned to a continent? "
		<<(isCountries1? true:false) <<std::endl;

	std::cout<<"All countries can only be assigned one continent and it cannot be changed"<<
		"once it has been set because there is no mutator method for the continent."<<std::endl;

	bool isMapConnected_ContinentConnected = validMap->validate();
	std::cout<<"Is the map a connected graph and does each continent a connected subgraph?"<<
	(isMapConnected_ContinentConnected? true:false)<<std::endl;

	Map* brokenMapOne = new Map();
	brokenMapOne->getBrokenMap();

	std::cout<<"A broken map"<<std::endl;

	isCountries1 = brokenMapOne->isCountriesAssignedToContinent();
	std::cout<<"Are all countries assigned to a continent? "
		<<(isCountries1? true:false) <<std::endl;

	std::cout<<"All countries can only be assigned one continent and it cannot be changed"<<
		"once it has been set because there is no mutator method for the continent."<<std::endl;

	isMapConnected_ContinentConnected = brokenMapOne->validate();
	std::cout<<"Is the map a connected graph and does each continent a connected subgraph?"<<
	(isMapConnected_ContinentConnected? true:false)<<std::endl;

	Map* brokenMapTwo = new Map();
	brokenMapTwo->getBrokenMap2();

	std::cout<<"A broken map"<<std::endl;

	isCountries1 = brokenMapTwo->isCountriesAssignedToContinent();
	std::cout<<"Are all countries assigned to a continent? "
		<<(isCountries1? true:false) <<std::endl;

	std::cout<<"All countries can only be assigned one continent and it cannot be changed"<<
		"once it has been set because there is no mutator method for the continent."<<std::endl;

	isMapConnected_ContinentConnected = brokenMapTwo->validate();
	std::cout<<"Is the map a connected graph and does each continent a connected subgraph?"<<
	(isMapConnected_ContinentConnected? true:false)<<std::endl;

	Map* brokenMapThree = new Map();
	brokenMapThree->getBrokenMap3();

	std::cout<<"A broken map"<<std::endl;

	isCountries1 = brokenMapThree->isCountriesAssignedToContinent();
	std::cout<<"Are all countries assigned to a continent? "
		<<(isCountries1? true:false) <<std::endl;

	std::cout<<"All countries can only be assigned one continent and it cannot be changed"<<
		"once it has been set because there is no mutator method for the continent."<<std::endl;

	isMapConnected_ContinentConnected = brokenMapThree->validate();
	std::cout<<"Is the map a connected graph and does each continent a connected subgraph?"<<
	(isMapConnected_ContinentConnected? true:false)<<std::endl;

}