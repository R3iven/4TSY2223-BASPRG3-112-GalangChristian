#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include "text.h"
#include "draw.h"
#include "Explosion.h"

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
	std::vector<Explosion*> activeExplosions;

	void doSpawnLogic();
	void doCollisionLogic();
	void doOffscreenLogic();
	void spawn();
	void despawnEnemy(Enemy* enemy);
	void spawnExplosion(int x, int y);
	void updateExplosions();

	int points;
};

