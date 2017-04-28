#include <SFML/Graphics.hpp>
#include "level.h"
#include "collider.h"
#include "player.h"
#include "gameobject.h"
#include "enemy.h"

int main()
{
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1280, 768), "Just Another RPG");
	window->setFramerateLimit(30);

	std::cout << window->getSize().x << ", " << window->getSize().y << std::endl;
	
	Level level1(1);

	std::vector<short> level1room1 =
	{
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,
		1,0,2,0,1,0,0,0,0,1,0,0,0,0,0,1,
		1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,
		1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,1,0,0,1,0,0,0,1,1,0,0,1,
		1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,
		1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,1,1,1,1,1,1,1,1,1,0,0,0,1,
		1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,
		1,3,0,1,0,0,0,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	};

	RoomInstructions n_room1;
	n_room1.file = "tiles/fullbettertiles.png";
	n_room1.mainEntrance = sf::Vector2i(3, 3);
	n_room1.mainExit = sf::Vector2i(2, 15);
	n_room1.mapSize = sf::Vector2i(16, 16);
	n_room1.roomTiles = level1room1;

	std::vector<EnemyInstructions> n_enemies1;
	EnemyInstructions n_enemy1;
	n_enemy1.position = sf::Vector2i(14, 3);
	std::vector<MoveDirections> new_path1 =
	{
		DOWN, DOWN, DOWN, DOWN, DOWN, DOWN, DOWN, DOWN,
		LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, LEFT,
		RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT,
		UP, UP, UP, UP, UP, UP, UP, UP,
	};
	n_enemy1.path = new_path1;
	n_enemies1.push_back(n_enemy1);

	EnemyInstructions n_enemy2;
	n_enemy2.position = sf::Vector2i(3, 11);
	std::vector<MoveDirections> new_path2 =
	{
		RIGHT, RIGHT, RIGHT, RIGHT, RIGHT,
		UP, DOWN, DOWN, UP,
		LEFT, LEFT, LEFT, LEFT, LEFT
	};
	n_enemy2.path = new_path2;
	n_enemies1.push_back(n_enemy2);

	EnemyInstructions n_enemy5;
	n_enemy5.position = sf::Vector2i(3, 7);
	std::vector<MoveDirections> new_path5 = 
	{
		UP, UP, DOWN, DOWN
	};
	n_enemy5.path = new_path5;
	n_enemies1.push_back(n_enemy5);


	level1.addRoom(n_room1, n_enemies1);
	
	std::vector<short> level1room2 =
	{
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,
		1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,3,1,
		1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,
		1,0,2,0,0,0,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,

	};
	
	RoomInstructions n_room2;
	n_room2.file = "tiles/fullbettertiles.png";
	n_room2.mainEntrance = sf::Vector2i(3, 5);
	n_room1.mainExit = sf::Vector2i(15, 3);
	n_room2.mapSize = sf::Vector2i(32, 8);
	n_room2.roomTiles = level1room2;
	
	std::vector<EnemyInstructions> n_enemies2;
	EnemyInstructions n_enemy3;
	n_enemy3.position = sf::Vector2i(9, 3);
	std::vector<MoveDirections> new_path3 =
	{
		RIGHT, RIGHT, RIGHT,
		DOWN, DOWN, DOWN,
		LEFT, LEFT, LEFT,
		UP, UP, UP
	};
	n_enemy3.path = new_path3;
	n_enemies2.push_back(n_enemy3);

	EnemyInstructions n_enemy4;
	n_enemy4.position = sf::Vector2i(16, 3);
	std::vector<MoveDirections> new_path4 =
	{
		RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT,
		DOWN, DOWN, DOWN,
		RIGHT, RIGHT,
		UP, UP, UP,
		LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, LEFT
	};
	n_enemy4.path = new_path4;
	n_enemies2.push_back(n_enemy4);

	level1.addRoom(n_room2, n_enemies2);

	int gotoNextLevel = level1.runLevel(window);

	if (gotoNextLevel == 1) {
		//run level2
	}
	else {
		//display shutting down or something
	}
	

	return 0;
}