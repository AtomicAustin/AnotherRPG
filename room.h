#pragma once

#include <iostream>
#include <time.h>
#include <SFML\Graphics.hpp>
#include "types.h"

class Room : public sf::Drawable, public sf::Transformable
{
public:
	Room();
	Room(RoomInstructions);
	void setNewRoom(RoomInstructions);
	void setUpTiles(std::vector<short>, sf::Vector2i, const std::string&);
	int randomizeTile(int);
	std::vector<sf::FloatRect> getWalls();
	std::vector<sf::FloatRect> getEntrances();
	std::vector<sf::FloatRect> getExits();
	sf::Vector2i getMainEntrance();
	sf::Vector2i getMainExit();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;

	int last_floor;
	int last_wall;
	int randomTile;

	sf::Vector2i mainEntrance;
	sf::Vector2i mainExit;
	std::vector<sf::FloatRect> walls;
	std::vector<sf::FloatRect> entrances;
	std::vector<sf::FloatRect> exits;

};

