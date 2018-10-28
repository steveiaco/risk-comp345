#include "Map.h"
#include "MapLoader.h"
#include <iostream>
#include <exception>
#include <string>
int main() {
	std::cout << "=======================================\n";
	std::cout << "            RISK TEST PART 1           \n";
	std::cout << "=======================================\n";

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
			std::cout << mapName + ".map does not define a valid map!\n";
			std::cout << e.what() << std::endl;
		}
	}

	//Display map
	map->display();
}
