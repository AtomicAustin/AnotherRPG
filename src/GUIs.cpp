#include "GUIs.h"

GUI::GUI()
{}
void GUI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// draw the vertex array
	target.draw(m_sprite, states);
}

GameConsole::GameConsole()
{}
GameConsole::GameConsole(std::string filename, sf::Vector2f position)
{
	create(filename, position);
}
void GameConsole::create(std::string filename, sf::Vector2f position)
{
	m_texture.loadFromFile(filename);
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(10, 10);
	m_sprite.setPosition(position);

	firstLinePosition.x = position.x + 15;
	firstLinePosition.y = position.y + m_sprite.getGlobalBounds().height - 30;

	m_font.loadFromFile(GENERIC_FONT);

	sf::Text newMessage("Level has begun!", m_font, FONT_SIZE);
	newMessage.setPosition(firstLinePosition);

	displayedText.push_back(newMessage);
	displayedNum = 1;
}
void GameConsole::sendMessage(std::string message)
{
	if (displayedNum < 10) { // can only display 10 lines of text
		displayedNum++;
		displayedText.resize(displayedNum);
	}

	for (int i = displayedNum - 1; i > 0; i--) {
		displayedText[i] = displayedText[i - 1];
	}

	for (int i = 0; i < displayedNum; i++) {
		displayedText[i].move(sf::Vector2f(0, -16)); //move up 10 pixels
	}

	sf::Text newMessage(message, m_font, FONT_SIZE);
	newMessage.setPosition(firstLinePosition);
	
	displayedText[0] = newMessage;

}
void GameConsole::reset()
{
	displayedText.clear();
	sf::Text newMessage("Level has begun!", m_font, FONT_SIZE);
	newMessage.setPosition(firstLinePosition);

	displayedText.push_back(newMessage);
	displayedNum = 1;
}
void GameConsole::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	target.draw(m_sprite, states);

	for (int i = 0; i < displayedNum; i++) {
		target.draw(displayedText[i], states);
	}

}

PlayerStats::PlayerStats()
{}
PlayerStats::PlayerStats(std::string filename, std::string portrait, sf::Vector2f position, int totalHealth)
{
	create(filename, portrait, position, totalHealth);
}
void PlayerStats::create(std::string filename, std::string portrait, sf::Vector2f position, int totalHealth)
{
	this->totalHealth = totalHealth;

	m_texture.loadFromFile(filename);
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(10, 10);
	m_sprite.setPosition(position);

	m_portraitTexture.loadFromFile(portrait);
	m_portrait.setTexture(m_portraitTexture);
	m_portrait.setScale(10, 10);
	m_portrait.setPosition(position.x + 20, position.y + 20);
	
	textPosition.x = position.x + 215;
	textPosition.y = position.y + 27;
	m_font.loadFromFile(GENERIC_FONT);
	healthDisplay.setFont(m_font);
	healthDisplay.setCharacterSize(18);
	healthDisplay.setPosition(textPosition);

	updateHealth(totalHealth);
}
void PlayerStats::updateHealth(int cur_health)
{
	currentHealth = cur_health;
	std::string str_health = "HP [" + std::to_string(cur_health) + "/" + std::to_string(totalHealth) + "]";

	healthDisplay.setString(str_health);
}
void PlayerStats::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	target.draw(m_sprite, states);
	target.draw(m_portrait, states);
	target.draw(healthDisplay, states);
}

MiniMap::MiniMap()
{}
MiniMap::MiniMap(std::string filename, sf::Vector2f position, std::string level, std::string room)
{
	create(filename, position, level, room);
}
void MiniMap::create(std::string filename, sf::Vector2f position, std::string level, std::string room)
{
	m_texture.loadFromFile(filename);
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(10, 10);
	m_sprite.setPosition(position);

	lr_pos.x = position.x + 35;
	lr_pos.y = position.y + 22;

	m_font.loadFromFile(GENERIC_FONT);
	cur_lr.setFont(m_font);
	cur_lr.setCharacterSize(18);
	cur_lr.setPosition(lr_pos);

	update(level, room);
}
void MiniMap::update(std::string level, std::string room)
{
	std::string lr = "Level " + level + " : " + room;
	cur_lr.setString(lr);
}
void MiniMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	target.draw(m_sprite, states);
	target.draw(cur_lr, states);
}