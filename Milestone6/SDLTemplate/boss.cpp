#include "boss.h"
#include "Scene.h"
#include "util.h"

boss::boss()
{
}

boss::~boss()
{
}

void boss::start()
{
	// Load texture
	texture = loadTexture("gfx/REDBOSS.png");

	// Initialize to avoid garbage values
	directionX = -1;
	directionY = 0;
	width = 0;
	height = 0;
	speed = 1;
	hp = 400;

	isFiring = false;

	reloadTime = 60; //reload time of 60 frames, or 1 seconds
	currentReloadTime = 60;

	fireTime = 8;
	currentFireTime = 0;

	burstTime = 32;
	currentBurstTime = 32;

	isFiring2 = false;

	reloadTime2 = 60;
	currentReloadTime2 = 60;

	fireTime2 = 4;
	currentFireTime2 = 0;

	burstTime2 = 64;
	currentBurstTime2 = 64;

	isFiring3 = false;

	reloadTime3 = 60;
	currentReloadTime3 = 60;

	fireTime3 = 16;
	currentFireTime3 = 0;

	burstTime3 = 36;
	currentBurstTime3 = 36;

	directionChangeTime = 180 + (rand() % 240); //direction change time of 3-6 sec
	currentDirectionChangeTime = 0;

	isInCutscene = true;
	isGoLeft = true;
	changePatternPoints = 0;

	isPattern1 = true;

	isPattern2 = false;
	isGoLeft2 = false;
	isGoRight2 = true;
	isStop = false;
	timer = 30;

	isPattern3 = false;
	isGoLeft3 = true;
	isGoRight3 = false;

	// query the texture to set our width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
}

void boss::update()
{
	texture = loadTexture("gfx/REDBOSS.png");

	x += directionX * speed;
	y += directionY * speed;

	if (isInCutscene == true)
	{
		cutscene();
	}

	if (isInCutscene == false)
	{
		if (isPattern1)
		{
			doMovementPattern();
		}

		if (isPattern2)
		{
			doMovementPattern2();
		}
	
		if (isPattern3)
		{
			doMovementPattern3();
		}
	}


	//memory manage our bullets, when they go offscreen, delete them
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionX() < 0)
		{
			// Cache the variables so we can delete it later
			// we can't delete it after erasing from the vector (leaked pointer)
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToErase;

			break;
		}
	}
}

void boss::draw()
{
	blit(texture, x, y);
}

void boss::setPlayerTarget(Player* player)
{
	playerTarget = player;
}

void boss::setPosition(int xPos, int yPos)
{
	this->x = xPos;
	this->y = yPos;
}

int boss::getPositionX()
{
	return x;
}

int boss::getPositionY()
{
	return y;
}

int boss::getWidth()
{
	return width;
}

int boss::getHeight()
{
	return height;
}

void boss::doFiringPattern1()
{
	if (isFiring)
	{
		// Decrement the fire timer
		if (currentFireTime > 0)
		{
			currentFireTime--;
			//std::cout << "fire time: " << currentFireTime << std::endl;
		}

		if (currentFireTime == 0)
		{
			float dx = 0;
			float dy = 0;

			calcSlope(playerTarget->getPositionX(), playerTarget->getPositionY(), x + width / 2, y + height, &dx, &dy);

			//SoundManager::playSound(sound);
			Bullet* bulletEnemy = new Bullet(x + width / 2, y + height, dx, dy, 5, Side::ENEMY_SIDE);
			bullets.push_back(bulletEnemy);
			getScene()->addGameObject(bulletEnemy);
			bulletEnemy->start();

			// after firing, reset the reload timer
			currentFireTime = fireTime;
		}
	}

	if (isFiring && currentBurstTime > 0)
	{
		currentBurstTime--;
		//std::cout << "Reload time: " << currentBurstTime << std::endl;
	}

	if (currentBurstTime == 0)
	{
		isFiring = false;
		currentBurstTime = burstTime;
	}

	if (!isFiring && currentReloadTime > 0)
	{
		currentReloadTime--;
	}

	if (currentReloadTime == 0)
	{
		isFiring = true;
		currentReloadTime = reloadTime;
		//std::cout << "Reload time: " << currentReloadTime << std::endl;
	}
}

