#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include <vector>
#include "util.h"
#include "Player.h"
class powerUp : public GameObject
{
public:
	powerUp();
	~powerUp();
	void start();
	void update();
	void draw();

	void setPosition(int xPos, int yPos);
	
	//get position when offscreen
	int getPositionX();
	int getPositionY();

	int getWidth();
	int getHeight();

private:
	SDL_Texture* texture;
	Mix_Chunk* sound;
	int x;
	int y;

	float directionX;
	float directionY;

	int width;
	int height;
	int speed;
};

