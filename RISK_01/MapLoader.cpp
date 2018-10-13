#include "MapLoader.h"

/**
	Read a .map file. Build the map described by the file and return a pointer to it. If map is invalid, ensure that an exception is thrown specifying why.

	A .map file can be invalid for any of the following reasons:
		1 - The file lacks the following sections: [Map], [Continents], and/or [Territories]. Note that these sections can be empty (if file describes an empty map, for example), but that the .map file must still have a header for each section.
		2 - A continent in the file does not have a name and value parameter.
		3 - A continent in the map file has an invalid value (a non integer value).
		4 - A country in the map file does not have a name, x coordinate, y coordinate, continent, and neighbor.
		5 - A country in the continent has an invalid x or y coordinate (not an integer value). We will not consider this aspect for now because we are not using the coordinates.
		6 - A country in the continent has an invalid neighbor (no country defined with the same name in the .map file).
		7 - Two countries defined in the map have the same name.
		8 - The file describes a map that is not fully connected (ie one in which some countries/continents are unreachable from others).
		9 - The named file does not exist.

	Note: We need not worry about empty maps because those are technically valid. Additionally, we need not worry about countries belonging to multiple continents because a countries continent can only ever e defined once. Moreover, we need not check if a country's defined neighbors also define said country as their neighbor. The neighbor relationship will alwasy be made symmetrical (this is ensured by the addNeighbor method) regardless of the country definitions.
**/
Map* MapLoader::readMapFile(std::string mapName) {
	//Create a blank map
	Map* map = new Map(mapName);
	std::ifstream inFile;
	bool allSections = false; //Keep track of whether or not the map file contains all three sections ([Map], [Continents], and [Territories])

	try { //Check for IO errors
		inFile.open("C:\\Users\\sende\\OneDrive\\Desktop\\Git Repos\\RISK\\local-project\\Debug\\" + mapName + "\\" + mapName + ".map");

		if (!inFile.good()) //If named map DNE, throw invalid argument exception. Explain why.
			throw std::invalid_argument(mapName + " does not exist.");

		//Read map file in line by line
		std::string line;
		//Reach the [Map] part of the file
		while (std::getline(inFile, line) && 0 != line.compare("[Map]")) {}
		//Continue to [Continents] part of map file (We will do nothing with [Map] section for now)
		while (std::getline(inFile, line) && 0 != line.compare("[Continents]")) {}

		//Continue to [Territories] part of map file
		while (std::getline(inFile, line) && 0 != line.compare("[Territories]")) { //Read continents
			std::string name, value;
			std::stringstream ss(line); //We will need to split each line here around the equals sign. We will process each line through a string stream to do so.
			if (std::getline(ss, name, '=') && std::getline(ss, value)) //Take only the lines with two arguments
				try {
					map->addContinent(new Continent(name, std::stoi(value)));
				}
				catch (std::invalid_argument& e) { //If the value passed to std::stoi is not  valid integer, an invalid argument exception will be thrown, catch that exception and explain it.
					throw std::invalid_argument(value + " is not a valid value for " + name + ".");
				}
			else if (line.compare("") != 0) //If line does not have two arguments seperated by an equals sign, check if it is empty. If it is not empty, it is an invalid definition for a continent.
				throw std::invalid_argument(line + " is not a valid continent definition.");
		}

		std::vector<std::string> countries;
		//Continue to end of map file
		while (std::getline(inFile, line)) {
			//Read and store country construction parameters (we will need to do two passes over them: one for constructing them and one for linking them via neighbor parameter)
			if(!line.empty())
				countries.push_back(line);
			allSections = true; //Note that the program can not reach this loop if it has exhausted all lines trying to find the headers for [Map], [Continents], and [Territories] in the previous loops because the condition for this loop is that the stream has not reached the end of the file. Thus, if the program reaches this line, we can rest assured that the file contains all three required sections.
		}

		if (!allSections)
			throw std::invalid_argument("Some sections are missing.");

		//Construct countries
		for (std::string line : countries) {

			std::stringstream ss(line);

			//We will need each country's name and continent. The first two values assigned to continent are the x and y coordinates of the country, we are not keeping those values, they are replaced by the name of the continent once we reach it.
			std::string name;
			std::string continent;
			if (std::getline(ss, name, ',') && std::getline(ss, continent, ',') && std::getline(ss, continent, ',') && std::getline(ss, continent, ','))
				map->addCountry(new Country(name, map->getContinent(continent))); //tracked the bug to this line in code, in the new Country(name, continent) call
			else if (line.compare("") != 0) //If line does not have four arguments seperated by commas, check if it is empty. If it is not empty, it is an invalid definition for a country.
				throw std::invalid_argument(line + " is not a valid country definition.");
		}

		//Link countries
		for (std::string line : countries) {
			std::stringstream ss(line);
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
			throw std::invalid_argument("Some continents/countries are out of reach.");
		else
			return map;


	}
	//Catch io errors
	catch (std::ifstream::failure e) {
		std::cout << "Exception opening/reading/closing file.\n";
	}
	return NULL;
}