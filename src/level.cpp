#include "level.h"

//0 - path
//1 - wall
//2 - entrance
//3 - exit

Level::Level()
{}
Level::Level(int level_num) : cur_level(level_num),	totalRooms(0), roomIter(0), main_ret(2), totalEnemies(0)
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
int Level::runLevel(sf::RenderWindow* gameWindow, PlayerInstructions p_inst)
{
	g_window = gameWindow;
	gameView = g_window->getDefaultView();

	gameOver.setSize(sf::Vector2f(g_window->getSize().x, g_window->getSize().y));
	gameOver.setPosition(0, 0);
	sf::Color go_Color = sf::Color(255, 255, 255, 0);
	gameOver.setFillColor(go_Color);

	currentRoom = new Room(allRooms[roomIter]);

	m_collider = new Collider(currentRoom->getWalls(), currentRoom->getEntrances(), currentRoom->getExits());
	player.setUp(p_inst, m_collider);
	player.setPosition(currentRoom->getMainEntrance());
	//attack = player.getattackiterator
	attack = 0;
	to_hit = -1;

	m_console.create("UI/gameconsole.png", sf::Vector2f(0, 576));
	m_pstats.create("UI/playerStats.png", p_inst.portrait_file_name, sf::Vector2f(540, 576), player.getCurHealth());
	m_minimap.create("UI/minimap.png", sf::Vector2f(1088, 0), std::to_string(cur_level), std::to_string(roomIter + 1));
	updateMiniMap();

	setUpEnemies(roomIter);
	m_console.sendMessage("Playing as " + player.getName());

	sf::Clock messageGen;

	while (g_window->isOpen())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			attack = 4;
		}
		//[-2,-1,1,2] - [up,left,right,down]
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			player.move(UP);
			adjustView();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			player.move(DOWN);
			adjustView();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			player.move(LEFT);
			adjustView();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			player.move(RIGHT);
			adjustView();
		}

		sf::Event event;
		while (g_window->pollEvent(event)){
			if (event.type == sf::Event::Closed)
				g_window->close();
		}

		if (roomChangeClock.getElapsedTime().asSeconds() > 3){
			if (m_collider->getPcollidedwith() > 1 && m_collider->getPcollidedwith() < 4){
				main_ret = changeRoom(m_collider->getPcollidedwith());
			}
		}

		update();

		switch (main_ret)
		{
			case -1: return main_ret;
			case 0: { killPlayer();  return main_ret; }
			case 1: return main_ret;
		}
	}

	return -1;
}
void Level::update()
{
	updatePlayer();
	updateEnemies();
	updateCollider();
	updateWindow();
}
void Level::updatePlayer()
{
	if (attack > 0) 
	{
		player.attack(attack);

		if (attack == 3) 
		{
			to_hit = m_collider->getPattacked();
			
			if (to_hit != -1) 
			{
				if (!enemies[to_hit]->isDead())
				{
					int hplost = player.getDamage();
					enemies[to_hit]->updateHealth(hplost);
					m_console.sendMessage("You attacked" + enemies[to_hit]->getName() + " for " + std::to_string(hplost) + " damage!");

					if (enemies[to_hit]->getHealth() < 1){
						to_kill = to_hit;
						m_console.sendMessage("Killed " + enemies[to_kill]->getName());
						enemies[to_kill]->kill();
						m_collider->removeEnemy(to_kill);
					}
				}

				to_hit = -1;
			}
		}

		attack--;
	}

}
void Level::updateEnemies() 
{
	if (e_clock.getElapsedTime().asSeconds() > 1) {
		for (int i = 0; i < totalEnemies; i++) 
		{
			enemies[i]->move();
			//test if attack
			/*int hpLost = enemies[i]->attack();
			m_console.sendMessage(enemies[i]->getName() + " attacked you for " + std::to_string(hpLost) + " damage!");
			player.removeHealth(hpLost);
			m_pstats.updateHealth(player.getCurHealth());

			if (player.getCurHealth() < 1) {
				m_pstats.updateHealth(0);
				main_ret = 0;*/
		}
		e_clock.restart();
	}

	if (kill_clock.getElapsedTime().asSeconds() > .25)
	{
		for (int i = 0; i < totalEnemies; i++)
		{
			if (enemies[i]->isDead()) {
				if (enemies[i]->killAnimation()) {
					kill(i);
				}
			}
		}

		kill_clock.restart();
	}
}
void Level::updateWindow()
{
	g_window->clear();

	g_window->setView(gameView);
	//GUIs
	g_window->draw(m_console);
	g_window->draw(m_pstats);
	//still just rects
	g_window->draw(Tooltip);
	g_window->draw(Inventory);
	g_window->draw(Toolbar);

	g_window->draw(m_minimap);

	g_window->setView(mm_view);
	g_window->draw(*currentRoom);

	g_window->setView(levelView);
	g_window->draw(*currentRoom);
	g_window->draw(player);
	for (int i = 0; i < totalEnemies; i++) {
		g_window->draw(*enemies[i]);
	}

	g_window->draw(gameOver);

	g_window->display();

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
int Level::changeRoom(int choice)
{
	if (choice == 3)
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
	else if(choice == 2)
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

	return 2;
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
		Enemy* new_enemy = new Enemy(allEnemies[room_iter][i], i + 1, allEnemies[room_iter][i].displayname, m_collider);
		enemies.push_back(new_enemy);
		enemies[i]->addPath(allEnemies[room_iter][i].path);
		totalEnemies++;

		m_collider->addEnemy(new_enemy->getRect());
	}

}
void Level::updateCollider()
{
	m_collider->updatePlayer(player.getRect());

	for (int i = 0; i < m_collider->getTotalEnemies(); i++){
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

	//m_collider->removeEnemy(to_kill);
}
void Level::killPlayer()
{
	sf::Clock pkill_Clock;
	//run death animation
	while (true) {
		if (pkill_Clock.getElapsedTime().asSeconds() > .25) {
			if (player.kill()) {
				//updateWindow();
				break;
			}
			updateWindow();
			pkill_Clock.restart();
		}
	}

	//slowly fade screen out
	sf::Color go_Color = sf::Color(255, 255, 255, 0);

	while (int(go_Color.a) < 255)
	{
		if (pkill_Clock.getElapsedTime().asSeconds() > .25)
		{
			go_Color.a += 17;
			
			gameOver.setFillColor(go_Color);
			updateWindow();

			pkill_Clock.restart();
		}
	}


	//go back to level x room 1
}
void Level::resetLevel(int level_num)
{
	cur_level = level_num;
	//totalRooms = 0;
	roomIter = 0;
	main_ret = 2;
	totalEnemies = 0;

	levelView.reset(sf::FloatRect(0, 0, 250, 150));
	levelView.setViewport(sf::FloatRect(0, 0, .85, .75));
	viewCenter.left = levelView.getCenter().x - 100;
	viewCenter.top = levelView.getCenter().y - 50;
	viewCenter.height = 84;
	viewCenter.width = 184;

	mm_view.setViewport(sf::FloatRect(.86, .07, .13, .15));

	gameOver.setSize(sf::Vector2f(g_window->getSize().x, g_window->getSize().y));
	gameOver.setPosition(0, 0);
	sf::Color go_Color = sf::Color(255, 255, 255, 0);
	gameOver.setFillColor(go_Color);

	m_console.reset();
}