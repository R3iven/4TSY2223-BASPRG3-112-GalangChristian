#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include <vector>
#include "util.h"
#include "Player.h"

class Fruit : public GameObject
{
public:
	Fruit();
	~Fruit();
	void start();
	void update();
	void draw();
	void setPosition(int xPos, int yPos); 

	int getPositionX();
	int getPositionY();

	int getWidth();
	int getHeight();

private:
	SDL_Texture* texture;
	Mix_Chunk* sound;
	Player* playerTarget;
	int x;
	int y;

	int width;
	int height;
};

