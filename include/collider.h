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
	bool checkCollision(sf::Vector2f);
	bool checkLevelCollision(sf::Vector2f);
	bool checkWallCollision(sf::Vector2f);
	bool checkEnemyCollision(sf::Vector2f);
	bool checkEnemyHit(sf::Vector2f);
	void updatePlayer(sf::FloatRect);
	bool checkPlayerCollision(sf::Vector2f);
	bool playerFound(sf::Vector2f);
	sf::Vector2f getPlayerVect();
	int getPcollidedwith();
	int getPattacked();
	int getTotalEnemies();
	~Collider();

private:
	sf::FloatRect p_rect;
	sf::Vector2f p_vect;
	int p_attacked;
	int p_collidedwith;

	std::vector<sf::FloatRect> l_walls;
	std::vector<sf::FloatRect> l_entrances;
	std::vector<sf::FloatRect> l_exits;
	std::vector<sf::FloatRect> l_enemies;
	int totalEnemies;
};

