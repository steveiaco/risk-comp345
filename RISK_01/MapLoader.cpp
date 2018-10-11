// Reads in map files and creates corresponding maps. Is utility class (members are static).

#include "Map.h"
#include "MapLoader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <exception>

//Creates a map object for the map with the passed name.
Map* MapLoader::readMapFile(std::string mapName) {
	//Create a blank map
	Map* map = new Map(mapName);
	std::ifstream inFile;
	bool allSections = false; //Keep track of whether or not the map file contains all four sections

	try { //Check for IO errors
		inFile.open("C:\\Users\\sende\\OneDrive\\Desktop\\Git Repos\\RISK\\local-project\\Debug\\" + mapName + "\\" + mapName + ".map");

		if (!inFile.good()) //If named map DNE, throw invalid argument exception. Explain why.
			throw std::invalid_argument(mapName + " does not exist.");

		//Read map file in line by line
		std::string line;
		//Reach the [Map] part of the file
		while (std::getline(inFile, line) && 0 != line.compare("[Map]")) {}
		//Continue to [Continents] part of map file
		while (std::getline(inFile, line) && 0 != line.compare("[Continents]")) {}

		//Continue to [Territories] part of map file
		while (std::getline(inFile, line) && 0 != line.compare("[Territories]")) { //Read continents
			std::string name, value;
			std::stringstream ss(line); //We will need to split each line here around the equals sign. We will process each line through a string stream to do so.
			if (std::getline(ss, name, '=') && std::getline(ss, value)) //Take only the lines with at least two arguments (the non-blank lines)
				map->addContinent(new Continent(name, std::stoi(value)));
		}

		std::vector<string> countries;
		//Continue to end of map file
		while (std::getline(inFile, line)) {
			//Read and store country construction parameters (we will need to do two passes over them: one for constructing them and one for linking them via neighbor parameter)
			if(!line.empty())
				countries.push_back(line);
			allSections = true;
		}

		if (!allSections)
			throw std::invalid_argument(mapName + " is invalid!\nSome sections do not exist!");

		//Construct countries
		for (std::string s : countries) {

			std::stringstream ss(s);

			//We will need each country's name and continent. The first two values assigned to continent are the x and y coordinates of the country, we are not keeping those values, they are replaced by the continent once we reach it.
			std::string name;
			std::string continent;
			std::getline(ss, name, ','); std::getline(ss, continent, ','); std::getline(ss, continent, ','); std::getline(ss, continent, ',');
			map->addCountry(new Country(name, map->getContinent(continent))); //tracked the bug to this line in code, in the new Country(name, continent) call

		}

		//Link countries
		for (std::string s : countries) {
			std::stringstream ss(s);
			//Get country by name
			std::string name;
			std::getline(ss, name, ',');
			Country* country = map->getCountry(name);
			//Get country neighbors and add them
			std::string neighbor;
			getline(ss, neighbor, ','); getline(ss, neighbor, ','); getline(ss, neighbor, ','); //Skip over x/y coords and continent name
			while(getline(ss, neighbor, ','))
				country->addNeighbor(map->getCountry(neighbor));
		}

		//Validate map
		if (!map->validate())
			throw std::invalid_argument(mapName + " is invalid!\nSome continents/countries are out of reach!");
		else
			return map;


	}
	//Catch io errors
	catch (std::ifstream::failure e) {
		std::cout << "Exception opening/reading/closing file\n";
	}
	return NULL;
}

int main() {
	cout << "=======================================\n";
	cout << "              RISK V0_01               \n";
	cout << "=======================================\n";

	//Keep trying to get map until a valid map is returned
	Map* map = NULL;
	while (map == NULL) {
		//Get map name
		std::string mapName;
		std::cout << "Enter name of map to load: ";
		std::getline(std::cin, mapName); std::cout << std::endl;
		try {
			map = MapLoader::readMapFile(mapName);
		}
		catch (std::invalid_argument& e) { //Catch invalid maps
			std::cout << e.what() << std::endl;
		}
	}

	//Display map
	map->display();
}