#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
	player = new Player();
	this->addGameObject(player);

}

GameScene::~GameScene()
{
	delete player;
}

void GameScene::start()
{
	Scene::start();
	// Initialize any scene logic here

	currentSpawntimer = 300;
	spawnTime = 300; // 5 secs

	for (int i = 0; i < 1; i++)
	{
		spawn();
	}
}

void GameScene::draw()
{
	Scene::draw();
}

void GameScene::update()
{
	Scene::update();

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
