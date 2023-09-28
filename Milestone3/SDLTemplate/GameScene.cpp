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
}

void GameScene::spawn()
{
	Enemy* enemy = new Enemy();
	this->addGameObject(enemy);
	enemy->setPlayerTarget(player);

	enemy->setPosition(1200, 300 + (rand() % 300));
	spawnedEnemies.push_back(enemy);
}
