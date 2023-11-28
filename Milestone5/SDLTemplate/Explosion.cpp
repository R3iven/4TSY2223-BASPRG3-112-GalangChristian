#include "Explosion.h"

Explosion::Explosion(int positionX, int positionY)
{
    this->x = positionX;
    this->y = positionY;
}

Explosion::~Explosion()
{
}

void Explosion::start()
{
    sound = SoundManager::loadSound("sound/245372__quaker540__hq-explosion.ogg");
    sound->volume = 20;
    SoundManager::playSound(sound);
    lifetime = 30;
	explosionTexture = loadTexture("gfx/explosion.png");
}

void Explosion::update()
{
    if (lifetime > 0)
    {
        lifetime--;
    }
}

void Explosion::draw()
{
    if (lifetime > 0)
    {
        blit(explosionTexture, x, y);
    }
}

int Explosion::getLifetime()
{
    return lifetime;
}
