#pragma once

#include <SFML\Graphics.hpp>

class Animator
{
public:
	Animator();
	Animator(sf::Sprite*, sf::Vector2i);
	void direction(int);
	~Animator();

private:
	int v_iter;
	int h_iter;
	//int move_iter;

	sf::IntRect m_textureRect;
	sf::Sprite* m_sprite;
};

