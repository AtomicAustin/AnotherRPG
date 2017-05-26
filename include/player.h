#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>

#include "gameobject.h"
#include "movement.h"
#include "types.h"

class Player : public GameObject
{
public:
	Player();
	void setUp(PlayerInstructions, Collider*);
	void move(MoveDirections);
	bool testHitBox(MoveDirections);
	void attack(int);
	int getDamage();
	int getCurHealth();
	void removeHealth(int);
	bool kill();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	~Player();
	
private:

	int lastmove;
	sf::Vector2f attack_box;

	int TOTAL_HEALTH;
	int cur_health;
	int damage_modifier;

	sf::Clock p_clock;

	Movement* m_mover;

	sf::RectangleShape r_attackbox;
	bool show_box;
};

