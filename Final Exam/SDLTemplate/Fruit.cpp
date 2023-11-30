#include "Fruit.h"
#include "Scene.h"
#include "util.h"

Fruit::Fruit()
{
}

Fruit::~Fruit()
{

}

void Fruit::start()
{
	// Load texture
	texture = loadTexture("gfx/points.png");

	// Initialize to avoid garbage values
	width = 0;
	height = 0;


	// query the texture to set our width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
}

void Fruit::update()
{
	
}

void Fruit::draw()
{
	blit(texture, x, y);
}

void Fruit::setPosition(int xPos, int yPos)
{
	this->x = xPos;
	this->y = yPos;
}

int Fruit::getPositionX()
{
	return x;
}

int Fruit::getPositionY()
{
	return y;
}

int Fruit::getWidth()
{
	return width;
}

int Fruit::getHeight()
{
	return height;
}
