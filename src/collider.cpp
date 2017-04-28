#include "collider.h"

Collider::Collider()
{}
Collider::Collider(std::vector<sf::FloatRect> n_walls, std::vector<sf::FloatRect> n_entrances, std::vector<sf::FloatRect> n_exits)
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
}
void Collider::updateEnemy(sf::FloatRect n_enemy, int i)
{
	l_enemies[i] = n_enemy;
}
void Collider::removeEnemy(int to_remove)
{
	if (l_enemies.size() > 1){
		l_enemies.erase(l_enemies.begin() + to_remove);
	}
	else {
		l_enemies.pop_back();
	}
}
void Collider::clearEnemies()
{
	l_enemies.clear();
}
int Collider::checkCollision(sf::Vector2f n_hitbox)
{
	for (int i = 0; i < l_walls.size(); i++)
	{
		if (l_walls[i].contains(n_hitbox)) {
			return 1;
		}
	}

	for (int i = 0; i < l_entrances.size(); i++)
	{
		if (l_entrances[i].contains(n_hitbox)) {
			return 2;
		}
	}

	for (int i = 0; i < l_exits.size(); i++)
	{
		if (l_exits[i].contains(n_hitbox)) {
			return 3;
		}
	}
	
	for (int i = 0; i < l_enemies.size(); i++)
	{
		if (l_enemies[i].contains(n_hitbox)) {
			p_collidedwith = i;
			return 4;
		}
	}

	return 0;

}
void Collider::updatePlayer(sf::FloatRect n_player)
{
	l_player = n_player;
}
bool Collider::checkPlayerCollision(sf::Vector2f n_enemy)
{
	if (l_player.contains(n_enemy)) {
		return true;
	}

	return false;
}
int Collider::getPcollidedwith()
{
	return p_collidedwith;
}
Collider::~Collider()
{}
