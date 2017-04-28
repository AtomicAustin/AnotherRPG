#include "level.h"

//0 - path
//1 - wall
//2 - entrance
//3 - exit

Level::Level()
{}
Level::Level(int level_num) : cur_level(level_num),	totalRooms(0), roomIter(0), collided_with(0), nextLevel(false), totalEnemies(0)
{
	levelView.reset(sf::FloatRect(0, 0, 250, 150));
	levelView.setViewport(sf::FloatRect(0, 0, .85, .75));
	viewCenter.left = levelView.getCenter().x - 100;
	viewCenter.top = levelView.getCenter().y - 50;
	viewCenter.height = 84;
	viewCenter.width = 184;	

	mm_view.setViewport(sf::FloatRect(.86, .07, .13, .15));

	Tooltip.setSize(sf::Vector2f(192, 192));
	Inventory.setSize(sf::Vector2f(192, 336));
	Toolbar.setSize(sf::Vector2f(192, 48));

	Tooltip.setPosition(1088, 576);
	Inventory.setPosition(1088, 240);
	Toolbar.setPosition(1088, 192);


	Tooltip.setOutlineColor(sf::Color::Blue);
	Tooltip.setFillColor(sf::Color::Black);
	Tooltip.setOutlineThickness(5);

	Inventory.setOutlineColor(sf::Color::Blue);
	Inventory.setFillColor(sf::Color::Black);
	Inventory.setOutlineThickness(5);

	Toolbar.setOutlineColor(sf::Color::Blue);
	Toolbar.setFillColor(sf::Color::Black);
	Toolbar.setOutlineThickness(5);

}
Level::~Level()
{
	if (currentRoom != NULL) {
		delete currentRoom;
		currentRoom = NULL;
	}

	for (int i = 0; i < totalEnemies; i++) {
		if (enemies[i] != NULL) {
			delete enemies[i];
			enemies[i] = NULL;
		}
	}

	if (m_collider != NULL) {
		delete m_collider;
		m_collider = NULL;
	}
}
void Level::addRoom(RoomInstructions n_room, std::vector<EnemyInstructions> n_enemies)
{
	allRooms.push_back(n_room);
	totalRooms++;

	allEnemies.push_back(n_enemies);
}
int Level::runLevel(sf::RenderWindow* gameWindow)
{
	gameView = gameWindow->getDefaultView();

	currentRoom = new Room(allRooms[roomIter]);

	m_collider = new Collider(currentRoom->getWalls(), currentRoom->getEntrances(), currentRoom->getExits());
	player.setUp("player/BuffNerd(16x16).png", sf::Vector2i(16,16), "Buff Nerd", m_collider);
	player.setPosition(currentRoom->getMainEntrance());

	m_console.create("UI/gameconsole.png", sf::Vector2f(0, 576));
	m_pstats.create("UI/playerStats.png", sf::Vector2f(540, 576), player.getCurHealth());
	m_minimap.create("UI/minimap.png", sf::Vector2f(1088, 0), std::to_string(cur_level), std::to_string(roomIter + 1));
	updateMiniMap();

	setUpEnemies(roomIter);
	m_console.sendMessage("Playing as " + player.getName());

	sf::Clock messageGen;

	while (gameWindow->isOpen())
	{
		if (clock.getElapsedTime().asSeconds() > .25) 
		{
			//[-2,-1,1,2] - [up,left,right,down]
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				collided_with = player.move(-2);
				clock.restart();
				adjustView();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				collided_with = player.move(2);
				clock.restart();
				adjustView();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				collided_with = player.move(-1);
				clock.restart();
				adjustView();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				collided_with = player.move(1);
				clock.restart();
				adjustView();
			}
		}

		if (collided_with == 4) {
			int to_kill = m_collider->getPcollidedwith();
			//std::cout << "Enemy #" << to_kill + 1 << ", Vector size: " << totalEnemies << std::endl;
			m_console.sendMessage("Killed " + enemies[to_kill]->getName());
			kill(to_kill);
		}

		sf::Event event;
		while (gameWindow->pollEvent(event)){
			if (event.type == sf::Event::Closed)
				gameWindow->close();
		}

		if (e_clock.getElapsedTime().asSeconds() > 1) {
			for (int i = 0; i < totalEnemies; i++) {
				if (enemies[i]->move() == 1) {
					int hpLost = rand() % 10 + 5;
					m_console.sendMessage(enemies[i]->getName() + " attacked you for " + std::to_string(hpLost) + " damage!");
					player.removeHealth(hpLost);
					m_pstats.updateHealth(player.getCurHealth());
				}
			}
			e_clock.restart();	
		}

		if (roomChangeClock.getElapsedTime().asSeconds() > 3){
			if (collided_with > 0 && collided_with < 3){
				nextLevel = changeRoom();
			}
		}

		if (nextLevel) {
			return 1;
		}

		updateCollider();

		gameWindow->clear();

		gameWindow->setView(gameView);
		//GUIs
		gameWindow->draw(m_console);
		gameWindow->draw(m_pstats);
		//still just rects
		gameWindow->draw(Tooltip);
		gameWindow->draw(Inventory);
		gameWindow->draw(Toolbar);

		gameWindow->draw(m_minimap);
		
		gameWindow->setView(mm_view);
		gameWindow->draw(*currentRoom);

		gameWindow->setView(levelView);
		gameWindow->draw(*currentRoom);
		gameWindow->draw(player);
		for (int i = 0; i < totalEnemies; i++) {
			gameWindow->draw(*enemies[i]);
		}

		gameWindow->display();
	}

	return 0;
}
void Level::adjustView()
{
	viewCenter.left = levelView.getCenter().x - 100;
	viewCenter.top = levelView.getCenter().y - 50;

	if (!viewCenter.contains(player.getPosition()))
	{
		sf::Vector2f playerPos = player.getPosition();
		if (playerPos.x < viewCenter.left || playerPos.x > viewCenter.left + viewCenter.width) {
			//move view in x direction
			levelView.setCenter(playerPos.x, viewCenter.top + 50);
		}
		else if (playerPos.y < viewCenter.top || playerPos.y > viewCenter.top + viewCenter.height) {
			//move view in y direction
			levelView.setCenter(viewCenter.left + 100, playerPos.y);
		}

	}
}
bool Level::changeRoom()
{
	if (collided_with == 2)
	{
		roomIter++;

		if (roomIter == totalRooms) {
			//SHOULD set next level bool to quit this level
			//return true;
			//for now:
			roomIter = 0;
		}

		delete currentRoom;
		currentRoom = new Room(allRooms[roomIter]);
		player.setPosition(currentRoom->getMainEntrance());
		adjustView();
		m_collider->replaceTiles(currentRoom->getWalls(), currentRoom->getEntrances(), currentRoom->getExits());
		updateMiniMap();
		setUpEnemies(roomIter);
		roomChangeClock.restart();
		m_console.sendMessage("You enter the next room...");
		m_console.sendMessage("It's filled with " + enemies[0]->getName() + "s");

	}
	else if(collided_with == 1)
	{
		if (roomIter != 0) 
		{
			roomIter--;
			currentRoom->setNewRoom(allRooms[roomIter]);
			player.setPosition(currentRoom->getMainExit());
			adjustView();
			m_collider->replaceTiles(currentRoom->getWalls(), currentRoom->getEntrances(), currentRoom->getExits());
			updateMiniMap();
			setUpEnemies(roomIter);
			roomChangeClock.restart();
			m_console.sendMessage("You return to the previous room...");
		}
	}

	collided_with = 0;
	return false;
}
void Level::updateMiniMap()
{
	sf::FloatRect mapSize(0, 0, allRooms[roomIter].mapSize.x * 16, allRooms[roomIter].mapSize.y * 16);
	mm_view.reset(mapSize);
	m_minimap.update(std::to_string(cur_level), std::to_string(roomIter + 1));
}
void Level::setUpEnemies(int room_iter)
{
	for (int i = 0; i < totalEnemies; i++) {
		delete enemies[i];
	}

	enemies.clear();
	totalEnemies = 0;

	m_collider->clearEnemies();

	for (int i = 0; i < allEnemies[room_iter].size(); i++)
	{
		Enemy* new_enemy = new Enemy(allEnemies[room_iter][i].filename, allEnemies[room_iter][i].position, allEnemies[room_iter][i].size, i + 1, "Infected Buff Skeleton", m_collider);
		enemies.push_back(new_enemy);
		enemies[i]->addPath(allEnemies[room_iter][i].path);
		totalEnemies++;

		m_collider->addEnemy(new_enemy->getRect());
	}

}
void Level::updateCollider()
{
	m_collider->updatePlayer(player.getRect());

	for (int i = 0; i < totalEnemies; i++)
	{
		m_collider->updateEnemy(enemies[i]->getRect(), i);
	}
}
void Level::kill(int to_kill)
{
	if (totalEnemies > 1) {
		enemies.erase(enemies.begin() + to_kill);
		totalEnemies--;
	}
	else {
		enemies.pop_back();
		totalEnemies = 0;
	}

	m_collider->removeEnemy(to_kill);

	collided_with = 0;
}