#include "gameobject.h"

GameObject::GameObject()
{}
void GameObject::updateHitbox()
{
	m_hitbox.x = m_sprite.getPosition().x + (m_sprite.getGlobalBounds().width / 2);
	m_hitbox.y = m_sprite.getPosition().y + (m_sprite.getGlobalBounds().height / 2);
}
void GameObject::addCollider(Collider* n_collider)
{
	m_collider = n_collider;
}
void GameObject::setPosition(sf::Vector2i pos)
{
	m_sprite.setPosition(float((pos.x - 1) * 16), float((pos.y - 1) * 16));
	updateHitbox();
}
void GameObject::setName(std::string n_name)
{
	name = n_name;
}
sf::Vector2f GameObject::getPosition()
{
	return m_sprite.getPosition();
}
std::string GameObject::getName()
{
	return name;
}
sf::FloatRect GameObject::getRect()
{
	return m_sprite.getGlobalBounds();
}
void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// draw the vertex array
	target.draw(m_sprite, states);
}
GameObject::~GameObject()
{}
