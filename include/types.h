#pragma once

struct RoomInstructions
{
	std::vector<short> roomTiles;
	sf::Vector2i mapSize;
	std::string file;
	sf::Vector2i mainEntrance;
	sf::Vector2i mainExit;
};

namespace MOVE {
	enum MoveDirections {
		UP,
		DOWN,
		LEFT,
		RIGHT,
		PAUSE
	};
}
enum MoveDirections { 
	UP, 
	DOWN, 
	LEFT, 
	RIGHT, 
	PAUSE
};
enum PathingState {
	wandering,
	seeking,
	returning
};

struct PlayerInstructions
{
	sf::Vector2f deathdimensions;
	sf::Vector2f deathmove;
	int total_iterations;
	std::string filename;
	sf::Vector2i dimensions;
	std::string disp_name;
	std::string portrait_file_name;
	int total_health;
	int damage_modifier;
};
struct EnemyInstructions
{
	std::vector<MoveDirections> path;
	std::string filename;
	std::string displayname;
	sf::Vector2i size;
	sf::Vector2i position;
	sf::Vector2f deathdimensions;
	sf::Vector2f deathmove;
	int total_iterations;
	int total_health;
	int damage_modifier;
};
namespace {
	std::string GENERIC_FONT = "SFPixelate.ttf";
}