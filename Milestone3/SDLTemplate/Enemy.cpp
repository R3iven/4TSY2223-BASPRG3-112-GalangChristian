#include "Enemy.h"
#include "Scene.h"
#include "util.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{

}

void Enemy::start()
{
	// Load texture
	texture = loadTexture("gfx/enemy.png");

	// Initialize to avoid garbage values
	directionX = -1;
	directionY = 1;
	width = 0;
	height = 0;
	speed = 2;
	reloadTime = 60; //reload time of 60 frames, or 1 seconds
	currentReloadTime = 0;
	directionChangeTime = (rand() % 300) - 180; //direction change time of 3-8 sec
	currentDirectionChangeTime = 0;

	reloadTime2 = 32;
	currentReloadTime2 = 0;

	// query the texture to set our width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
}

void Enemy::update()
{
	x += directionX * speed;
	y += directionY * speed;

	// Decrement the enemy's direction timer
	if (currentDirectionChangeTime > 0)
	{
		currentDirectionChangeTime--;
	}

	if (currentDirectionChangeTime == 0)
	{
		directionY = -directionY;
		currentDirectionChangeTime = directionChangeTime;
	}

	// Decrement the enemy's reload timer
	if (currentReloadTime > 0)
	{
		currentReloadTime--;
	}

	if (currentReloadTime == 0)
	{
		float dx = -1;
		float dy = 0;

		calcSlope(playerTarget->getPositionX(), playerTarget->getPositionY(), x, y, &dx, &dy);

		SoundManager::playSound(sound);
		BulletEnemy* bulletEnemy = new BulletEnemy(x - 50 + width, y - 4 + height / 2, dx, dy, 10);
		bullets.push_back(bulletEnemy);
		getScene()->addGameObject(bulletEnemy);
		bulletEnemy->start();

		// after firing, reset the reload timer
		currentReloadTime = reloadTime;
	}

	//memory manage our bullets, when they go offscreen, delete them
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionX() < 0)
		{
			// Cache the variables so we can delete it later
			// we can't delete it after erasing from the vector (leaked pointer)
			BulletEnemy* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToErase;

			break;
		}
	}
}

void Enemy::draw()
{
	blit(texture, x, y);
}

void Enemy::setPlayerTarget(Player* player)
{
	playerTarget = player;
}

void Enemy::setPosition(int xPos, int yPos)
{
	this->x = xPos;
	this->y = yPos;
}

int Enemy::getPositionX()
{
	return x;
}

int Enemy::getPositionY()
{
	return y;
}
