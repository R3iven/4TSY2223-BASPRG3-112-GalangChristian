#include "Player.h"
#include "Scene.h"

Player::~Player()
{
	//memory manage our body parts, delete all bullets on player death
	
}

void Player::start()
{ 
	// Load texture
	texture = loadTexture("gfx/player.png");

	// Initialize to avoid garbage values
	x = 360;
	y = 500;
	width = 0;
	height = 0;
	speed = 3;
	boost = 5;
	isAlive = true;

	// query the texture to set our width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Player::update()
{
    if (!isAlive) return;

    if (app.keyboard[SDL_SCANCODE_LSHIFT])
    {
        speed = boost;
    }
    else
    {
        speed = 3;
    }

    // Reset movement
    bool moveUp = false;
    bool moveDown = false;
    bool moveLeft = false;
    bool moveRight = false;

    if (app.keyboard[SDL_SCANCODE_W])
    {
        moveUp = true;
    }
    if (app.keyboard[SDL_SCANCODE_S])
    {
        moveDown = true;
    }
    if (app.keyboard[SDL_SCANCODE_A])
    {
        moveLeft = true;
    }
    if (app.keyboard[SDL_SCANCODE_D])
    {
        moveRight = true;
    }

    // cant move in opposite direction
    if (moveUp && !moveDown && currentDirection != Direction::Down)
    {
        currentDirection = Direction::Up;
    }
    else if (moveDown && !moveUp && currentDirection != Direction::Up)
    {
        currentDirection = Direction::Down;
    }
    else if (moveLeft && !moveRight && currentDirection != Direction::Right)
    {
        currentDirection = Direction::Left;
    }
    else if (moveRight && !moveLeft && currentDirection != Direction::Left)
    {
        currentDirection = Direction::Right;
    }

    // keep moving in direction
    if (currentDirection == Direction::Up)
    {
        y -= speed;
        texture = loadTexture("gfx/player.png");
    }
    else if (currentDirection == Direction::Down)
    {
        y += speed;
        texture = loadTexture("gfx/playerdown.png");
    }
    else if (currentDirection == Direction::Left)
    {
        x -= speed;
        texture = loadTexture("gfx/playerleft.png");
    }
    else if (currentDirection == Direction::Right)
    {
        x += speed;
        texture = loadTexture("gfx/playerright.png");
    }

}



void Player::draw()
{
	blit(texture, x, y);
}

int Player::getPositionX()
{
	return x;
}

int Player::getPositionY()
{
	return y;
}

int Player::getWidth()
{
	return width;
}

int Player::getHeight()
{
	return height;
}

bool Player::getIsAlive()
{
	return isAlive;
}

void Player::Dead()
{
    isAlive = false;
}

