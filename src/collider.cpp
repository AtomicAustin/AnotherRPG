#include "collider.h"

Collider::Collider() : totalEnemies(0)
{}
Collider::Collider(std::vector<sf::FloatRect> n_walls, std::vector<sf::FloatRect> n_entrances, std::vector<sf::FloatRect> n_exits) : totalEnemies(0)
{
	l_walls = n_walls;
	l_entrances = n_entrances;
	l_exits = n_exits;
}
void Collider::replaceTiles(std::vector<sf::FloatRect> n_walls, std::vector<sf::FloatRect> n_entrances, std::vector<sf::FloatRect> n_exits)
{
	l_walls.clear();
	l_entrances.clear();
	l_exits.clear();

	l_walls = n_walls;
	l_entrances = n_entrances;
	l_exits = n_exits;
}
void Collider::addEnemy(sf::FloatRect n_enemy)
{
	l_enemies.push_back(n_enemy);
	totalEnemies++;
}
void Collider::updateEnemy(sf::FloatRect n_enemy, int i)
{
	l_enemies[i] = n_enemy;
}
void Collider::removeEnemy(int to_remove)
{
	if (l_enemies.size() > 1){
		l_enemies.erase(l_enemies.begin() + to_remove);
		totalEnemies--;
	}
	else {
		l_enemies.pop_back();
		totalEnemies = 0;
	}

}
void Collider::clearEnemies()
{
	l_enemies.clear();
	totalEnemies = 0;
}
bool Collider::checkCollision(sf::Vector2f n_hitbox)
{
	bool ret_val = checkLevelCollision(n_hitbox);
	
	if (ret_val == 0) {
		ret_val = checkEnemyCollision(n_hitbox);
	}

	return ret_val;

}
bool Collider::checkLevelCollision(sf::Vector2f n_hitbox)
{
	for (int i = 0; i < l_entrances.size(); i++)
	{
		if (l_entrances[i].contains(n_hitbox)) {
			p_collidedwith = 2;
			return true;
		}
	}

	for (int i = 0; i < l_exits.size(); i++)
	{
		if (l_exits[i].contains(n_hitbox)) {
			p_collidedwith = 3;
			return true;
		}
	}

	p_collidedwith = -1;
	return false;
}
bool Collider::checkWallCollision(sf::Vector2f n_box)
{
	for (int i = 0; i < l_walls.size(); i++)
	{
		if (l_walls[i].contains(n_box)) {
			return true;
		}
	}

	return false;
}
bool Collider::checkEnemyCollision(sf::Vector2f n_box)
{
	for (int i = 0; i < totalEnemies; i++)
	{
		if (l_enemies[i].contains(n_box)) {
			p_collidedwith = 4;
			return true;
		}
	}

	p_collidedwith = -1;

	return false;
}
bool Collider::checkEnemyHit(sf::Vector2f n_box)
{
	for (int i = 0; i < totalEnemies; i++)
	{
		if (l_enemies[i].contains(n_box)) {
			p_attacked = i;
			return true;
		}
	}

	p_attacked = -1;

	return false;
}
void Collider::updatePlayer(sf::FloatRect n_player)
{
	p_rect = n_player;
	p_vect = sf::Vector2f(n_player.left + 8, n_player.top + 8);
}
bool Collider::checkPlayerCollision(sf::Vector2f n_enemy)
{
	if (p_rect.contains(n_enemy)) {
		return true;
	}

	return false;
}
bool Collider::playerFound(sf::Vector2f n_enemy)
{
	sf::FloatRect e_sight(n_enemy.x - 32, n_enemy.y - 32, 16 * 5, 16 * 5);

	if (e_sight.contains(p_vect)){
		return true;
	}

	return false;
}
sf::Vector2f Collider::getPlayerVect()
{
	return p_vect;
}
int Collider::getPcollidedwith()
{
	return p_collidedwith;
}
int Collider::getPattacked()
{
	return p_attacked;
}
int Collider::getTotalEnemies()
{
	return totalEnemies;
}
Collider::~Collider()
{}