void boss::doFiringPattern2()
{
	if (isFiring2)
	{
		// Decrement the fire timer
		if (currentFireTime2 > 0)
		{
			currentFireTime2--;
			//std::cout << "fire time: " << currentFireTime2 << std::endl;
		}

		if (currentFireTime2 == 0)
		{
			float dx = 0;
			float dy = 0;

			calcSlope(playerTarget->getPositionX(), playerTarget->getPositionY(), x + width / 2, y + height, &dx, &dy);

			//SoundManager::playSound(sound);
			Bullet* bulletEnemy = new Bullet(x + width / 2 - 59, y + height - 50, 0, 1, 10, Side::ENEMY_SIDE);
			bullets.push_back(bulletEnemy);
			getScene()->addGameObject(bulletEnemy);
			bulletEnemy->start();

			Bullet* bulletEnemy2 = new Bullet(x + width / 2 + 52, y + height - 50, 0, 1, 10, Side::ENEMY_SIDE);
			bullets.push_back(bulletEnemy2);
			getScene()->addGameObject(bulletEnemy2);
			bulletEnemy2->start();

			// after firing, reset the reload timer
			currentFireTime2 = fireTime2;
		}
	}

	if (isFiring2 && currentBurstTime2 > 0)		//decrement burst timer
	{
		currentBurstTime2--;
		//std::cout << "Reload time: " << currentBurstTime2 << std::endl;
	}

	if (currentBurstTime2 == 0)		//if burst depleted stop firing, and refill burst timer
	{
		isFiring2 = false;
		currentBurstTime2 = burstTime2;
	}

	if (!isFiring2 && currentReloadTime2 > 0)	//while not firing, decrement reload timer 
	{
		currentReloadTime2--;
	}

	if (currentReloadTime2 == 0)	// if reload timer depleted, refill reload timer and fire again
	{
		isFiring2 = true;
		currentReloadTime2 = reloadTime2;
		//std::cout << "Reload time: " << currentReloadTime2 << std::endl;
	}
}

void boss::doFiringPattern3()
{
	if (isFiring3)
	{
		// Decrement the fire timer
		if (currentFireTime3 > 0)
		{
			currentFireTime3--;
			//std::cout << "fire time: " << currentFireTime3 << std::endl;
		}

		if (currentFireTime3 == 0)
		{
			float dx = 0;
			float dy = 0;

			calcSlope(playerTarget->getPositionX(), playerTarget->getPositionY(), x + width / 2, y + height, &dx, &dy);

			//SoundManager::playSound(sound);
			Bullet* bulletEnemy = new Bullet(x + width / 2, y + height, -.5, 1, 5, Side::ENEMY_SIDE);
			bullets.push_back(bulletEnemy);
			getScene()->addGameObject(bulletEnemy);
			bulletEnemy->start();

			//SoundManager::playSound(sound);
			Bullet* bulletEnemy2 = new Bullet(x + width / 2, y + height, 0, 1, 5, Side::ENEMY_SIDE);
			bullets.push_back(bulletEnemy2);
			getScene()->addGameObject(bulletEnemy2);
			bulletEnemy2->start();

			//SoundManager::playSound(sound);
			Bullet* bulletEnemy3 = new Bullet(x + width / 2, y + height, 0.65, 1, 5, Side::ENEMY_SIDE);
			bullets.push_back(bulletEnemy3);
			getScene()->addGameObject(bulletEnemy3);
			bulletEnemy3->start();

			// after firing, reset the reload timer
			currentFireTime3 = fireTime3;
		}
	}

	if (isFiring3 && currentBurstTime3 > 0)
	{
		currentBurstTime3--;
		//std::cout << "Reload time: " << currentBurstTime3 << std::endl;
	}

	if (currentBurstTime3 == 0)
	{
		isFiring3 = false;
		currentBurstTime3 = burstTime3;
	}

	if (!isFiring3 && currentReloadTime3 > 0)
	{
		currentReloadTime3--;
	}

	if (currentReloadTime3 == 0)
	{
		isFiring3 = true;
		currentReloadTime3 = reloadTime3;
		//std::cout << "Reload time: " << currentReloadTime3 << std::endl;
	}
}

