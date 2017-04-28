#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>

class Movement
{
public:
	Movement();
	Movement(sf::Sprite*);
	void move(int);
	~Movement();

private:
	sf::Sprite* obj_sprite;
};

