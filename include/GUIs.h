#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include "types.h"

class GUI : public sf::Transformable, public sf::Drawable
{
public:
	GUI();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::Font m_font;
	int FONT_SIZE = 12;
};

class GameConsole : public GUI
{
public:
	GameConsole();
	GameConsole(std::string, sf::Vector2f);
	void create(std::string, sf::Vector2f);
	void sendMessage(std::string);
	void reset();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	std::vector<sf::Text> displayedText;
	int displayedNum;
	sf::Vector2f firstLinePosition;
};

class PlayerStats : public GUI
{
public:
	PlayerStats();
	PlayerStats(std::string, std::string, sf::Vector2f, int);
	void create(std::string, std::string, sf::Vector2f, int);
	void updateHealth(int);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Vector2f textPosition;
	int totalHealth;
	int currentHealth;
	sf::Text healthDisplay;

	sf::Texture m_portraitTexture;
	sf::Sprite m_portrait;
};

class MiniMap : public GUI
{
public:
	MiniMap();
	MiniMap(std::string, sf::Vector2f, std::string, std::string);
	void create(std::string, sf::Vector2f, std::string, std::string);
	void update(std::string, std::string);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Text cur_lr;
	sf::Vector2f lr_pos;
};