#include "movement.h"

Movement::Movement()
{}
Movement::Movement(sf::Sprite* n_sprite)
{
	obj_sprite = n_sprite;
}
void Movement::move(MoveDirections dir)
{
	switch (dir)
	{
	case UP: { obj_sprite->move(sf::Vector2f(0, -16));break;}
	case LEFT: { obj_sprite->move(sf::Vector2f(-16, 0));break;}
	case RIGHT: { obj_sprite->move(sf::Vector2f(16, 0));break;}
	case DOWN: { obj_sprite->move(sf::Vector2f(0, 16));break;}
	}
	
	lastMove = dir;
}
void Movement::moveHitbox(MoveDirections dir, sf::Vector2f& n_hitbox)
{
	switch (dir)
	{
	case UP: { n_hitbox.y += -16;break;}
	case LEFT: { n_hitbox.x += -16;break;}
	case RIGHT: { n_hitbox.x += 16;break;}
	case DOWN: { n_hitbox.y += 16;break;}
	}
}
void Movement::moveBackHitbox(MoveDirections dir, sf::Vector2f& n_hitbox)
{
	switch (dir)
	{
	case UP: {n_hitbox.y += 16; break; }
	case DOWN: {n_hitbox.y -= 16; break; }
	case LEFT: {n_hitbox.x += 16; break; }
	case RIGHT: {n_hitbox.x -= 16; break; }
	}
}
MoveDirections Movement::takeXY(sf::Vector2f m_hitbox, sf::Vector2f n_hitbox)
{
	xDiff = m_hitbox.x - n_hitbox.x;
	yDiff = m_hitbox.y - n_hitbox.y;

	if (abs(xDiff) >= abs(yDiff)) {
		//take X
		if (xDiff > 0) {
			lastMove = LEFT;
		}
		else {
			lastMove = RIGHT;
		}
	}
	else {
		//take Y
		if (yDiff > 0) {
			lastMove = UP;
		}
		else {
			lastMove = DOWN;
		}
	}

	return lastMove;
}
MoveDirections Movement::retakeXY()
{
	if (lastMove == DOWN || UP) {
		if (xDiff > 0) {
			lastMove = RIGHT;
		}
		else {
			lastMove = LEFT;
		}
	}
	else {
		if (yDiff > 0) {
			lastMove = UP;
		}
		else {
			lastMove = DOWN;
		}
	}

	return lastMove;
}
Movement::~Movement()
{
	/*if (obj_sprite != NULL) {
		delete obj_sprite;
		obj_sprite = NULL;
	}*/
}
