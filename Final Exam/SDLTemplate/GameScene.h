#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Fruit.h"
#include <vector>
#include "text.h"
#include "draw.h"
#include "tail.h"

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	void start();
	void draw();
	void update();

	std::vector<tail*>& getTails()
	{
		return tails;
	}

private:
	Player* player;
	std::vector<tail*> tails;
	std::vector<Fruit*> spawnedFruit;

	int points;

	void doSpawnFruitLogic();
	void doCollisionLogic();
	void despawnFruit(Fruit* fruit);
	void spawnTail();
	void moveTail(int x, int y);
};

