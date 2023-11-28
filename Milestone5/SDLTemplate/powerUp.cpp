#include "powerUp.h"

powerUp::powerUp()
{
}

powerUp::~powerUp()
{
}

void powerUp::start()
{
	// Load texture
	texture = loadTexture("gfx/points.png");

	// Initialize to avoid garbage values
	directionX = 0;
	directionY = 1;
	width = 0;
	height = 0;
	speed = 2;

	// query the texture to set our width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void powerUp::update()
{
	x += directionX * speed;
	y += directionY * speed;

}

void powerUp::draw()
{
	blit(texture, x, y);
}

void powerUp::setPosition(int xPos, int yPos)
{
	this->x = xPos;
	this->y = yPos;
}

int powerUp::getPositionX()
{
	return x;
}

int powerUp::getPositionY()
{
	return y;
}

int powerUp::getWidth()
{
	return width;
}

int powerUp::getHeight()
{
	return height;
}
