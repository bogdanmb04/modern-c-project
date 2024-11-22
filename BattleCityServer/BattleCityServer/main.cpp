import <iostream>;
#include "map.h"
//TODO: add namespace game for every class


int main()
{
	std::cout << "Hello team!" << std::endl;
	
	game::Map myMap;
	std::cout << myMap;
	std::vector<Bomb> bombs;
	myMap.PlaceBombsOnWalls(bombs);

	return 0;
}