#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include "gameobject.h"
#include "types.h"
#include "movement.h"

class Enemy: public GameObject
{
public:
	Enemy();
	~Enemy();
	Enemy(std::string, sf::Vector2i, sf::Vector2i, int, std::string);
	Enemy(std::string, sf::Vector2i, sf::Vector2i, int, std::string, Collider*);
	void addPath(std::vector<MoveDirections>);
	void setTag(int);
	int getTag();
	int move();

private:
	Movement* m_mover;

	std::vector<MoveDirections> m_path;
	int currentDirection;
	int tag;
};

