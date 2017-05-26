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
Enemy::Enemy(EnemyInstructions n_inst, int n_tag, std::string n_name, Collider* n_collider) : tag(n_tag), dead(false)
{
	if (n_collider != NULL) {
		m_collider = n_collider;

	}
	else {
		std::cout << "Collider is bad" << std::endl;
	}

	m_texture.loadFromFile(n_inst.filename);
	m_sprite.setTexture(m_texture);
	setPosition(n_inst.position);

	updateHitbox();

	name = n_name;

	m_animator = new Animator(&m_sprite, n_inst.size);
	m_animator->addDeath(n_inst.deathdimensions, n_inst.deathmove, n_inst.total_iterations);
	m_mover = new Movement(&m_sprite);

	TOTAL_HEALTH = n_inst.total_health;
	cur_health = TOTAL_HEALTH;
	damage_modifier = n_inst.damage_modifier;

	red.setFillColor(sf::Color::Red);
	red.setSize(sf::Vector2f(m_sprite.getGlobalBounds().width - 2, 3));
	red.setPosition(m_sprite.getGlobalBounds().left + 1, m_sprite.getGlobalBounds().top - 5);

	green.setFillColor(sf::Color::Green);
	green.setSize(sf::Vector2f(m_sprite.getGlobalBounds().width - 2, 3));
	green.setPosition(m_sprite.getGlobalBounds().left + 1, m_sprite.getGlobalBounds().top - 5);

	showHealth = false;
	attackPlayer = false;
	state = wandering;
	collidingWithPlayer = false;
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
void Enemy::move()
{
	if (dead) {
		return;
	}

	updateState();

	switch (state)
	{
		case wandering: {wander(); break; }
		case seeking: {seek(); break; }
		case returning: {goBack(); break; }
	}
}
void Enemy::updateState()
{
	if (m_collider->playerFound(m_hitbox)) 
	{
		if (state == wandering) {
			oldPosition = m_hitbox;
		}
		state = seeking;
	}
	else if (state == seeking) {
		state = returning;
	}
	else if (m_hitbox == oldPosition) {
		state = wandering;
	}
}
void Enemy::wander()
{
	MoveDirections to_move = m_path[currentDirection];

	if (testHitbox(to_move))
	{
		takeMove(to_move);

		currentDirection++;
		if (currentDirection == m_path.size()) {
			currentDirection = 0;
		}
	}
}
void Enemy::seek()
{
	MoveDirections to_player = m_mover->takeXY(m_hitbox, m_collider->getPlayerVect());

	if (!testHitbox(to_player))
	{
		if (!collidingWithPlayer) {
			to_player = m_mover->retakeXY();
		}
	}
	else {
		takeMove(to_player);
	}
}
void Enemy::goBack()
{
	MoveDirections to_oldPosition = m_mover->takeXY(m_hitbox, oldPosition);

	if (!testHitbox(to_oldPosition)){
		to_oldPosition = m_mover->retakeXY();
		
		if (!testHitbox(to_oldPosition)) {
			return;
		}
	}

	takeMove(to_oldPosition);
}
bool Enemy::testHitbox(MoveDirections dir)
{
	m_mover->moveHitbox(dir, m_hitbox);

	if (m_collider->checkPlayerCollision(m_hitbox)) {
		m_mover->moveBackHitbox(dir, m_hitbox);
		collidingWithPlayer = true;
		attackPlayer = true;
		return false;
	}
	else {
		attackPlayer = false;
		collidingWithPlayer = false;
	}

	if (m_collider->checkWallCollision(m_hitbox)){
		m_mover->moveBackHitbox(dir, m_hitbox);
		return false;
	}

	return true;
}
void Enemy::takeMove(MoveDirections dir)
{
	m_mover->move(dir);
	m_animator->direction(dir);
	setHealthPosition();
	updateHitbox();
}
int Enemy::attack()
{
	return rand() % 3 + damage_modifier;
}
void Enemy::updateHealth(int n_hit)
{
	cur_health -= n_hit;

	green.setSize(sf::Vector2f(((float)cur_health / TOTAL_HEALTH) * (m_sprite.getGlobalBounds().width - 2), 3));
	
	showHealth = true;
}
int Enemy::getHealth()
{
	return cur_health;
}
bool Enemy::killAnimation()
{
	return m_animator->deathAnim();
}
void Enemy::kill() 
{
	cur_health = 0;
	green.setSize(sf::Vector2f(0, 3));
	dead = true;
}
bool Enemy::isDead()
{
	return dead;
}
void Enemy::setHealthPosition()
{
	red.setPosition(m_sprite.getGlobalBounds().left + 1, m_sprite.getGlobalBounds().top - 5);
	green.setPosition(m_sprite.getGlobalBounds().left + 1, m_sprite.getGlobalBounds().top - 5);
}
void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// draw the vertex array
	target.draw(m_sprite, states);
	
	if (showHealth) {
		target.draw(red, states);
		target.draw(green, states);
	}
}