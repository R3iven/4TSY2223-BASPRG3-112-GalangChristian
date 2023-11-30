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
	void doPowerup();
	void doDeath();
	
	void getPowerup1();
	void getPowerup2();
std::vector<Bullet*>& getBullets() 
	{
		return bullets;
	}
	

private:
	SDL_Texture* texture;
	Mix_Chunk* laserSound;
	Mix_Chunk* doubleLaserSound;
	Mix_Chunk* shotGunSound;
	int x;
	int y;
	int width;
	int height;
	int speed;
	int boost;
	float reloadTime;
	float reloadTime2;
	float reloadTime3;
	float currentReloadTime;
	float currentReloadTime2;
	float currentReloadTime3;
	bool isAlive;
	bool isPoweredup;
	bool isCounting;
	int powerupDuration;
	int currentPowerupDuration;

	bool isPowerup1;

	std::vector <Bullet*> bullets;
};

