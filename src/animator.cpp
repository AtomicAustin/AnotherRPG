#include "animator.h"



Animator::Animator()
{}
Animator::Animator(sf::Sprite* n_sprite, sf::Vector2i size)
{
	m_sprite = n_sprite;

	m_textureRect.top = 0;
	m_textureRect.left = 0;
	m_textureRect.width = size.x;
	m_textureRect.height = size.y;

	if (size.x > 16) {
		int xDiff = size.x - 16;
		m_sprite->move(-(xDiff), 0);
	}
	if (size.y > 16) {
		int yDiff = size.y - 16;
		m_sprite->move(0, -(yDiff));
	}

	h_iter = m_textureRect.height;
	v_iter = m_textureRect.width;

	m_sprite->setTextureRect(m_textureRect);
}
void Animator::direction(int dir)
{
	switch (dir)
	{
		case 1: {m_textureRect.top = 0; break; }
		case -1: {m_textureRect.top = h_iter; break; }
		case 2: {m_textureRect.left = 0; break; }
		case -2: {m_textureRect.left = v_iter; break; }
	}

	m_sprite->setTextureRect(m_textureRect);
}
Animator::~Animator()
{
}
