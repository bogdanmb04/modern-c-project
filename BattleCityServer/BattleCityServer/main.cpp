import <iostream>;
import "map.h";
//TODO: add namespace game for every class


int main()
{
	std::cout << "Hello team!" << std::endl;
	
	//just for verification
	game::Map myMap;
	std::cout << myMap;
	std::vector<Bomb> bombs;
	//TODO: need to change logic add a constant for how many bombs to be planted and this 
	//limitation in the constructor of the map
	myMap.PlaceBombsOnWalls(bombs);

	return 0;
}