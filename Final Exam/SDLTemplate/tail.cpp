#include "tail.h"

tail::tail()
{
}

tail::~tail()
{
}

void tail::start()
{
	// Load texture
	texture = loadTexture("gfx/player.png");

	// Initialize to avoid garbage values
	width = 0;
	height = 0;
	x = 0;
	y = 0;
	speed = 5;

	// query the texture to set our width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
}

void tail::setDirection(Direction dir)
{
	currentDirection = dir;
}

void tail::update()
{
	// update tail position based on the direction
	if (currentDirection == Direction::Up)
	{
		y -= speed;
	}
	else if (currentDirection == Direction::Down)
	{
		y += speed;
	}
	else if (currentDirection == Direction::Left)
	{
		x -= speed;
	}
	else if (currentDirection == Direction::Right)
	{
		x += speed;
	}

	// update tail position based on the previous position
	if (!tailPositions.empty())
	{
		// move tail to its previous position
		std::pair<int, int> prevPos = tailPositions.front();
		x = prevPos.first;
		y = prevPos.second;

		std::cout << "test2" << std::endl;

		// pop the front to remove the oldest position
		tailPositions.pop_front();
	}
}

void tail::draw()
{
	blit(texture, x, y);
}

void tail::setPosition(int xPos, int yPos)
{
	// store the current position as the previous position
	tailPositions.push_back(std::make_pair(x, y));

	this->x = xPos;
	this->y = yPos;
}

int tail::getPositionX()
{
    return x;
}

int tail::getPositionY()
{
    return y;
}

int tail::getWidth()
{
    return width;
}

int tail::getHeight()
{
    return height;
}
