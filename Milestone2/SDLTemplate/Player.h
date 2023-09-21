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

private:
	SDL_Texture* texture;
	Mix_Chunk* sound;
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
};

