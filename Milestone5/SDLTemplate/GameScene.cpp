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

	spawnTimePowerup = 600 + (rand() % 1800); //10-30 secs cd
	currentSpawntimerPowerup = spawnTimePowerup;

	powerupSound = SoundManager::loadSound("sound/power.ogg");
	powerupSound->volume = 40;
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
	doSpawnPowerupLogic();
	doCollisionLogic();
	doCollisionPowerupLogic();
	doCollisionDropPowerupLogic();
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
						spawnExplosion(currentEnemy->getPositionX() - 20, currentEnemy->getPositionY() - 20); // Spawn explosion at enemy's position
						dropPowerUp(currentEnemy->getPositionX(), currentEnemy->getPositionY());
						despawnEnemy(currentEnemy);
						despawnBullet(bullet);
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
	//memory manage our enemy, when they go offscreen, delete them
	for (int i = 0; i < spawnedEnemies.size(); i++)
	{
		if (spawnedEnemies[i]->getPositionX() > 770 || spawnedEnemies[i]->getPositionX() < -50 || spawnedEnemies[i]->getPositionY() > 770)
		{
			// Cache the variables so we can delete it later
			// we can't delete it after erasing from the vector (leaked pointer)
			Enemy* enemyToErase = spawnedEnemies[i];
			spawnedEnemies.erase(spawnedEnemies.begin() + i);
			delete enemyToErase;

			break;
		}
	}

	//memory manage powerup, when they go offscreen, delete them
	for (int i = 0; i < spawnedPowerUp.size(); i++)
	{
		if (spawnedPowerUp[i]->getPositionX() > 770 || spawnedPowerUp[i]->getPositionX() < -50 || spawnedPowerUp[i]->getPositionY() > 770)
		{
			// Cache the variables so we can delete it later
			// we can't delete it after erasing from the vector (leaked pointer)
			powerUp* powerupToErase = spawnedPowerUp[i];
			spawnedPowerUp.erase(spawnedPowerUp.begin() + i);
			delete powerupToErase;

			break;
		}
	}
}

void GameScene::spawn()
{
	Enemy* enemy = new Enemy();
	this->addGameObject(enemy);
	enemy->setPlayerTarget(player);

	enemy->setPosition(216 + (rand() % 504),-100);
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

void GameScene::spawnPowerup()
{
	powerUp* powerup = new powerUp();
	this->addGameObject(powerup);

	powerup->setPosition(0 + (rand() % 680), -100);
	spawnedPowerUp.push_back(powerup);
}

void GameScene::doSpawnPowerupLogic()
{
	if (currentSpawntimerPowerup > 0)
	{
		currentSpawntimerPowerup--;
	}

	if (currentSpawntimerPowerup == 0)
	{
		for (int i = 0; i < 1; i++)
		{
			spawnPowerup();
		}
		currentSpawntimerPowerup = spawnTimePowerup;
	}
}

void GameScene::doCollisionPowerupLogic()
{
	//check for collisions
	for (int i = 0; i < objects.size(); i++)
	{
		// cast to powerup
		powerUp* powerup = dynamic_cast<powerUp*>(objects[i]);

		// check if the cast was success, if object[i] is a bullet
		if (powerup != NULL)
		{
			int collision = checkCollision(
				player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(),
				powerup->getPositionX(), powerup->getPositionY(), powerup->getWidth(), powerup->getHeight()
			);

			if (collision == 1)
			{
				std::cout << "powered up";
				SoundManager::playSound("sound/power.ogg");
				
				int randomPowerupType = doRandomPowerup(); //pick a random powerup
				if (randomPowerupType == 1)
				{
					player->getPowerup1();
					player->doPowerup();
				}
				else if (randomPowerupType == 2)
				{
					player->getPowerup2();
					player->doPowerup();
				}

				despawnPowerup(powerup);
				break;
			}
		}
	}
}

void GameScene::despawnPowerup(powerUp * powerup)
{
	int index = -1;
	for (int i = 0; i < spawnedPowerUp.size(); i++)
	{
		// if the pointer matches
		if (powerup == spawnedPowerUp[i])
		{
			index = i;
			break;
		}
	}

	// if any match is found
	if (index != -1)
	{
		spawnedPowerUp.erase(spawnedPowerUp.begin() + index);
		delete powerup;
	}
}

void GameScene::dropPowerUp(int x, int y)
{
	int randomChance = 1 + rand() % 10;

	int dropPercentage = 9; // chance to drop

	if (randomChance <= dropPercentage)
	{
		// Spawn powerup at the enemy's position
		powerUpDrop* powerup = new powerUpDrop(x, y);
		this->addGameObject(powerup);
		spawnedPowerUp.push_back(powerup);
	}
}

void GameScene::doCollisionDropPowerupLogic()
{
	//check for collisions
	for (int i = 0; i < objects.size(); i++)
	{
		// cast to powerup
		powerUpDrop* powerup = dynamic_cast<powerUpDrop*>(objects[i]);

		// check if the cast was success, if object[i] is a bullet
		if (powerup != NULL)
		{
			int collision = checkCollision(
				player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(),
				powerup->getPositionX(), powerup->getPositionY(), powerup->getWidth(), powerup->getHeight()
			);

			if (collision == 1)
			{
				std::cout << "powered up";
				SoundManager::playSound("sound/power.ogg");

				int randomPowerupType = doRandomPowerup(); //pick a random powerup
				if (randomPowerupType == 1)
				{
					player->getPowerup1();
					player->doPowerup();
				}
				else if (randomPowerupType == 2)
				{
					player->getPowerup2();
					player->doPowerup();
				}
				despawnPowerup(powerup);
				break;
			}
		}
	}
}

void GameScene::despawnBullet(Bullet* bullet) 
{
	std::vector<Bullet*>& playerBullets = player->getBullets();

	int index = -1;
	for (int i = 0; i < playerBullets.size(); i++) 
	{
		if (bullet == playerBullets[i]) {
			index = i;
			break;
		}
	}

	if (index != -1) 
	{
		playerBullets.erase(playerBullets.begin() + index);
		delete bullet;
	}
}

int GameScene::doRandomPowerup()
{
	int randomPowerup = 1 + rand() % 2;
	std::cout << "random powerup: " << randomPowerup;
	return randomPowerup;
}
