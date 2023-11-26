#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
	player = new Player();
	this->addGameObject(player);

	points = 0;
}

GameScene::~GameScene()
{
	delete player;
}

void GameScene::start()
{
	Scene::start();
	// Initialize any scene logic here

	initFonts();
	currentSpawntimer = 300;
	spawnTime = 300; // 5 secs

	for (int i = 0; i < 1; i++)
	{
		spawn();
	}
}

void GameScene::draw()
{
	prepareScene();

	// Draw the background
	drawBackground("gfx/background.png");

	Scene::draw();

	drawText(110, 10, 255, 255, 255, TEXT_CENTER, "POINTS: %03d", points);

	if (player->getIsAlive() == false)
	{
		drawText(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 255, 255, 255, TEXT_CENTER, "GAME OVER!");
	}

	presentScene();
}

void GameScene::update()
{
	Scene::update();

	doSpawnLogic();
	doCollisionLogic();
	doOffscreenLogic();	
}

void GameScene::doSpawnLogic()
{
	if (currentSpawntimer > 0)
	{
		currentSpawntimer--;
	}

	if (currentSpawntimer == 0)
	{
		for (int i = 0; i < 1; i++)
		{
			spawn();
		}

		currentSpawntimer = spawnTime;
	}
}

void GameScene::doCollisionLogic()
{
	//check for collisions
	for (int i = 0; i < objects.size(); i++)
	{
		// cast to bullet
		Bullet* bullet = dynamic_cast<Bullet*>(objects[i]);

		// check if the cast was success, if object[i] is a bullet
		if (bullet != NULL)
		{
			// if from enemy
			if (bullet->getSide() == Side::ENEMY_SIDE)
			{
				int collision = checkCollision(
					player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(),
					bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()
				);

				if (collision == 1)
				{
					if (player->getIsAlive()) // only explodes once, when the player is alive (bug encountered where player explodes even dead)
					{
						spawnExplosion(player->getPositionX() - 20, player->getPositionY() - 20); // Spawn explosion at enemy's position
					}
					
					player->doDeath();
					break;
				}
			}

			// if from player
			else if (bullet->getSide() == Side::PLAYER_SIDE)
			{
				for (int i = 0; i < spawnedEnemies.size(); i++)
				{
					Enemy* currentEnemy = spawnedEnemies[i];

					int collision = checkCollision(
						currentEnemy->getPositionX(), currentEnemy->getPositionY(), currentEnemy->getWidth(), currentEnemy->getHeight(),
						bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()
					);

					if (collision == 1)
					{
						spawnExplosion(currentEnemy->getPositionX(), currentEnemy->getPositionY() - 20); // Spawn explosion at enemy's position
						despawnEnemy(currentEnemy);
						// increment points
						points++;
						// IMPORTANT: only despawn one at a time
						break;
					}
				}
			}
		}
	}
}

void GameScene::doOffscreenLogic()
{
	//memory manage our enemy, when they go offscreen to the left, delete them
	for (int i = 0; i < spawnedEnemies.size(); i++)
	{
		if (spawnedEnemies[i]->getPositionX() < -100 || spawnedEnemies[i]->getPositionY() > 850 || spawnedEnemies[i]->getPositionY() < -100)
		{
			// Cache the variables so we can delete it later
			// we can't delete it after erasing from the vector (leaked pointer)
			Enemy* enemyToErase = spawnedEnemies[i];
			spawnedEnemies.erase(spawnedEnemies.begin() + i);
			delete enemyToErase;

			break;
		}
	}
}

void GameScene::spawn()
{
	Enemy* enemy = new Enemy();
	this->addGameObject(enemy);
	enemy->setPlayerTarget(player);

	enemy->setPosition(1380, 300 + (rand() % 300));
	spawnedEnemies.push_back(enemy);
}

void GameScene::despawnEnemy(Enemy* enemy)
{
	int index = -1;
	for (int i = 0; i < spawnedEnemies.size(); i++)
	{
		// if the pointer matches
		if (enemy == spawnedEnemies[i])
		{
			index = i;
			break;
		}
	}

	// if any match is found
	if (index != -1)
	{
		spawnedEnemies.erase(spawnedEnemies.begin() + index);
		delete enemy;
	}
}

void GameScene::spawnExplosion(int x, int y)
{
	Explosion* explosion = new Explosion(x, y);
	this->addGameObject(explosion);
	activeExplosions.push_back(explosion);
}

void GameScene::updateExplosions()
{
	for (auto it = activeExplosions.begin(); it != activeExplosions.end(); /* no increment */)
	{
		(*it)->update();

		if ((*it)->getLifetime() <= 0)
		{
			delete (*it);
			it = activeExplosions.erase(it);
		}
		else
		{
			++it;
		}
	}
}
