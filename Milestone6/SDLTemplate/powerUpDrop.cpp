#include "powerUpDrop.h"

powerUpDrop::powerUpDrop(int positionX, int positionY)
{
	this->x = positionX;
	this->y = positionY;
}

powerUpDrop::~powerUpDrop()
{
}

void powerUpDrop::start()
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

void powerUpDrop::update()
{
	x += directionX * speed;
	y += directionY * speed;

}

void powerUpDrop::draw()
{
	blit(texture, x, y);
}

void powerUpDrop::setPosition(int xPos, int yPos)
{
	this->x = xPos;
	this->y = yPos;
}

int powerUpDrop::getPositionX()
{
	return x;
}

int powerUpDrop::getPositionY()
{
	return y;
}

int powerUpDrop::getWidth()
{
	return width;
}

int powerUpDrop::getHeight()
{
	return height;
}
