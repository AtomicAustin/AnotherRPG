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
	int runLevel(sf::RenderWindow*, PlayerInstructions);
	void update();
	void updatePlayer();
	void updateEnemies();
	void updateWindow();
	void adjustView();
	int changeRoom(int);
	void updateMiniMap();
	void setUpEnemies(int);
	void updateCollider();
	void kill(int);
	void killPlayer();
	void resetLevel(int);

private:

	sf::RenderWindow* g_window;
	sf::RectangleShape gameOver;

	//rooms
	std::vector<RoomInstructions> allRooms;
	//std::vector<Room*> rooms;
	Room* currentRoom;
	int cur_level, totalRooms, roomIter;
	int main_ret;

	//enemies
	std::vector<std::vector<EnemyInstructions>> allEnemies;
	std::vector<Enemy*> enemies;
	int totalEnemies;
	int to_kill;
	int to_hit;

	//clocks
	sf::Clock e_clock, kill_clock, roomChangeClock;


	//player
	Player player;
	Collider* m_collider;
	int move_dir;
	int attack;


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

