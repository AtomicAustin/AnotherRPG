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

	s_height = m_textureRect.height;
	s_width = m_textureRect.width;
	d_iter = 0;

	m_sprite->setTextureRect(m_textureRect);
	
	death = false;
}
void Animator::direction(MoveDirections dir)
{
	switch (dir)
	{
		case RIGHT: {m_textureRect.top = 0; break; }
		case LEFT: {m_textureRect.top = s_height; break; }
		case DOWN: {m_textureRect.left = 0; break; }
		case UP: {m_textureRect.left = s_width; break; }
	}

	m_sprite->setTextureRect(m_textureRect);
}
void Animator::attackAnim(int attack_iter)
{
	//iterate through attack animation based on attack iterator
}
void Animator::addDeath(sf::Vector2f dimensions, sf::Vector2f move, int tot_iter)
{
	if (tot_iter != 0) {
		death = true;
	}
	else {
		return;
	}

	m_deathRect.left = 0;
	m_deathRect.top = s_height * 2;
	m_deathRect.width = dimensions.x;
	m_deathRect.height = dimensions.y;

	death_x = dimensions.x;
	d_move = move;
	max_iter = tot_iter;
}
bool Animator::deathAnim()
{
	if (!death) {
		return true;
	}

	if (d_iter == 0) {
		m_sprite->move(d_move);
	}

	m_deathRect.left = death_x * d_iter;
	m_sprite->setTextureRect(m_deathRect);
	d_iter++;

	if (d_iter >= max_iter) {
		return true;
	}
	return false;
}
Animator::~Animator()
{
}
