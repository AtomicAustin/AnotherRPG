#pragma once

#include <SFML\Graphics.hpp>
#include "types.h"

namespace PLAYERS
{
	namespace BuffNerd
	{
		sf::Vector2f deathdimensions = sf::Vector2f(27, 19);
		sf::Vector2f deathmove = sf::Vector2f(-4, -2);
		int total_iterations = 8;
		std::string filename = "player/BuffNerdwithdeath.png";
		sf::Vector2i dimensions = sf::Vector2i(16, 16);
		std::string disp_name = "Buff Nerd";
		std::string portrait_file_name = "UI/portraits/PortraitBuffNerd.png";
		int total_health = 25;
		int damage_modifier = 7.5;
	};
	namespace BuffBot
	{
		sf::Vector2f deathdimensions = sf::Vector2f(16, 21);
		sf::Vector2f deathmove = sf::Vector2f(0, -5);
		int total_iterations = 8;
		std::string filename = "player/BuffBotwithdeath.png";
		sf::Vector2i dimensions = sf::Vector2i(16, 16);
		std::string disp_name = "Buff Bot";
		std::string portrait_file_name = "UI/portraits/PortraitBuffBot.png";
		int total_health = 35;
		int damage_modifier = 6.5;
	};
	namespace BuffKnight
	{
		sf::Vector2f deathdimensions = sf::Vector2f(0,0);
		sf::Vector2f deathmove = sf::Vector2f(0,0);
		int total_iterations = 0;
		std::string filename = "player/BuffKnight18x16.png";
		sf::Vector2i dimensions = sf::Vector2i(18, 16);
		std::string disp_name = "Buff Knight";
		std::string portrait_file_name = "UI/portraits/PortraitBuffKnight.png";
		int total_health = 45;
		int damage_modifier = 5.5;
	};
}
namespace ENEMIES
{
	namespace InfectedBuffSkeleton
	{
		std::string displayName = "Infected Buff Skeleton";
		std::string filename = "enemies/InfectedBuffSkeletonwithDeath.png";
		sf::Vector2i size = sf::Vector2i(16, 18);
		sf::Vector2f deathdimensions = sf::Vector2f(16, 18);
		sf::Vector2f deathmove = sf::Vector2f(0, 0);
		int total_iterations = 7;
		int total_health = 10;
		int damage_modifier = 5;
	};
	
	namespace SpaceGhoul
	{
		std::string displayName = "Space Ghoul";
		std::string filename = "enemies/SpaceGhoultest16x16.png";
		sf::Vector2i size = sf::Vector2i(16, 16);
		sf::Vector2f deathdimensions = sf::Vector2f(0,0);
		sf::Vector2f deathmove = sf::Vector2f(0, 0);
		int total_iterations = 0;
		int total_health = 15;
		int damage_modifier = 5;
	}
}
namespace ROOM1
{
	std::vector<short> room =
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

	std::string filename = "tiles/fullbettertiles.png";
	sf::Vector2i mainEntrance = sf::Vector2i(3, 3);
	sf::Vector2i mainExit = sf::Vector2i(2, 15);
	sf::Vector2i mapSize = sf::Vector2i(16, 16);

	namespace data_IBS1
	{
		sf::Vector2i position = sf::Vector2i(14, 3);
		std::vector<MoveDirections> new_path =
		{
			DOWN, DOWN, DOWN, DOWN, DOWN, DOWN, DOWN, DOWN,
			LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, LEFT,
			RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT,
			UP, UP, UP, UP, UP, UP, UP, UP,
		};
	};

	namespace data_IBS2
	{
		sf::Vector2i position = sf::Vector2i(3, 11);
		std::vector<MoveDirections> new_path =
		{
			RIGHT, RIGHT, RIGHT, RIGHT, RIGHT,
			UP, DOWN, DOWN, UP,
			LEFT, LEFT, LEFT, LEFT, LEFT
		};
	};

	namespace data_IBS3
	{
		sf::Vector2i position = sf::Vector2i(3, 7);
		std::vector<MoveDirections> new_path =
		{
			UP, UP, DOWN, DOWN, PAUSE
		};
	};
}

namespace ROOM2
{
	std::vector<short> room =
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

	std::string filename = "tiles/fullbettertiles.png";
	sf::Vector2i mainEntrance = sf::Vector2i(3, 5);
	sf::Vector2i mainExit = sf::Vector2i(15, 3);
	sf::Vector2i mapSize = sf::Vector2i(32, 8);
	
	namespace data_SpaceGhoul1
	{
			
		sf::Vector2i position = sf::Vector2i(9, 3);
		std::vector<MoveDirections> new_path =
		{
			RIGHT, RIGHT, RIGHT,
			DOWN, DOWN, DOWN,
			LEFT, LEFT, LEFT,
			UP, UP, UP
		};
	};
		
	namespace data_SpaceGhoul2
	{
		sf::Vector2i position = sf::Vector2i(16, 3);
		std::vector<MoveDirections> new_path =
		{
			RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT,
			DOWN, DOWN, DOWN,
			RIGHT, RIGHT,
			UP, UP, UP,
			LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, LEFT
		};
	};

}

