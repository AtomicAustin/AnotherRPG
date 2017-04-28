#pragma once

struct RoomInstructions
{
	std::vector<short> roomTiles;
	sf::Vector2i mapSize;
	std::string file;
	sf::Vector2i mainEntrance;
	sf::Vector2i mainExit;
};

enum MoveDirections { 
	UP, 
	DOWN, 
	LEFT, 
	RIGHT, 
	PAUSE
};

struct EnemyInstructions
{
	std::vector<MoveDirections> path;
	std::string filename = "enemies/InfectedBuffSkeleton(16x18).png";
	sf::Vector2i size = sf::Vector2i(16,18);
	sf::Vector2i position;
};
