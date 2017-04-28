#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include "player.h"
#include "enemy.h"
#include "collider.h"
#include "room.h"
#include "types.h"
#include "GUIs.h"


class Level
{
public:
	Level();
	Level(int);
	~Level();
	void addRoom(RoomInstructions, std::vector<EnemyInstructions>);
	int runLevel(sf::RenderWindow*);
	void adjustView();
	bool changeRoom();
	void updateMiniMap();
	void setUpEnemies(int);
	void updateCollider();
	void kill(int);

private:

	//rooms
	std::vector<RoomInstructions> allRooms;
	//std::vector<Room*> rooms;
	Room* currentRoom;
	int cur_level, totalRooms, roomIter;
	bool nextLevel;

	//enemies
	std::vector<std::vector<EnemyInstructions>> allEnemies;
	std::vector<Enemy*> enemies;
	int totalEnemies;


	//clocks
	sf::Clock clock, e_clock, roomChangeClock;


	//player
	Player player;
	Collider* m_collider;
	int collided_with;


	//views
	sf::View levelView;
	sf::View gameView;
	sf::View mm_view;
	sf::FloatRect viewCenter;

	//UI
	GameConsole m_console;
	PlayerStats m_pstats;
	MiniMap m_minimap;

	//sf::RectangleShape GameConsole;
	//sf::RectangleShape PlayerStats;
	sf::RectangleShape Tooltip;
	sf::RectangleShape Inventory;
	sf::RectangleShape Toolbar;
	//sf::RectangleShape Map;
	
};

