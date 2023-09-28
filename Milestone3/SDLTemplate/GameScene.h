#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	void start();
	void draw();
	void update();

private:
	Player* player;

	// enemy spawn logic
	float spawnTime;
	float currentSpawntimer;
	std::vector<Enemy*> spawnedEnemies;

	void spawn();
};

