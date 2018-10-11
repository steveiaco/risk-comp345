#ifndef MAP_LOADER
#define MAP_LOADER

class MapLoader;

#include "Map.h"
#include <string>

class MapLoader {

public:
	static Map* readMapFile(std::string);

};

#endif