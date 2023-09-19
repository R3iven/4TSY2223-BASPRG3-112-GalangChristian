#include "Player.h"

void Player::start()
{ 
	// Load texture
	texture = loadTexture("gfx/player.png");

		// Initialize to avoid garbage values
		x = 100;
		y = 100;
		width = 0;
		height = 0;
		speed = 2;
		boost = 5;

		// query the texture to set our width and height
		SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Player::update()
{
	if (app.keyboard[SDL_SCANCODE_LSHIFT])
	{
		speed = boost;
	}

	if (app.keyboard[SDL_SCANCODE_BACKSPACE])
	{
		speed = 2;
	}

	if (app.keyboard[SDL_SCANCODE_W])
	{
		y -= (speed * 1);
	}

	if (app.keyboard[SDL_SCANCODE_S])
	{
		y += (speed * 1);
	}

	if (app.keyboard[SDL_SCANCODE_A])
	{
		x -= (speed * 1);
	}

	if (app.keyboard[SDL_SCANCODE_D])
	{
		x += (speed * 1);
	}
}

void Player::draw()
{
	blit(texture, x, y);
}
