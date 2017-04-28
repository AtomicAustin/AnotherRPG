#pragma once

#include "animator.h"
#include "collider.h"
#include <SFML\Graphics.hpp>

class GameObject: public sf::Transformable, public sf::Drawable
{
public:
	GameObject();
	~GameObject();
	void updateHitbox();
	void addCollider(Collider*);
	void setPosition(sf::Vector2i);
	void setName(std::string);
	sf::Vector2f getPosition();
	std::string getName();
	sf::FloatRect getRect();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
	Animator* m_animator;

	//shared collider among all gameobjects - all enemies/players/etc
	Collider* m_collider;

	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_hitbox;

	std::string name;
};

