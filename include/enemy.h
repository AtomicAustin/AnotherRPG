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
	Enemy(EnemyInstructions, int, std::string, Collider*);
	void addPath(std::vector<MoveDirections>);
	void setTag(int);
	int getTag();
	void move();
	void updateState();
	void seek();
	void wander();
	void goBack();
	bool testHitbox(MoveDirections);
	void takeMove(MoveDirections);
	int attack();
	void updateHealth(int);
	int getHealth();
	bool killAnimation();
	void kill();
	bool isDead();
	void setHealthPosition();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	Movement* m_mover;
	std::vector<MoveDirections> m_path;
	sf::Vector2f oldPosition;
	PathingState state;
	bool collidingWithPlayer;
	bool attackPlayer;
	int currentDirection;
	int tag;

	int TOTAL_HEALTH;
	int cur_health;
	int damage_modifier;

	sf::RectangleShape red;
	sf::RectangleShape green;
	bool showHealth;
	bool dead;
};

