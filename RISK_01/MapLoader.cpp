#include "Map.h"
#include "MapLoader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <exception>
using namespace std;

static Map* readMapFile(string mapName) {
	Map* map = new Map(mapName);
	ifstream inFile;
	vector<string> fields;

	try {
		//Check if named map exists
		inFile.open("C:\\Users\\sende\\source\\repos\\RISK_01\\" + mapName + "\\" + mapName + ".map");
		if (!inFile.good())
			throw std::invalid_argument(mapName + " does not exist.");

		//Start reading map file in line by line
		string line;
		//Reach the [Map] part of the file
		do {
			getline(inFile, line);
		} while (0 != line.compare("[Map]"));

		//Continue to [Continents] part of map file
		do {
			getline(inFile, line);
		} while (0 != line.compare("[Continents]"));
		getline(inFile, line);

		//Continue to [Territories] part of map file
		do {
			//Create continents
			string name;
			string value;
			stringstream ss(line);
			if (getline(ss, name, '=') && getline(ss, value)) {
				map->addContinent(new Continent(name, stoi(value)));
			}
			getline(inFile, line);
		} while (0 != line.compare("[Territories]"));
		getline(inFile, line);

		//Continue to end of map file
		vector<string> countries;
		do {
			//Read countries
			if(!line.empty())
				countries.push_back(line);
		} while (getline(inFile, line));

		//Create countries
		for (string s : countries) {
			stringstream ss(s);

			string name;
			string continent;
			getline(ss, name, ',');
			getline(ss, continent, ',');
			getline(ss, continent, ',');
			getline(ss, continent, ',');

			map->addCountry(new Country(name, map->getContinent(continent)));
		}

		//Link countries
		for (string s : countries) {
			stringstream ss(s);

			string name;
			string neighbor;

			getline(ss, name, ',');
			Country* country = map->getCountry(name);

			getline(ss, neighbor, ',');
			getline(ss, neighbor, ',');
			getline(ss, neighbor, ',');
			while(getline(ss, neighbor, ','))
				map->getCountry(name)->addNeighbor(map->getCountry(neighbor));
		}

		//Validate map
		if (!map->validate())
			throw invalid_argument(mapName + " is invalid!\nSome continents/countries are out of reach!");
		else
			return map;
	}
	//Catch io errors
	catch (std::ifstream::failure e) {
		cout << "Exception opening/reading/closing file\n";
	}
	return NULL;
}

int main() {
	Map* map = NULL;

	//Get map name
	string mapName;
	cout << "Enter name of map to load: ";
	cin >> mapName;
	cout << endl;

	//Get map
	while (map == NULL)
		try {
			map = readMapFile(mapName);
		}
		//Catch invalid maps
		catch (invalid_argument& e) {
			cout << e.what() << endl;
			cout << "Enter name of map to load: ";
			cin >> mapName;
			cout << endl;
		}

	//Display map
	map->display();

	cin >> mapName;
}