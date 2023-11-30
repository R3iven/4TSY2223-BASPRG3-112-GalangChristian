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
    sound->volume = 5;
    SoundManager::playSound(sound);
    lifetime = 20;
	explosionTexture = loadTexture("gfx/explosion.png");

    boom = false;
}

void Explosion::update()
{
    if (boom)
    {
        explosionTexture = loadTexture("gfx/boom.png");
    }

    if (lifetime > 0)
    {
        lifetime--;
    }

    if (lifetime == 0)
    {
        boom = false;
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

void Explosion::bossBoom()
{
    boom = true;
}
