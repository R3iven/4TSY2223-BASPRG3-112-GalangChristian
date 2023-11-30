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
		x = 360;
		y = 500;
		width = 0;
		height = 0;
		speed = 2;
		boost = 5;
		reloadTime = 8; //reload time of 8 frames, or 0.5 seconds
		currentReloadTime = 0;
		isAlive = true;
		
		isPowerup1 = false;

		isCounting = false;
		isPoweredup = false;
		powerupDuration = 900; // 15 secs
		currentPowerupDuration = powerupDuration;

		reloadTime2 = 16;
		currentReloadTime2 = 0;

		reloadTime3 = 24;
		currentReloadTime3 = 0;

		// query the texture to set our width and height
		SDL_QueryTexture(texture, NULL, NULL, &width, &height);

		laserSound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
		doubleLaserSound = SoundManager::loadSound("sound/196914__dpoggioli__laser-gun.ogg");
		doubleLaserSound->volume = 20;

		shotGunSound = SoundManager::loadSound("sound/shotgun.ogg");
		shotGunSound->volume = 20;
}

void Player::update()
{
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
	
	if (!isAlive) return;

	if (app.keyboard[SDL_SCANCODE_LSHIFT])
	{
		speed = boost;
	}

	if (app.keyboard[SDL_SCANCODE_BACKSPACE])
	{
		speed = 2;
	}

	texture = loadTexture("gfx/player.png");

	if (app.keyboard[SDL_SCANCODE_W])
	{
		y -= (speed * 1.2);
	}

	if (app.keyboard[SDL_SCANCODE_S])
	{
		y += (speed * 1);
	}

	if (app.keyboard[SDL_SCANCODE_A])
	{
		x -= (speed * 1);
		texture = loadTexture("gfx/playerLeft.png");
	}

	if (app.keyboard[SDL_SCANCODE_D])
	{
		x += (speed * 1);
		texture = loadTexture("gfx/playerRight.png");
	}

	// Decrement the player's reload timer
	if (currentReloadTime > 0)
	{
		currentReloadTime--;
	}

	if (isPoweredup) {
		doPowerup(); // call doPowerup continuously during powerup
	}

	if (app.keyboard[SDL_SCANCODE_SPACE] && currentReloadTime == 0 && isPoweredup == false)
	{
		SoundManager::playSound(laserSound);
		Bullet* bullet = new Bullet(x + 19, y - 10, 0, -1, 15, Side::PLAYER_SIDE);
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
	
	if (app.keyboard[SDL_SCANCODE_SPACE] && currentReloadTime2 == 0 && isPoweredup == true && isPowerup1 == true)
	{		
		SoundManager::playSound(doubleLaserSound);

		// spawn 1st bullet
		Bullet* bullet1 = new Bullet(x, y + 10, 0, -1, 15, Side::PLAYER_SIDE);
		bullets.push_back(bullet1);
		getScene()->addGameObject(bullet1);
		bullet1->start();

		// Spawn 2nd bullet
		Bullet* bullet2 = new Bullet(x + 40, y + 10, 0, -1, 15, Side::PLAYER_SIDE);
		bullets.push_back(bullet2);
		getScene()->addGameObject(bullet2);
		bullet2->start();

		// reset reload timer
		currentReloadTime2 = reloadTime2;
	}

	// Decrement the player's reload timer
	if (currentReloadTime3 > 0)
	{
		currentReloadTime3--;
	}

	if (app.keyboard[SDL_SCANCODE_SPACE] && currentReloadTime3 == 0 && isPoweredup == true && isPowerup1 == false)
	{
		SoundManager::playSound(shotGunSound);

		// spawn 1st bullet
		Bullet* bullet1 = new Bullet(x + 19, y - 10, -0.3, -1, 15, Side::PLAYER_SIDE);
		bullets.push_back(bullet1);
		getScene()->addGameObject(bullet1);
		bullet1->start();

		// Spawn 2nd bullet
		Bullet* bullet2 = new Bullet(x + 19, y - 10, 0, -1, 15, Side::PLAYER_SIDE);
		bullets.push_back(bullet2);
		getScene()->addGameObject(bullet2);
		bullet2->start();

		// Spawn 3rd bullet
		Bullet* bullet3 = new Bullet(x + 19, y - 10, .3, -1, 15, Side::PLAYER_SIDE);
		bullets.push_back(bullet3);
		getScene()->addGameObject(bullet3);
		bullet3->start();

		// reset reload timer
		currentReloadTime3 = reloadTime3;
	}
}


void Player::draw()
{
	if (!isAlive) return;
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

void Player::doPowerup()
{
	isPoweredup = true;

	if (isPoweredup && !isCounting)
	{
		isCounting = true;
		
		if (currentPowerupDuration > 0)
		{
			currentPowerupDuration--;
		}

		isCounting = false;

		std::cout << "Powerup: " << currentPowerupDuration << std::endl; //debug

		if (currentPowerupDuration == 0)
		{
			isPoweredup = false;
			currentPowerupDuration = powerupDuration; //reset duration
		}
	}

	if (isPoweredup && isCounting)// reset the timer if replenished while powerup is active
	{
		currentPowerupDuration = 0;

		std::cout << "Powerup: still counting" << currentPowerupDuration << std::endl; //debug

		if (currentPowerupDuration == 0)
		{
			isPoweredup = false;
			currentPowerupDuration = powerupDuration;
			isCounting = false;
		}
	}	
}

void Player::doDeath()
{
	isAlive = false;
}

void Player::getPowerup1()
{
	isPowerup1 = true;
}

void Player::getPowerup2()
{
	isPowerup1 = false;
}