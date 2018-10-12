#ifndef MAP_LOADER
#define MAP_LOADER

class MapLoader;

#include "Map.h"
#include "MapLoader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <exception>

/**MapLoader loads up maps from .map files. Will not be instantiated, is only used for storing static methods.**/
class MapLoader {

public:
	//Utility
	/**
	   Read a .map file. Build the map described by the file and return a pointer to it. If map is invalid, ensure that an exception is thrown specifying why.
	   
	   A .map file can be invalid for any of the following reasons:
			1 - The file lacks the following sections: [Map], [Continents], and [Territories]. Note that these sections can be empty (if file describes an empty map, for example), but that the .map file must still have a header for each section.
			2 - A continent in the file does not have a name and value parameter.
			3 - A continent in the map file has an invalid value (a non integer value).
			4 - A country in the map file does not have a name, x coordinate, y coordinate, continent, and neighbor.
			5 - A country in the continent has an invalid x or y coordinate (not an integer value).
			6 - A country in the continent has an invalid neighbor (no country defined with the same name in the .map file).
			7 - Two countries defined in the map have the same name.
			8 - The file describes a map that is not fully connected (ie one in which some countries/continents are unreachable from others).
		
		Note: We need not worry about empty maps because those are technically valid. Additionally, we need not worry about countries belonging to multiple continents because a countries continent can only ever e defined once. Moreover, we need not check if a country's defined neighbors also define said country as their neighbor. The neighbor relationship will alwasy be made symmetrical (this is ensured by the addNeighbor method) regardless of the country definitions.
	**/
	static Map* readMapFile(std::string);

};

#endif