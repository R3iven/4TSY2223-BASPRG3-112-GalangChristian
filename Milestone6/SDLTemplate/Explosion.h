#pragma once
#include "GameObject.h"
#include "draw.h"
#include "Enemy.h"

class Explosion : public GameObject
{
public:
	Explosion(int positionX, int positionY);
	~Explosion();
	void start();
	void update();
	void draw();

	int getLifetime();
	void bossBoom();

private:
	SDL_Texture* explosionTexture;
	Mix_Chunk* sound;

	bool boom;
	int x;
	int y;
	int height;
	int width;
	int lifetime; //lifetime of the explosion
};