void boss::doMovementPattern()
{
	doFiringPattern1();

	if (isGoLeft) // call going left once only 
	{
		directionX = -1; 
		directionY = 0;
		speed = 4;
		
		isGoLeft = false;
	}
	
	if (x < 0)
	{
		std::cout << "BUMP, go right" << std::endl << std::endl;
		directionX = +1;

		changePatternPoints++;
	}

	if (x > SCREEN_WIDTH - width)
	{
		std::cout << "BUMP, go left" << std::endl << std::endl;
		isGoLeft = true;
	}

	if (changePatternPoints == 3 && x > SCREEN_WIDTH/2 - width / 2) // if it bumps to right side no. of times, change pattern
	{
		std::cout << "change pattern" << std::endl << std::endl;
		changePatternPoints = 0;
		isPattern2 = true;
		isPattern1 = false;
	}
}

void boss::doMovementPattern2()
{
	if (isGoLeft2)
	{
		directionX = -1;
		speed = 1;

		isGoLeft2 = false;
	}

	if (isGoRight2)
	{
		directionX = 1;
		speed = 1;

		isGoRight2 = false;
	}

	if (isStop)
	{
		directionX = 0;
	}

	if (isStop && timer ==30)
	{
		directionX = 0;

		timer--;

		std::cout << timer << std::endl << std::endl;
	}

	if (timer == 0)
	{
		isStop = false;
		timer = 30;
	}

	doFiringPattern2();

	if (x <= 144 - width / 2)
	{
		isGoRight2 = true; 

		//std::cout << "Go, Right" << std::endl << std::endl;
	}

	if (x >= 576 - width / 2)
	{
		directionX = -1;

		changePatternPoints++;
		std::cout << "POINTS" << std::endl << std::endl;
	}

	if (x >= 576 - width / 2 && changePatternPoints == 2)
	{
		isGoLeft2 = true;
		//std::cout << "Go, left" << std::endl << std::endl;

		changePatternPoints = 0;
		isPattern2 = false;
		isPattern3 = true;
	}
}

void boss::doMovementPattern3()
{
	if (isGoLeft3)
	{
		directionX = -1;
		speed = 2.5;

		isGoLeft3 = false;
	}

	if (isGoRight3)
	{
		directionX = 1;
		speed = 2.5;

		isGoRight3 = false;
	}

	doFiringPattern3();

	if (x <= 252 - width / 2)
	{
		directionX = +1;

		changePatternPoints++;
		std::cout << "POINTS" << std::endl << std::endl;
	}

	if (x >= 468 - width / 2)
	{
		isGoLeft3 = true;
		//std::cout << "Go, Left" << std::endl << std::endl;
	}
		

	if (x <= 252 - width / 2 && changePatternPoints == 4)
	{
		isGoRight3 = true;
		//std::cout << "Go, left" << std::endl << std::endl;

		changePatternPoints = 0;
		isPattern3 = false;
		isPattern1 = true;
	}
}


void boss::isHit()
{
	//load hit texture
	texture = loadTexture("gfx/REDBOSShit.png");
	hp--;
	std::cout << hp << std::endl;
}

int boss::getHp()
{
	return hp;
}

void boss::cutscene()
{
	directionX = 0;
	directionY = 1;

	if (y > 0) 
	isInCutscene = false;
}