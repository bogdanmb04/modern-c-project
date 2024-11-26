import <iostream>;
#include "map.h"
//#include "playermovement.h"
import <vector>;
#include "../Logging/logging.h"
#include <fstream>

#include "database.h"
#include "routing.h"
#include <chrono>
#include <thread>
#include <iomanip>

//TODO: add namespace game for every class


int main()
{
	server::GameDatabase gameDatabase;
	gameDatabase.Initialize();
	//TODO: optimize this code
	auto start_time = std::chrono::high_resolution_clock::now();
	for (int i = 1; i < 30; i++) {
		auto current_time = std::chrono::high_resolution_clock::now();
		std::chrono::duration<int> elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time);

		int hours = elapsed_seconds.count() / 3600;
		int minutes = (elapsed_seconds.count() % 3600) / 60;
		int seconds = elapsed_seconds.count() % 60;

		std::cout << "\rTime: "
			<< std::setfill('0') << std::setw(2) << hours << ":"
			<< std::setfill('0') << std::setw(2) << minutes << ":"
			<< std::setfill('0') << std::setw(2) << seconds
			<< std::flush;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	std::ofstream of("syslog.log", std::ios::app);
	Logger logger(of);
	logger.Log("Started Application...", Logger::Level::Info);

	/*server::Database db = server::CreateDatabase("test.db");  
	server::GameDatabase gameDb(db);  
	http::Routing routing;
	routing.Run(gameDb);*/

	std::cout << "Hello team!" << std::endl;
	
	game::Map myMap;
	std::vector<Bomb> bombs;
	myMap.PlaceBombsOnWalls(bombs);
	myMap.PlacePlayer();
	std::cout << myMap;


	//PlayerMovement player(5, 5);
	//player.DisplayBoard();

	

  

	return 0;
}