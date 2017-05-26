#include "player.h"

Player::Player()
{}
void Player::setUp(PlayerInstructions n_player, Collider* n_collider)
{
	m_texture.loadFromFile(n_player.filename);
	m_sprite.setTexture(m_texture);
	updateHitbox();

	m_animator = new Animator(&m_sprite, n_player.dimensions);

	sf::Vector2f deathdimensions = n_player.deathdimensions;
	sf::Vector2f deathmove = n_player.deathmove;
	int total_iterations = n_player.total_iterations;

	m_animator->addDeath(deathdimensions, deathmove, total_iterations);

	m_mover = new Movement(&m_sprite);
	m_collider = n_collider;

	name = n_player.disp_name;

	TOTAL_HEALTH = n_player.total_health;
	cur_health = TOTAL_HEALTH;
	damage_modifier = n_player.damage_modifier;

	r_attackbox.setPosition(0, 0);
	r_attackbox.setSize(sf::Vector2f(5, 5));
	r_attackbox.setFillColor(sf::Color::Red);
	show_box = false;
}
void Player::move(MoveDirections direction)
{
	m_animator->direction(direction);
	lastmove = direction;

	if (p_clock.getElapsedTime().asSeconds() > .25)
	{
		if (testHitBox(direction)) {
			m_mover->move(direction);
			updateHitbox();
			p_clock.restart();

			m_collider->checkLevelCollision(m_hitbox);
		}
	}
}
bool Player::testHitBox(MoveDirections dir)
{
	bool to_ret = true;

	m_mover->moveHitbox(dir, m_hitbox);

	if (m_collider->checkWallCollision(m_hitbox)) {
		to_ret = false;
	}
	else if (m_collider->checkEnemyCollision(m_hitbox)) {
		to_ret = false;
	}

	m_mover->moveBackHitbox(dir, m_hitbox);

	return to_ret;
}
void Player::attack(int attack_iter)
{
	//[-2,-1,1,2] - [up,left,right,down]
	switch (lastmove)
	{
		case UP: { attack_box = sf::Vector2f(m_hitbox.x, m_hitbox.y - 16); break;}
		case LEFT: { attack_box = sf::Vector2f(m_hitbox.x - 16, m_hitbox.y); break;}
		case RIGHT: { attack_box = sf::Vector2f(m_hitbox.x + 16, m_hitbox.y); break;}
		case DOWN: { attack_box = sf::Vector2f(m_hitbox.x, m_hitbox.y + 16); break;}
	}

	r_attackbox.setPosition(attack_box);//for the box visual

	m_collider->checkEnemyHit(attack_box);

	m_animator->attackAnim(attack_iter);

	show_box = true;

	if (attack_iter == 1) {
		show_box = false;
	}
}
int Player::getDamage()
{
	return rand() % 3 + damage_modifier;
}
int Player::getCurHealth()
{
	return cur_health;
}
void Player::removeHealth(int hp)
{
	cur_health -= hp;
}
bool Player::kill()
{
	return m_animator->deathAnim();
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
void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// draw the vertex array
	target.draw(m_sprite, states);

	if (show_box) {
		target.draw(r_attackbox, states);
	}
}