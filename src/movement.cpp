#include "movement.h"

Movement::Movement()
{}
Movement::Movement(sf::Sprite* new_sprite)
{
	obj_sprite = new_sprite;
}
void Movement::move(int direction)
{
	//[-2,-1,1,2] - [up,left,right,down]
	switch (direction)
	{
		case -2:{
			obj_sprite->move(sf::Vector2f(0, -16));
			break;
		}
		case -1:{
			obj_sprite->move(sf::Vector2f(-16, 0));
			break;
		}
		case 1:{
			obj_sprite->move(sf::Vector2f(16, 0));
			break;
		}
		case 2:{
			obj_sprite->move(sf::Vector2f(0, 16));
			break;
		}
	}
}
Movement::~Movement()
{
	/*if (obj_sprite != NULL) {
		delete obj_sprite;
		obj_sprite = NULL;
	}*/
}
