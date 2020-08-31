#include "stdafx.h"
#include "Game.h"
enum class Things
{
	FARM,
	FOREST,
	ROAD,
	HOUSE,
	SHOP,
	POLICE_STATION,
	ALLEY
};
enum class Direction
{
	NORTH,
	SOUTH,
	EAST,
	WEST
};
typedef Things T;
bool wallet = true;
std::vector<std::vector<Things>> village=
{
{T::FOREST, T::FOREST, T::FOREST, T::FOREST,T::FOREST},
{T::FARM, T::FARM, T::FOREST, T::FARM, T::FOREST},
{T::FOREST, T::HOUSE, T::FOREST, T::HOUSE, T::FOREST},
{T::ROAD, T::ROAD , T::ROAD , T::ROAD , T::ROAD },
{T::HOUSE, T::ROAD, T::HOUSE, T::ROAD, T::HOUSE},
{T::ALLEY, T::ROAD, T::ALLEY, T::HOUSE, T::ALLEY },
{T::HOUSE, T::ROAD, T::SHOP, T::ALLEY, T::ALLEY},
{T::ROAD, T::ROAD, T::ROAD,T::ROAD, T::ROAD},
{T::FOREST, T::ROAD, T::POLICE_STATION, T::ALLEY, T::ALLEY}

};

void Game::PlayGame()
{
	Position p, lastp;
	std::string direction;
	FileReader("title");
	std::this_thread::sleep_for(std::chrono::seconds(2));
	FileReader("intro");
	try
	{
		while (true)
		{
			PlayerPosition(p, lastp);
			FileReader("which_way");
			getline(std::cin, direction);
			lastp = p;
			Move(direction, p, lastp);
		}
	}
	catch (std::exception e)
	{
		std::cout << "Game Over" << std::endl;
	}
}

void Game::PlayerPosition(Position &p, Position &lastp)
{
	
	switch (village[p.x][p.y])
	{
	case T::FARM:
		if (village[lastp.x][lastp.y] != T::FARM)
		{
			FileReader("warning");
		}
		else
		{
			FileReader("tresspass");
			throw std::exception();
		}
		break;
	case T::ROAD:
		std::cout << "Road" << std::endl;
		break;
	case T::ALLEY:
		if (village[lastp.x][lastp.y] != T::ALLEY)
		{
			FileReader("alley");
		}
		else
		{
			FileReader("mugging");
			wallet = false;
		}
		break;
	case T::SHOP:
		VillageShop(p);
		break;
	case T::FOREST:
		if (village[lastp.x][lastp.y] != T::FOREST)
		{
			std::cout << "You have entered the forest" << std::endl;
		}
		else
		{
			std::cout << "forest" << std::endl;
		}
		break;
	case T::POLICE_STATION:
		FileReader("police_station");
		break;
	default:
		break;
	}

}
void Game::Move(std::string input, Position &p, Position &lastp)
{
	Direction direction;
	if (input == "north" || input=="n")
	{
		direction = Direction::NORTH;
	}
	else if (input == "south" || input == "s")
	{
		direction = Direction::SOUTH;
	}
	else if (input == "east" || input == "e")
	{
		direction = Direction::EAST;
	}
	else if (input == "west" || input == "w")
	{
		direction = Direction::WEST;
	}

	else
	{
		std::cout <<input;
		FileReader("valid_directions");
	}
	switch (direction)
	{
	case Direction::NORTH:
		if (p.x+1 == village.size()) {
			p.x = 0;
		}
		
		else if (village[p.x + 1][p.y]==T::HOUSE)
		{
			FileReader("house");
			p.x = 8;
			p.y = 2;
		}
		else
		{
			p.x++;
		}
		break;
	case Direction::SOUTH:
		if (p.x-1<0) {
			p.x = village.size()-1;
		}
		
		else if (village[p.x - 1][p.y] == T::HOUSE)
		{
			FileReader("house");
			p.x = 8;
			p.y = 2;
		}
		else
		{
			p.x--;
		}
		break;
	case Direction::EAST:
		if (p.y + 1 == village[p.x].size()) {
			p.y = 0;
		}

		else if (village[p.x][p.y + 1] == T::HOUSE)
		{
			FileReader("house");
			p.x = 8;
			p.y = 2;
		}
		else
		{
			p.y++;
		}
		break;
	case Direction::WEST:
		if (p.y - 1<0) {
			p.y = 0;
		}

		else if (village[p.x][p.y - 1] == T::HOUSE)
		{
			FileReader("house");
			p.x = 8;
			p.y = 2;
		}
		else
		{
			p.y--;
		}
		break;
	default:
		
		break;
	}

}

void Game::VillageShop(Position &p)
{
	std::string item;
	FileReader("village_shop");
	getline(std::cin.ignore(), item);
	if (!wallet)
	{
		std::cout << "You tried to steal " + item + "!";
	}
	else if (item == "coffee" || item == "cigarettes")
	{
		std::cout << "Here is your " + item + ". Enjoy your visit" << std::endl;
	}
	else
	{
		std::cout << "Sorry, we don\'t have " + item + ".";
	}
}

void Game::FileReader(std::string filename)
{
	std::string filepath = "../text/" + filename + ".txt";
	std::ifstream file(filepath);
	std::string line;
	while (std::getline(file, line))
	{
		std::cout << line << std::endl;
	}
}