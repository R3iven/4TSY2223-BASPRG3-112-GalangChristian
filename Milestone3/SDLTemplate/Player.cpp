#include "Player.h"
#include "Scene.h"

Player::~Player()
{
	//memory manage our bullets, delete all bullets on player death
	for (int i = 0; i < bullets.size(); i++)
	{
		delete bullets[i];
	}
	bullets.clear();
}

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
		reloadTime = 8; //reload time of 8 frames, or 0.5 seconds
		currentReloadTime = 0;

		reloadTime2 = 32;
		currentReloadTime2 = 0;

		// query the texture to set our width and height
		SDL_QueryTexture(texture, NULL, NULL, &width, &height);

		sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
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

	// Decrement the player's reload timer
	if (currentReloadTime > 0)
	{
		currentReloadTime--;
	}

	if (app.keyboard[SDL_SCANCODE_F] && currentReloadTime == 0 )
	{
		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x + width, y -4 + height/2, 1, 0, 15);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);
		bullet->start();

		// after firing, reset the reload timer
		currentReloadTime = reloadTime;
	}

	// Decrement the player's reload timer
	if (currentReloadTime2 > 0)
	{
		currentReloadTime2--;
	}

	if (app.keyboard[SDL_SCANCODE_G] && currentReloadTime2 == 0)
	{
		SoundManager::playSound(sound);

		// spawn 1st bullet
		Bullet* bullet1 = new Bullet(x - 35 + width, y - 25 + height / 2, 1, 0, 10);
		bullets.push_back(bullet1);
		getScene()->addGameObject(bullet1);
		bullet1->start();

		// Spawn 2nd bullet
		Bullet* bullet2 = new Bullet(x - 35 + width, y + 15 + height / 2, 1, 0, 10); 
		bullets.push_back(bullet2);
		getScene()->addGameObject(bullet2);
		bullet2->start();

		// reset reload timer
		currentReloadTime2 = reloadTime2;
	}

	//memory manage our bullets, when they go offscreen, delete them
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionX() > SCREEN_WIDTH)
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
