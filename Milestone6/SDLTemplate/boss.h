#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include <vector>
#include "util.h"
#include "Player.h"
#include "powerUpDrop.h"

class boss : public GameObject
{
public:
	boss();
	~boss();
	void start();
	void update();
	void draw();
	void setPlayerTarget(Player* player);
	void setPosition(int xPos, int yPos);

	//get position when offscreen
	int getPositionX();
	int getPositionY();

	int getWidth();
	int getHeight();

	void doFiringPattern1();
	void doFiringPattern2();
	void doFiringPattern3();

	void doMovementPattern();
	void doMovementPattern2();
	void doMovementPattern3();

	void isHit();
	int getHp();

	void cutscene();

private:
	SDL_Texture* texture;
	Mix_Chunk* sound;
	Player* playerTarget;
	int x;
	int y;

	float directionX;
	float directionY;

	int width;
	int height;
	int speed;
	int boost;

	bool isFiring;

	float reloadTime;	// interval between bursts
	float currentReloadTime;

	float fireTime;		// interval between bullets / distance between bullets
	float currentFireTime;

	float burstTime;	// burst duration / how many bullets in a burst
	float currentBurstTime;
	
	bool isFiring2;

	float reloadTime2;
	float currentReloadTime2;

	float fireTime2;		
	float currentFireTime2;

	float burstTime2;	
	float currentBurstTime2;

	bool isFiring3;

	float reloadTime3;
	float currentReloadTime3;

	float fireTime3;
	float currentFireTime3;

	float burstTime3;
	float currentBurstTime3;

	float directionChangeTime;
	float currentDirectionChangeTime;

	bool isInCutscene;
	bool isGoLeft;

	bool isPattern1;

	bool isPattern2;
	bool isGoLeft2;
	bool isGoRight2;
	bool isStop;

	bool isPattern3;
	bool isGoLeft3;
	bool isGoRight3;

	int changePatternPoints;
	int hp;

	int timer;

	std::vector <Bullet*> bullets;
};

