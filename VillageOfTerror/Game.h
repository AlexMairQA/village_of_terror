#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <exception>
#include <thread>
#include <chrono>


class Game
{

	 

	struct Position
	{
		int x = 0;
		int y = 1;
	};
public:
	
	static void PlayGame();
private:
	static void PlayerPosition(Position&, Position&);
	static void Move(std::string, Position&, Position&);
	static void VillageShop(Position&);
	static void FileReader(std::string);
};

