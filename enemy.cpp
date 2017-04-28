#include "enemy.h"



Enemy::Enemy()
{}
Enemy::~Enemy()
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

Enemy::Enemy(std::string filename, sf::Vector2i position, sf::Vector2i size, int n_tag, std::string n_name) : tag(n_tag)
{
	m_texture.loadFromFile(filename);
	m_sprite.setTexture(m_texture);
	setPosition(position);

	updateHitbox();

	name = n_name;

	m_animator = new Animator(&m_sprite, size);
	m_mover = new Movement(&m_sprite);
}
Enemy::Enemy(std::string filename, sf::Vector2i position, sf::Vector2i size, int n_tag, std::string n_name, Collider* n_collider) : tag(n_tag)
{
	if (n_collider != NULL) {
		m_collider = n_collider;

	}
	else {
		std::cout << "Collider is bad" << std::endl;
	}

	m_texture.loadFromFile(filename);
	m_sprite.setTexture(m_texture);
	setPosition(position);

	updateHitbox();

	name = n_name;

	m_animator = new Animator(&m_sprite, size);
	m_mover = new Movement(&m_sprite);
}
void Enemy::addPath(std::vector<MoveDirections> newDirections)
{
	if (!newDirections.empty()) {
		m_path = newDirections;
		currentDirection = 0;
	}
	else {
		std::cout << "Move directions empty." << std::endl;
	}

}
void Enemy::setTag(int n_tag)
{
	tag = n_tag;
}
int Enemy::getTag()
{
	return tag;
}
int Enemy::move()
{
	//[-2,-1,1,2] - [up,left,right,down]
	switch (m_path[currentDirection])
	{
			//UP
		case 0: {m_mover->move(-2); m_animator->direction(-2);  break; }
			//DOWN
		case 1: {m_mover->move(2); m_animator->direction(2); break; }
			//LEFT
		case 2: {m_mover->move(-1); m_animator->direction(-1); break; }
			//RIGHT
		case 3: {m_mover->move(1); m_animator->direction(1);  break; }
	}
	
	updateHitbox();

	if (m_collider->checkPlayerCollision(m_hitbox)) {
		switch (m_path[currentDirection])
		{
				//UP
		case 0: {m_mover->move(2); break; }
				//DOWN
		case 1: {m_mover->move(-2); break; }
				//LEFT
		case 2: {m_mover->move(1); m_animator->direction(1); break; }
				//RIGHT
		case 3: {m_mover->move(-1); m_animator->direction(-1); break; }
		}
		return 1;
	}
	else {
		currentDirection++;
		if (currentDirection == m_path.size()) {
			currentDirection = 0;
		}
	}
	
	return 0;
}