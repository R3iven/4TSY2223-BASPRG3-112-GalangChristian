#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include "text.h"
#include "draw.h"
#include "Explosion.h"
#include "powerUp.h"
#include "boss.h"

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

	// powerup spawn logic
	float spawnTimePowerup;
	float currentSpawntimerPowerup;

	Mix_Chunk* powerupSound;

	std::vector<Enemy*> spawnedEnemies;
	std::vector<Explosion*> activeExplosions;
	std::vector<powerUp*> spawnedPowerUp;
	std::vector<boss*> spawnedBoss;

	void doSpawnLogic();
	void doCollisionLogic();
	void doOffscreenLogic();
	void spawn();
	void despawnEnemy(Enemy* enemy);
	void spawnExplosion(int x, int y);
	void spawnExplosion2(int x, int y);
	void updateExplosions();

	void spawnPowerup();
	void doSpawnPowerupLogic();
	void doCollisionPowerupLogic();
	void despawnPowerup(powerUp* powerup);

	void dropPowerUp(int x, int y);
	void doCollisionDropPowerupLogic();

	void despawnBullet(Bullet* bullet);

	int doRandomPowerup();

	void spawnBoss();
	void despawnBoss(boss* boss);

	float cutscenetime;
	float currentCutsceneTime;
	bool isInCutscene;

	int points;
	int bossSpawnPoints;
	bool isBossSpawn;
};

