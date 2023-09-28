#include "BulletEnemy.h"

BulletEnemy::BulletEnemy(float positionX, float positionY, float directionX, float directionY, float speed)
{
	this->x = positionX;
	this->y = positionY;
	this->directionX = directionX;
	this->directionY = directionY;
	this->speed = speed;
}

void BulletEnemy::start()
{
	texture = loadTexture("gfx/alienBullet.png");

	width = 0;
	height = 0;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void BulletEnemy::update()
{
	x += directionX * speed;
	y += directionY * speed;
}

void BulletEnemy::draw()
{
	blit(texture, x, y);
}

float BulletEnemy::getPositionX()
{
	return x;
}

float BulletEnemy::getPositionY()
{
	return y;
}

float BulletEnemy::getWidth()
{
	return width;
}

float BulletEnemy::getHeight()
{
	return height;
}
