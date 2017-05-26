#include <SFML/Graphics.hpp>
#include "level.h"
#include "collider.h"
#include "player.h"
#include "gameobject.h"
#include "enemy.h"
#include "data.h"

PlayerInstructions pickPlayer(sf::RenderWindow* n_window);

int main()
{
	sf::Clock setUpClock;

	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1280, 768), "Just Another RPG");
	window->setFramerateLimit(30);

	std::cout << window->getSize().x << ", " << window->getSize().y << std::endl;
	
	Level level1(1);

	RoomInstructions n_room1;
	n_room1.file = ROOM1::filename;
	n_room1.mainEntrance = ROOM1::mainEntrance;
	n_room1.mainExit = ROOM1::mainExit;
	n_room1.mapSize = ROOM1::mapSize;
	n_room1.roomTiles = ROOM1::room;

	std::vector<EnemyInstructions> n_enemies1;
	EnemyInstructions n_enemy1;
	n_enemy1.displayname = ENEMIES::InfectedBuffSkeleton::displayName;
	n_enemy1.filename = ENEMIES::InfectedBuffSkeleton::filename;
	n_enemy1.size = ENEMIES::InfectedBuffSkeleton::size;
	n_enemy1.deathdimensions = ENEMIES::InfectedBuffSkeleton::deathdimensions;
	n_enemy1.deathmove = ENEMIES::InfectedBuffSkeleton::deathmove;
	n_enemy1.total_iterations = ENEMIES::InfectedBuffSkeleton::total_iterations;
	n_enemy1.total_health = ENEMIES::InfectedBuffSkeleton::total_health;
	n_enemy1.damage_modifier = ENEMIES::InfectedBuffSkeleton::damage_modifier;
	n_enemy1.path = ROOM1::data_IBS1::new_path;
	n_enemy1.position = ROOM1::data_IBS1::position;
	n_enemies1.push_back(n_enemy1);

	EnemyInstructions n_enemy2;
	n_enemy2.displayname = ENEMIES::InfectedBuffSkeleton::displayName;
	n_enemy2.filename = ENEMIES::InfectedBuffSkeleton::filename;
	n_enemy2.size = ENEMIES::InfectedBuffSkeleton::size;
	n_enemy2.deathdimensions = ENEMIES::InfectedBuffSkeleton::deathdimensions;
	n_enemy2.deathmove = ENEMIES::InfectedBuffSkeleton::deathmove;
	n_enemy2.total_iterations = ENEMIES::InfectedBuffSkeleton::total_iterations;
	n_enemy2.total_health = ENEMIES::InfectedBuffSkeleton::total_health;
	n_enemy2.damage_modifier = ENEMIES::InfectedBuffSkeleton::damage_modifier;
	n_enemy2.path = ROOM1::data_IBS2::new_path;
	n_enemy2.position = ROOM1::data_IBS2::position;
	n_enemies1.push_back(n_enemy2);

	EnemyInstructions n_enemy3;
	n_enemy3.displayname = ENEMIES::InfectedBuffSkeleton::displayName;
	n_enemy3.filename = ENEMIES::InfectedBuffSkeleton::filename;
	n_enemy3.size = ENEMIES::InfectedBuffSkeleton::size;
	n_enemy3.deathdimensions = ENEMIES::InfectedBuffSkeleton::deathdimensions;
	n_enemy3.deathmove = ENEMIES::InfectedBuffSkeleton::deathmove;
	n_enemy3.total_iterations = ENEMIES::InfectedBuffSkeleton::total_iterations;
	n_enemy3.total_health = ENEMIES::InfectedBuffSkeleton::total_health;
	n_enemy3.damage_modifier = ENEMIES::InfectedBuffSkeleton::damage_modifier;
	n_enemy3.path = ROOM1::data_IBS3::new_path;
	n_enemy3.position = ROOM1::data_IBS3::position;
	n_enemies1.push_back(n_enemy3);


	level1.addRoom(n_room1, n_enemies1);
	
	RoomInstructions n_room2;
	n_room2.file = ROOM2::filename;
	n_room2.mainEntrance = ROOM2::mainEntrance;
	n_room2.mainExit = ROOM2::mainExit;
	n_room2.mapSize = ROOM2::mapSize;
	n_room2.roomTiles = ROOM2::room;
	
	std::vector<EnemyInstructions> n_enemies2;
	EnemyInstructions n_enemy4;
	n_enemy4.displayname = ENEMIES::SpaceGhoul::displayName;
	n_enemy4.filename = ENEMIES::SpaceGhoul::filename;
	n_enemy4.size = ENEMIES::SpaceGhoul::size;
	n_enemy4.deathdimensions = ENEMIES::SpaceGhoul::deathdimensions;
	n_enemy4.deathmove = ENEMIES::SpaceGhoul::deathmove;
	n_enemy4.total_iterations = ENEMIES::SpaceGhoul::total_iterations;
	n_enemy4.total_health = ENEMIES::SpaceGhoul::total_health;
	n_enemy4.damage_modifier = ENEMIES::SpaceGhoul::damage_modifier;
	n_enemy4.path = ROOM2::data_SpaceGhoul1::new_path;
	n_enemy4.position = ROOM2::data_SpaceGhoul1::position;
	n_enemies2.push_back(n_enemy4);

	EnemyInstructions n_enemy5;
	
	n_enemy5.displayname = ENEMIES::SpaceGhoul::displayName;
	n_enemy5.filename = ENEMIES::SpaceGhoul::filename;
	n_enemy5.size = ENEMIES::SpaceGhoul::size;
	n_enemy5.deathdimensions = ENEMIES::SpaceGhoul::deathdimensions;
	n_enemy5.deathmove = ENEMIES::SpaceGhoul::deathmove;
	n_enemy5.total_iterations = ENEMIES::SpaceGhoul::total_iterations;
	n_enemy5.total_health = ENEMIES::SpaceGhoul::total_health;
	n_enemy5.damage_modifier = ENEMIES::SpaceGhoul::damage_modifier;
	n_enemy5.path = ROOM2::data_SpaceGhoul2::new_path;
	n_enemy5.position = ROOM2::data_SpaceGhoul2::position;

	n_enemies2.push_back(n_enemy5);

	level1.addRoom(n_room2, n_enemies2);

	bool runGame = true;

	std::cout << setUpClock.getElapsedTime().asSeconds() << std::endl;

	while (runGame)
	{

		int next_level = level1.runLevel(window, pickPlayer(window));
		
		switch(next_level)
		{
			case 1: {/*run next level*/; break; }
			case 0: {level1.resetLevel(1); continue; } //player died
			case -1: {runGame = false; break; } //quit game
		}
	}

	return 0;
}
PlayerInstructions pickPlayer(sf::RenderWindow* n_window)
{
	n_window->setView(n_window->getDefaultView());
	sf::Vector2f windowSize = sf::Vector2f(n_window->getSize());
	sf::RectangleShape background(windowSize);
	background.setFillColor(sf::Color::Black);
	background.setPosition(0, 0);

	int total_portraits = 3;
	sf::Texture portrait_Texture;
	sf::Texture border_Texture;
	portrait_Texture.loadFromFile("UI/portraits/FullPortrait.png");
	border_Texture.loadFromFile("UI/portraits/border.png");
	sf::Sprite portraits;
	sf::Sprite border;
	portraits.setTexture(portrait_Texture);
	border.setTexture(border_Texture);

	portraits.setPosition(windowSize.x * .4, windowSize.y * .2);
	portraits.setScale(10, 10);

	border.setPosition(portraits.getGlobalBounds().left, portraits.getGlobalBounds().top);
	border.setScale(portraits.getScale());

	int yDimen = portraits.getGlobalBounds().height / total_portraits + 1;
	int xDimen = portraits.getGlobalBounds().left;

	int curPortrait = 1;
	bool run = true;

	while (n_window->isOpen())
	{
		sf::Event event;
		while (n_window->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				n_window->close();
			
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::W)
				{
					//move iter up
					curPortrait--;
				}
				else if (event.key.code == sf::Keyboard::S)
				{
					//move iter down
					
					curPortrait++;
				}
				else if (event.key.code == sf::Keyboard::Return)
				{
					run = false;
				}
			}

			if (curPortrait > total_portraits) {
				curPortrait = 1;
			}
			if (curPortrait < 1) {
				curPortrait = total_portraits;
			}


			border.setPosition(xDimen, portraits.getGlobalBounds().top + ((curPortrait - 1) * (yDimen)));
		}

		if (!run) {
			break;
		}


		n_window->clear();

		n_window->draw(background);
		n_window->draw(portraits);
		n_window->draw(border);

		n_window->display();
	}

	PlayerInstructions player;

	switch (curPortrait)
	{
	case 1: 
	{ 
		player.deathdimensions = PLAYERS::BuffNerd::deathdimensions;
		player.deathmove = PLAYERS::BuffNerd::deathmove;
		player.total_iterations = PLAYERS::BuffNerd::total_iterations;
		player.filename = PLAYERS::BuffNerd::filename;
		player.dimensions = PLAYERS::BuffNerd::dimensions;
		player.disp_name = PLAYERS::BuffNerd::disp_name;
		player.portrait_file_name = PLAYERS::BuffNerd::portrait_file_name;
		player.total_health = PLAYERS::BuffNerd::total_health;
		player.damage_modifier = PLAYERS::BuffNerd::damage_modifier;
		
		break;
	}
	case 2: 
	{ 
		player.deathdimensions = PLAYERS::BuffBot::deathdimensions;
		player.deathmove = PLAYERS::BuffBot::deathmove;
		player.total_iterations = PLAYERS::BuffBot::total_iterations;
		player.filename = PLAYERS::BuffBot::filename;
		player.dimensions = PLAYERS::BuffBot::dimensions;
		player.disp_name = PLAYERS::BuffBot::disp_name;
		player.portrait_file_name = PLAYERS::BuffBot::portrait_file_name;
		player.total_health = PLAYERS::BuffBot::total_health;
		player.damage_modifier = PLAYERS::BuffBot::damage_modifier;

		break;
	}
	case 3:
	{
		player.deathdimensions = PLAYERS::BuffKnight::deathdimensions;
		player.deathmove = PLAYERS::BuffKnight::deathmove;
		player.total_iterations = PLAYERS::BuffKnight::total_iterations;
		player.filename = PLAYERS::BuffKnight::filename;
		player.dimensions = PLAYERS::BuffKnight::dimensions;
		player.disp_name = PLAYERS::BuffKnight::disp_name;
		player.portrait_file_name = PLAYERS::BuffKnight::portrait_file_name;
		player.total_health = PLAYERS::BuffKnight::total_health;
		player.damage_modifier = PLAYERS::BuffKnight::damage_modifier;

		break;
	}
	}

	return player;
}