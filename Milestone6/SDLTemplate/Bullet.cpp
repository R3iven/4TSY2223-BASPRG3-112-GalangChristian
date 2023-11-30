#include "Bullet.h"

Bullet::Bullet(float positionX, float positionY, float directionX, float directionY, float speed, Side side)
{
	this->x = positionX;
	this->y = positionY;
	this->directionX = directionX;
	this->directionY = directionY;
	this->speed = speed;
	this->side = side;
}

void Bullet::start()
{
	width = 0;
	height = 0;

	lifetime = 180;
	currentLifetime = lifetime;

	if (side == Side::PLAYER_SIDE)
	{
		texture = loadTexture("gfx/playerBullet.png");
	}
	else
	{
		texture = loadTexture("gfx/alienBullet.png");
	}

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Bullet::update()
{
	x += directionX * speed;
	y += directionY * speed;
}

void Bullet::draw()
{
	blit(texture, x, y);
}

float Bullet::getPositionX()
{
	return x;
}

float Bullet::getPositionY()
{
	return y;
}

float Bullet::getWidth()
{
	return width;
}

float Bullet::getHeight()
{
	return height;
}

Side Bullet::getSide()
{
	return side;
}
