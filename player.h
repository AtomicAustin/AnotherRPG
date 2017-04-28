#pragma once

#include "gameobject.h"
#include "movement.h"
#include <iostream>
#include <SFML\Graphics.hpp>
#include "types.h"

class Player : public GameObject
{
public:
	Player();
	void setUp(std::string, sf::Vector2i, std::string, Collider*);
	int move(int);
	int getCurHealth();
	void removeHealth(int);

	~Player();
	
private:

	int TOTAL_HEALTH;
	int cur_health;

	Movement* m_mover;
};

