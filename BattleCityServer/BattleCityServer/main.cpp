import <iostream>;
#include "map.h"
//#include "playermovement.h"
import <vector>;

//TODO: add namespace game for every class


int main()
{
	std::cout << "Hello team!" << std::endl;
	
	game::Map myMap;
	std::cout << myMap;
	std::vector<Bomb> bombs;
	myMap.PlaceBombsOnWalls(bombs);

	//PlayerMovement player(5, 5);
	//player.DisplayBoard();

	

  

	return 0;
}