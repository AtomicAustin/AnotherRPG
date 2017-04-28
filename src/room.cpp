#include "room.h"

Room::Room()
{}
Room::Room(RoomInstructions newRoom)
{
	setUpTiles(newRoom.roomTiles, newRoom.mapSize, newRoom.file);
	this->mainEntrance = newRoom.mainEntrance;
	this->mainExit = newRoom.mainExit;
}
void Room::setNewRoom(RoomInstructions newRoom)
{
	walls.clear();
	entrances.clear();
	exits.clear();
	m_vertices.clear();

	setUpTiles(newRoom.roomTiles, newRoom.mapSize, newRoom.file);
	this->mainEntrance = newRoom.mainEntrance;
	this->mainExit = newRoom.mainExit;
}
void Room::setUpTiles(std::vector<short> tiles, sf::Vector2i mapSize, const std::string& tileset)
{
	sf::Clock m_clock;
	m_clock.restart();

	int tileSize = 16;
	int textureSize = 16;

	// load the tileset texture
	m_tileset.loadFromFile(tileset);

	// resize the vertex array to fit the level size
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(mapSize.x * mapSize.y * 4);

	srand(time(NULL));
	int textureY;
	int textureX;

	// populate the vertex array, with one quad per tile
	for (unsigned int i = 0; i < mapSize.x; ++i)
	{
		for (unsigned int j = 0; j < mapSize.y; ++j)
		{
			// get the current tile number
			int tileNumber = tiles[i + j * mapSize.x];
						
			// find its position in the tileset texture
			textureY = tileNumber;
			if (tileNumber < 2) {
				textureX = randomizeTile(tileNumber);
			}
			else {
				textureX = 0;
			}

			/*int tu = tileNumber % (m_tileset.getSize().x / tileSize);
			int tv = tileNumber / (m_tileset.getSize().x / tileSize);*/
			//std::cout << " tu/tv = " << tu << "/" << tv << std::endl;

			// get a pointer to the current tile's quad
			sf::Vertex* quad = &m_vertices[(i + j * mapSize.x) * 4];

			// define its 4 corners
			quad[0].position = sf::Vector2f(i * textureSize, j * textureSize);
			quad[1].position = sf::Vector2f((i + 1) * textureSize, j * textureSize);
			quad[2].position = sf::Vector2f((i + 1) * textureSize, (j + 1) * textureSize);
			quad[3].position = sf::Vector2f(i * textureSize, (j + 1) * textureSize);

			sf::FloatRect newRect;
			newRect.height = 16;
			newRect.width = 16;

			switch (tileNumber)
			{
				case 1: 
				{
					newRect.left = quad[0].position.x;
					newRect.top = quad[0].position.y;
					walls.push_back(newRect);
					break;
				}
				case 2: 
				{
					newRect.left = quad[0].position.x;
					newRect.top = quad[0].position.y;
					entrances.push_back(newRect);
					break;
				}
				case 3: 
				{
					newRect.left = quad[0].position.x;
					newRect.top = quad[0].position.y;
					exits.push_back(newRect);
					break;
				}
			}

			quad[0].texCoords = sf::Vector2f(textureX * tileSize, textureY * tileSize);
			quad[1].texCoords = sf::Vector2f((textureX + 1) * tileSize, textureY * tileSize);
			quad[2].texCoords = sf::Vector2f((textureX + 1) * tileSize, (textureY + 1) * tileSize);
			quad[3].texCoords = sf::Vector2f(textureX * tileSize, (textureY + 1) * tileSize);
		}
	}

	std::cout << "Time: " << m_clock.getElapsedTime().asSeconds() << std::endl;
}
int Room::randomizeTile(int tileChoice)
{ //0 - floor, 1 - wall, 2 - entrance, 3 - exit
	if(tileChoice == 0)
	{
		do {
			randomTile = rand() % 4;
		} while (last_floor == randomTile);

		last_floor = randomTile;
	}
	else
	{
		do{
			randomTile = rand() % 4;
		} while (last_wall == randomTile);

		last_wall = randomTile;
	}

	return randomTile;
}
std::vector<sf::FloatRect> Room::getWalls()
{
	return walls;
}
std::vector<sf::FloatRect> Room::getEntrances()
{
	return entrances;
}
std::vector<sf::FloatRect> Room::getExits()
{
	return exits;
}
sf::Vector2i Room::getMainEntrance()
{
	return mainEntrance;
}
sf::Vector2i Room::getMainExit()
{
	return mainExit;
}
void Room::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the entity's transform -- combine it with the one that was passed by the caller
	states.transform *= getTransform();

	// apply the texture
	states.texture = &m_tileset;

	// you may also override states.shader or states.blendMode if you want

	// draw the vertex array
	target.draw(m_vertices, states);
}