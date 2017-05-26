#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <stdlib.h>

#include "types.h"

class Movement
{
public:
	Movement();
	Movement(sf::Sprite*);
	void move(MoveDirections);
	void moveHitbox(MoveDirections, sf::Vector2f&);
	void moveBackHitbox(MoveDirections, sf::Vector2f&);
	MoveDirections takeXY(sf::Vector2f, sf::Vector2f);
	MoveDirections retakeXY();
	MoveDirections tryMove(MoveDirections);
	~Movement();

private:
	sf::Sprite* obj_sprite;

	MoveDirections lastMove, lastlastMove;
	float xDiff, yDiff;
};

