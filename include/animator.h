#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include "types.h"

class Animator
{
public:
	Animator();
	Animator(sf::Sprite*, sf::Vector2i);
	void direction(MoveDirections);
	void attackAnim(int);
	void addDeath(sf::Vector2f, sf::Vector2f, int);
	bool deathAnim();
	~Animator();

private:
	int s_width;
	int s_height;
	
	int attack_offset;

	bool death;
	int death_x;
	sf::Vector2f d_move;
	int d_iter;
	int max_iter;

	sf::IntRect m_textureRect;
	sf::IntRect m_deathRect;
	sf::Sprite* m_sprite;
};

