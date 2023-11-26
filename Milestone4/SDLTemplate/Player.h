#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include <vector>

class Player :
    public GameObject
{
public:
	~Player();
	void start();
	void update();
	void draw();

	int getPositionX();
	int getPositionY();

	int getWidth();
	int getHeight();
	bool getIsAlive();
	void doDeath();

private:
	SDL_Texture* texture;
	Mix_Chunk* laserSound;
	Mix_Chunk* shotgunSound;
	int x;
	int y;
	int width;
	int height;
	int speed;
	int boost;
	float reloadTime;
	float reloadTime2;
	float currentReloadTime;
	float currentReloadTime2;
	std::vector <Bullet*> bullets;
	bool isAlive;
};

