#ifndef MAP_LOADER
#define MAP_LOADER

class MapLoader;

#include "Map.h"
#include <string>
using namespace std;

class MapLoader {

public:
	static Map* readMapFile(string);

};

#endif