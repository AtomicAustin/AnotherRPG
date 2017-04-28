#pragma once

#include<SFML\Graphics.hpp>
#include <iostream>

class Collider
{
public:
	Collider();
	Collider(std::vector<sf::FloatRect>, std::vector<sf::FloatRect>, std::vector<sf::FloatRect>);
	void replaceTiles(std::vector<sf::FloatRect>, std::vector<sf::FloatRect>, std::vector<sf::FloatRect>);
	void addEnemy(sf::FloatRect);
	void updateEnemy(sf::FloatRect, int);
	void removeEnemy(int);
	void clearEnemies();
	int checkCollision(sf::Vector2f);
	void updatePlayer(sf::FloatRect);
	bool checkPlayerCollision(sf::Vector2f);
	int getPcollidedwith();
	~Collider();

private:
	sf::FloatRect l_player;
	int p_collidedwith;

	std::vector<sf::FloatRect> l_walls;
	std::vector<sf::FloatRect> l_entrances;
	std::vector<sf::FloatRect> l_exits;
	std::vector<sf::FloatRect> l_enemies;
};

