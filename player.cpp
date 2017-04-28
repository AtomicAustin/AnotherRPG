#include "player.h"

Player::Player()
{}
void Player::setUp(std::string filename, sf::Vector2i size, std::string n_name, Collider* n_collider)
{
	m_texture.loadFromFile(filename);
	m_sprite.setTexture(m_texture);
	updateHitbox();

	m_animator = new Animator(&m_sprite, size);
	m_mover = new Movement(&m_sprite);
	m_collider = n_collider;

	name = n_name;

	TOTAL_HEALTH = 100;
	cur_health = 100;
}
int Player::move(int direction)
{
	m_mover->move(direction);
	m_animator->direction(direction);
	updateHitbox();


	switch(m_collider->checkCollision(m_hitbox))
	{ //1 wall 2 entrance 3 exit 4 enemy
		case 1:
		{
			m_mover->move(-(direction));
			m_animator->direction(direction);
			updateHitbox();
			break;
		}
		case 2: { 
			return 1;
		}
		case 3: {
			return 2;
		}
		case 4: {
			m_mover->move(-(direction));
			m_animator->direction(direction);
			updateHitbox();
			return 4;
		}
	}

	return 0;
}
int Player::getCurHealth()
{
	return cur_health;
}
void Player::removeHealth(int hp)
{
	cur_health -= hp;
}
Player::~Player()
{
	if (m_mover != NULL) {
		delete m_mover;
		m_mover = NULL;
	}
	if (m_animator != NULL) {
		delete m_animator;
		m_animator = NULL;
	}

}
